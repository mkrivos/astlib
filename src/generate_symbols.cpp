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
#include <iostream>

using namespace astlib;

int main(int argc, char* argv[])
{
    bool useCpp14 = 1;

    CodecRegister codecRegister;
    codecRegister.populateCodecsFromDirectory("specs");

    std::cout << "#pragma once" << std::endl << std::endl;
    std::cout << "#include \"astlib/AsterixItemCode.h\"" << std::endl << std::endl;
    if (useCpp14)
    {
    }
    else
        std::cout << "#define DECLARE_ASTERIX_ITEM(id, subid, type) ((type << 24) | (subid << 16) | id)" << std::endl << std::endl;

    auto globals = codecRegister.enumerateGlobalSymbols();
    int index = 1;
    for(const auto& entry: globals)
    {
        const astlib::PrimitiveItem& item = entry.second;
        if (useCpp14)
        {
            std::cout << "constexpr AsterixItemCode ASTERIX_ITEM_" << entry.first << "(" << Poco::NumberFormatter::formatHex(index, 4, true) << ", 0, PrimitiveType::" << item.getType().toString() << ");" << std::endl;
        }
        else
        {
            std::cout << "#define ASTERIX_ITEM_" << entry.first << " DECLARE_ASTERIX_ITEM(" << Poco::NumberFormatter::formatHex(index, 4, true) << ", 0, " << item.getType().toString() << ")" << std::endl;
        }
        index++;
    }

    return 0;
}


