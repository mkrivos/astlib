///
/// \package astlib
/// \file enumerate_symbols.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/GeneratedTypes.h"
#include "astlib/model/BitsDescription.h"
#include "astlib/PrimitiveItem.h"

#include <Poco/Ascii.h>
#include <Poco/XML/Content.h>
#include "Poco/SAX/InputSource.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Attr.h"
#include "Poco/DOM/Node.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/AutoPtr.h"
#include <Poco/AutoPtr.h>
#include "Poco/Exception.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include <Poco/FileStream.h>
#include <Poco/Exception.h>
#include <Poco/DirectoryIterator.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/String.h>


#include <iostream>
#include <map>

class BitsRegister
{
public:
    /**
     * Loads and registers all XML descriptions from directory.
     * @param path
     */
    std::vector<std::string> populateCodecsFromDirectory(const std::string& path)
    {
        auto dir = Poco::DirectoryIterator(path);
        auto end = Poco::DirectoryIterator();
        std::vector<std::string> files;

        while (dir != end)
        {
            Poco::File file = *dir;
            if (file.isFile())
            {
                Poco::Path filename = file.path();
                if (filename.getBaseName().find(std::string("asterix_cat")) == 0)
                {
                    files.push_back(file.path());
                }
            }
            ++dir;
        }

        return files;
    }

    void load(const std::string& filename)
    {
        try
        {
            Poco::XML::InputSource src(filename);
            Poco::XML::NamePool* pool = new Poco::XML::NamePool(3571);
            Poco::XML::DOMParser parser(pool);
            pool->release();

            parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, true);
            parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, true);

            Poco::XML::AutoPtr<Poco::XML::Document> document = parser.parse(&src);
            poco_check_ptr (document);

            auto root = Poco::XML::AutoPtr<Poco::XML::Element>(document->documentElement(), true);

            if (root->nodeName() != "Category")
            {
                throw Poco::DataFormatException("no 'Category' element at top level");
            }

            loadCategory(*root);
        }
        catch(Poco::Exception& e)
        {
            throw Poco::Exception("CodecDeclarationLoader::load(" + filename + "): " + e.displayText());
        }
    }

    void loadCategory(const Poco::XML::Element& root)
    {
        _signature = "cat" + root.getAttribute("id") + "-" + root.getAttribute("ver");

        for (auto node = root.firstChild(); node; node = node->nextSibling())
        {
            const Poco::XML::Element* element = dynamic_cast<Poco::XML::Element*>(node);
            if (element)
            {
                auto name = element->nodeName();
                if (name == "DataItem")
                {
                    loadDataItem(*element);
                }
            }
        }
    }

    void loadDataItem(const Poco::XML::Element& element)
    {
        auto description = element.getChildElement("DataItemName")->innerText();
        Poco::XML::Element* formatElement = dynamic_cast<Poco::XML::Element*>(element.getChildElement("DataItemFormat")->firstChild());
        poco_assert(formatElement);

        loadFormatElement(*formatElement);
    }

    void loadFormatElement(const Poco::XML::Element& formatElement)
    {
        astlib::ItemFormat format = astlib::ItemFormat(formatElement.nodeName());

        switch (format.toValue())
        {
            case astlib::ItemFormat::Fixed:
                loadFixedDeclaration(formatElement);
                break;

            case astlib::ItemFormat::Variable:
                loadVariableDeclaration(formatElement);
                break;

            case astlib::ItemFormat::Repetitive:
                loadRepetitiveDeclaration(formatElement);
                break;

            case astlib::ItemFormat::Compound:
                loadCompoundDeclaration(formatElement);
                break;

            case astlib::ItemFormat::Explicit:
                loadExplicitDeclaration(formatElement);
                break;

            default:
                throw Poco::Exception("CodecDeclarationLoader::loadDataItem(): unknown item type " + format.toString());
        }
    }

    void loadFixedDeclaration(const Poco::XML::Element& element)
    {
        loadFixed(element);
    }

    void loadFixed(const Poco::XML::Element& element, bool arrayType = false)
    {
        loadBitsDeclaration(element, arrayType);
    }

    void loadVariableDeclaration(const Poco::XML::Element& parent)
    {
        for (auto node = parent.firstChild(); node; node = node->nextSibling())
        {
            const Poco::XML::Element* element = dynamic_cast<Poco::XML::Element*>(node);
            if (element && element->nodeName() == "Fixed")
            {
                loadFixed(*element);
            }
        }
    }

    void loadRepetitiveDeclaration(const Poco::XML::Element& parent)
    {
        for (auto node = parent.firstChild(); node; node = node->nextSibling())
        {
            const Poco::XML::Element* element = dynamic_cast<Poco::XML::Element*>(node);
            if (element && element->nodeName() == "Fixed")
            {
                loadFixed(*element, true);
            }
        }
    }

    void loadCompoundDeclaration(const Poco::XML::Element& parent)
    {
        for (auto node = parent.firstChild(); node; node = node->nextSibling())
        {
            const Poco::XML::Element* element = dynamic_cast<Poco::XML::Element*>(node);
            if (element)
            {
                loadFormatElement(*element);
            }
        }
    }

    void loadExplicitDeclaration(const Poco::XML::Element& element)
    {
        // TODO:
    }

    void loadBitsDeclaration(const Poco::XML::Element& parent, bool arrayType)
    {
        for (auto node = parent.firstChild(); node; node = node->nextSibling())
        {
            const Poco::XML::Element* element = dynamic_cast<Poco::XML::Element*>(node);
            if (element && element->nodeType() == Poco::XML::Node::ELEMENT_NODE && element->nodeName() == "Bits")
            {
                astlib::BitsDescription bits;

                if (element->hasAttribute("bit"))
                {
                    const Poco::XML::Element* presenceNode = dynamic_cast<const Poco::XML::Element*>(element->getChildElement("BitsPresence"));
                    if (presenceNode)
                    {
                        continue;
                    }

                    bits.bit = Poco::NumberParser::parse(element->getAttribute("bit"));
                    if (element->hasAttribute("fx"))
                    {
                        bits.fx = Poco::NumberParser::parse(element->getAttribute("fx"));
                    }
                }
                else
                {
                    bits.from = Poco::NumberParser::parse(element->getAttribute("from"));
                    bits.to = Poco::NumberParser::parse(element->getAttribute("to"));
                    if (bits.from < bits.to)
                        std::swap(bits.from, bits.to);

                    // Enumerations
                    const Poco::XML::Element* node = dynamic_cast<const Poco::XML::Element*>(element->getChildElement("BitsValue"));
                    for(; node; node = dynamic_cast<const Poco::XML::Element*>(node->nextSibling()))
                    {
                        if (node->nodeName() == "BitsValue")
                        {
                            int value = Poco::NumberParser::parse(node->getAttribute("val"));
                            std::string key = node->innerText();
                            bits.addEnumeration(key, value);
                            //std::cout << "     enum " << key << " = " << value << std::endl;
                        }
                    }
                }

                if (element->hasAttribute("encode"))
                {
                    auto str = element->getAttribute("encode");
                    str[0] = Poco::Ascii::toUpper(str[0]);
                    if (str == "6bitschar")
                        str = "SixBitsChar";
                    bits.encoding = astlib::Encoding(str);
                }

                bits.name = dynamic_cast<const Poco::XML::Element*>(element->getChildElement("BitsShortName"))->innerText();
                Poco::toLowerInPlace(bits.name);
                Poco::replaceInPlace(bits.name, "_", ".");
                Poco::replaceInPlace(bits.name, "/", "_");

                if (parent.hasAttribute("length"))
                {
                    auto len = Poco::NumberParser::parse(parent.getAttribute("length"));
                    if (len > 8)
                    {
                       // std::cout << bits.name << " " << len << " bytes\n";
                    }
                }

                const Poco::XML::Element* descrNode = dynamic_cast<const Poco::XML::Element*>(element->getChildElement("BitsName"));
                if (descrNode)
                {
                    bits.description = descrNode->innerText();
                }

                const Poco::XML::Element* unitNode = dynamic_cast<const Poco::XML::Element*>(element->getChildElement("BitsUnit"));
                if (unitNode)
                {
                    auto units = unitNode->innerText();
                    if (Poco::icompare(units, "M") == 0)
                    {
                        bits.units = astlib::Units::M;
                    }
                    else if (Poco::icompare(units, "NM") == 0)
                    {
                        bits.units = astlib::Units::NM;
                    }
                    else if (Poco::icompare(units, "FL") == 0)
                    {
                        bits.units = astlib::Units::FL;
                    }
                    else if (Poco::icompare(units, "FT") == 0)
                    {
                        bits.units = astlib::Units::FT;
                    }
                    else
                    {
                        //throw Exception("Unknown unit type in " + bits.name);
                    }

                    if (unitNode->hasAttribute("scale"))
                    {
                        bits.scale = Poco::NumberParser::parseFloat(unitNode->getAttribute("scale"));
                    }

                    if (unitNode->hasAttribute("min"))
                    {
                        bits.min = Poco::NumberParser::parseFloat(unitNode->getAttribute("min"));
                    }

                    if (unitNode->hasAttribute("max"))
                    {
                        bits.max = Poco::NumberParser::parseFloat(unitNode->getAttribute("max"));
                    }
                }

                bits.repeat = arrayType;
                //std::cout << "      " << bits.toString() << " enc " << bits.encoding.toString() << std::endl;
                addPrimitiveItem(bits);
            }
        }
    }

    void addPrimitiveItem(const astlib::BitsDescription& bits)
    {
        if (Poco::icompare(bits.name,"FX") == 0 ||
            Poco::icompare(bits.name, "spare") == 0 ||
            Poco::icompare(bits.name, "unused") == 0
        )
            return;

        astlib::PrimitiveType type;

        if (bits.effectiveBitsWidth() == 1)
        {
            type = astlib::PrimitiveType::Boolean;
        }
        else
        {
            if (bits.scale != 1.0)
            {
                type = astlib::PrimitiveType::Real;
            }
            else if (bits.encoding == astlib::Encoding::Signed)
            {
                type = astlib::PrimitiveType::Integer;
            }
            else if (bits.encoding == astlib::Encoding::Unsigned || bits.encoding == astlib::Encoding::Octal)
            {
                type = astlib::PrimitiveType::Unsigned;
            }
            else
            {
                type = astlib::PrimitiveType::String;
            }

        }

        if (symbols.find(bits.name) == symbols.end())
        {
            symbols[bits.name] = astlib::PrimitiveItem(bits.name, bits.description, type, bits.repeat);
        }
        else
        {
            astlib::PrimitiveItem item = symbols[bits.name];
            if (item.getDescription().empty() || (item.getDescription().size() < bits.description.size()))
                symbols[bits.name] = astlib::PrimitiveItem(bits.name, bits.description, type, bits.repeat|item.isArray());

            if (item.getType() != type)
            {
                std::cerr << bits.name << " type differs " << item.getType().toString() << " from " << type.toString() << std::endl;
                std::cerr << "  change type to " << type.toString() << std::endl;
            }
        }

        categories[bits.name].insert(_signature);
    }

    std::map<std::string, astlib::PrimitiveItem> symbols;
    std::map<std::string, std::set<std::string>> categories;
    std::string _signature;
};


int main(int argc, char* argv[])
{
    std::string specs = "specs";
    std::string module = "AsterixItemDictionary";

    if (argc > 1)
    {
        specs = argv[1];

        if (argc > 2)
            module = argv[2];
    }


    std::cout << "Args: " << argc << std::endl;

    std::cout << "Reading specs: " << specs << std::endl;
    std::cout << "Generating source: " << module << "[.cpp .h]" << std::endl;

    try
    {
        BitsRegister bits;
        auto files = bits.populateCodecsFromDirectory(specs);
        auto& globals = bits.symbols;

        {
            for(auto file: files)
            {
                bits.load(file);
            }

            {
            	Poco::FileOutputStream csv("asterix_items.csv");
				for (const auto& entry : globals)
				{
					astlib::PrimitiveItem item = entry.second;

					csv << item.getType().toString() << ", " << (item.isArray() ? " Vector, " : " Scalar, " ) << entry.first << ", " << "\"" << item.getDescription() << "\",";
					for(auto cat: bits.categories[entry.first])
					{
						csv << "\"" << cat << "\"" << ',';
					}
					csv << std::endl;
				}
            }

            Poco::FileOutputStream header(module + ".h");
            header << "/// @brief file generated from XML asterix descriptions" << std::endl << std::endl;
            header << "#pragma once" << std::endl << std::endl;
            header << "#include \"astlib/AsterixItemCode.h\"" << std::endl << std::endl;
            header << "namespace astlib {" << std::endl << std::endl;

            int index = 1;
            for (const auto& entry : globals)
            {
                astlib::PrimitiveItem item = entry.second;
                std::string upperName = Poco::toUpper(entry.first);
                Poco::replaceInPlace(upperName, ".", "_");

                header << "constexpr AsterixItemCode " << upperName << "(" << Poco::NumberFormatter::formatHex(index, 4, true) << ", PrimitiveType::" << item.getType().toString() << ", " << item.isArray() << ");  ///< " << item.getDescription() << std::endl;
                index++;
            }

            header << std::endl;

            for (const auto& entry : globals)
            {
                std::string upperName = Poco::toUpper(entry.first);
                Poco::replaceInPlace(upperName, ".", "_");

                header << "extern const std::string SYMBOL_" << upperName << ";" << std::endl;
            }
            header << std::endl << "constexpr int ASTERIX_ITEM_COUNT = " << Poco::NumberFormatter::format(globals.size()) << ";" << std::endl << std::endl;

            header << "ASTLIB_API AsterixItemCode asterixSymbolToCode(const std::string& symbol);" << std::endl;
            header << "ASTLIB_API const std::string& asterixCodeToSymbol(AsterixItemCode code);" << std::endl;
            header << std::endl << "}" << std::endl;
        }

        // -------------------------------------------------------------------------------------------------------------

        {
            Poco::FileOutputStream source(module + ".cpp");
            source << "/// @brief file generated from XML asterix descriptions" << std::endl << std::endl;
            source << "#include \"" << module << ".h\"" << std::endl;
            source << "#include <unordered_map>" << std::endl << std::endl;
            source << "namespace astlib {" << std::endl << std::endl;

            for (const auto& entry : globals)
            {
                std::string upperName = Poco::toUpper(entry.first);
                Poco::replaceInPlace(upperName, ".", "_");

                source << "const std::string " << upperName << "_SYMBOL = \"" << entry.first << "\";" << std::endl;
            }

            source << std::endl << std::endl;
            source << "static struct AsterixGeneratedEntry { const std::string& name; const std::string description; } codeToNameTable[ASTERIX_ITEM_COUNT] = {\n";

            for (const auto& entry : globals)
            {
                std::string upperName = Poco::toUpper(entry.first);
                Poco::replaceInPlace(upperName, ".", "_");

                source << "    { " << upperName << "_SYMBOL, \"" << entry.first << "\" }," << std::endl;
            }
            source << "};" << std::endl << std::endl;

            source << "static std::unordered_map<std::string, AsterixItemCode> symbolToCodeMap = {" << std::endl;
            for (const auto& entry : globals)
            {
                std::string upperName = Poco::toUpper(entry.first);
                Poco::replaceInPlace(upperName, ".", "_");

                source << "    { " << upperName << "_SYMBOL, " << upperName << " }," << std::endl;
            }
            source << "};" << std::endl << std::endl;

            const char functions[] = "AsterixItemCode asterixSymbolToCode(const std::string& symbol)\n"
                "{\n"
                "    return symbolToCodeMap[symbol];\n"
                "}\n"
                "\n"
                "const std::string& asterixCodeToSymbol(AsterixItemCode code)\n"
                "{\n"
                "    int index = code.code();\n"
                "    poco_assert(index < ASTERIX_ITEM_COUNT);\n"
                "    return codeToNameTable[index-1].name;\n"
                "}\n";

            source << functions << std::endl;

            source << "}" << std::endl;
        }

        // -------------------------------------------------------------------------------------------------------------

        {
            Poco::FileOutputStream js("asterixitems.js");
            js << "/// @brief file generated from XML asterix descriptions" << std::endl << std::endl;

            int index = 1;
            js << "var exports = module.exports = {\n";

            for (const auto& entry : globals)
            {
                astlib::PrimitiveItem item = entry.second;
                std::string upperName = Poco::toUpper(entry.first);
                Poco::replaceInPlace(upperName, ".", "_");

                astlib::AsterixItemCode code(index, item.getType().toValue(), item.isArray());
                js << "    " << upperName << ": " << Poco::NumberFormatter::formatHex(code.value, 4, true) << ",  ///< " << item.getDescription() << std::endl;
                index++;
            }

            js << "};\n";
            js << std::endl;
        }

        Poco::File jsFile("asterixitems.js");
        jsFile.moveTo("../../node");
        std::cout << "Generated " << globals.size() << " unique symbols\n;";
    }
    catch(Poco::Exception& e)
    {
        std::cerr << e.displayText() << std::endl;
        return 1;
    }

    return 0;
}


