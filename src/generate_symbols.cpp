///
/// \package astlib
/// \file enumerate_symbols.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/CodecRegister.h"
#include <Poco/NumberFormatter.h>
#include <Poco/FileStream.h>

#include <iostream>

using namespace astlib;

int main(int argc, char* argv[])
{
    std::string module = "AsterixItemDictionary";
    CodecRegister codecRegister;
    codecRegister.populateCodecsFromDirectory("specs");

    Poco::FileOutputStream header(module + ".h");
    header << "/// @brief file generated from XML asterix descriptions" << std::endl << std::endl;
    header << "#pragma once" << std::endl << std::endl;
    header << "#include \"astlib/AsterixItemCode.h\"" << std::endl << std::endl;
    header << "namespace astlib {" << std::endl << std::endl;

    auto globals = codecRegister.enumerateGlobalSymbols();
    int index = 1;
    for(const auto& entry: globals)
    {
        const astlib::PrimitiveItem& item = entry.second;
        std::string upperName = Poco::toUpper(entry.first);
        Poco::replaceInPlace(upperName, ".", "_");

        header << "constexpr AsterixItemCode ASTERIX_CODE_" << upperName << "(" << Poco::NumberFormatter::formatHex(index, 4, true) << ", PrimitiveType::" << item.getType().toString() << ");  ///< " << item.getDescription() << std::endl;
        index++;
    }

    header << std::endl;

    for(const auto& entry: globals)
    {
        std::string upperName = Poco::toUpper(entry.first);
        Poco::replaceInPlace(upperName, ".", "_");

        header << "extern const std::string ASTERIX_SYMBOL_" << upperName << ";" << std::endl;
    }
    header << std::endl << "constexpr int ASTERIX_ITEM_COUNT = " << Poco::NumberFormatter::format(globals.size()) << ";" << std::endl << std::endl;

    header << "AsterixItemCode asterixSymbolFromCode(const std::string& symbol);" << std::endl;
    header << "const std::string& asterixCodeFromSymbol(AsterixItemCode code);" << std::endl;
    header << std::endl << "}" << std::endl;

    // -------------------------------------------------------------------------------------------------------------

    Poco::FileOutputStream source(module + ".cpp");
    source << "/// @brief file generated from XML asterix descriptions" << std::endl << std::endl;
    source << "#include \"" << module << ".h\"" << std::endl;
    source << "#include <unordered_map>" << std::endl << std::endl;
    source << "namespace astlib {" << std::endl << std::endl;

    for(const auto& entry: globals)
    {
        std::string upperName = Poco::toUpper(entry.first);
        Poco::replaceInPlace(upperName, ".", "_");

        source << "const std::string ASTERIX_SYMBOL_" << upperName << " = \"" << entry.first << "\";" << std::endl;
    }

    source << std::endl << std::endl;
    source << "static struct AsterixGeneratedEntry { const std::string& name; const std::string description; } codeToNameTable[ASTERIX_ITEM_COUNT] = {\n";

    for(const auto& entry: globals)
    {
        std::string upperName = Poco::toUpper(entry.first);
        Poco::replaceInPlace(upperName, ".", "_");

        source << "    { ASTERIX_SYMBOL_" << upperName << ", \"\" },"<< std::endl;
    }
    source << "};" << std::endl << std::endl;

    source << "static std::unordered_map<std::string, AsterixItemCode> symbolToCodeMap = {" << std::endl;
    for(const auto& entry: globals)
    {
        std::string upperName = Poco::toUpper(entry.first);
        Poco::replaceInPlace(upperName, ".", "_");

        source << "    { ASTERIX_SYMBOL_" << upperName << ", ASTERIX_CODE_" << upperName << " },"<< std::endl;
    }
    source << "};" << std::endl << std::endl;

    const char functions[] =
    "AsterixItemCode asterixSymbolFromCode(const std::string& symbol)\n" \
    "{\n" \
    "    return symbolToCodeMap[symbol];\n" \
    "}\n" \
    "\n" \
    "const std::string& asterixCodeFromSymbol(AsterixItemCode code)\n" \
    "{\n" \
    "    int index = code.code();\n" \
    "    poco_assert(index < ASTERIX_ITEM_COUNT);\n" \
    "    return codeToNameTable[index+1].name;\n" \
    "}\n";

    source << functions << std::endl;

    source << "}" << std::endl;
    return 0;
}


