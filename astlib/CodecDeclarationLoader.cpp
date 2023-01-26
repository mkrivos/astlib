///
/// \package astlib
/// \file CodecDeclarationLoader.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 31Jan.,2017 
/// \brief Formal XML Description Loader (ASTERIXED format)
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CodecDeclarationLoader.h"
#include "Exception.h"
#include "model/CodecDescription.h"
#include "model/CategoryDescription.h"
#include "model/VariableItemDescription.h"
#include "model/RepetitiveItemDescription.h"
#include "model/ExplicitItemDescription.h"
#include "model/CompoundItemDescription.h"

#include "AsterixItemDictionary.h"

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

#include <iostream>

using namespace Poco::XML;

namespace astlib
{

CodecDeclarationLoader::CodecDeclarationLoader(bool verbose) :
    _verbose(verbose)
{
}

CodecDeclarationLoader::~CodecDeclarationLoader()
{
}

CodecDescriptionPtr CodecDeclarationLoader::parse(std::istream& input)
{
    try
    {
        CodecDescriptionPtr codecDescription(new CodecDescription);
        Poco::XML::InputSource src(input);
        Poco::XML::NamePool* pool = new Poco::XML::NamePool(3571);
        Poco::XML::DOMParser parser(pool);
        pool->release();

        parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, true);
        parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, true);

        Poco::XML::AutoPtr<Poco::XML::Document> document = parser.parse(&src);
        poco_check_ptr (document);

        auto root = Poco::XML::AutoPtr<Element>(document->documentElement(), true);

        if (root->nodeName() != "Category")
        {
            throw Poco::DataFormatException("no 'Category' element at top level");
        }

        loadCategory(*codecDescription, *root);
        return codecDescription;
    }
    catch(Poco::Exception& e)
    {
        throw Exception("CodecDeclarationLoader::parse(): " + e.displayText());
    }
}

void CodecDeclarationLoader::loadCategory(CodecDescription& codecDescription, const Element& root)
{
    CategoryDescription categoryDescription;

    int cat = _category = Poco::NumberParser::parse(root.getAttribute("id"));
    categoryDescription.setCategory(cat);
    categoryDescription.setEdition(root.getAttribute("ver"));
    categoryDescription.setFamily(AsterixFamily::Eurocontrol);
    categoryDescription.setDescription(root.getAttribute("name"));
    codecDescription.addCategoryDescription(categoryDescription);

    if (_verbose)
    {
        std::cout << "Loading Description '" << categoryDescription.toString() << std::endl;
    }

    for (auto node = root.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element)
        {
            auto name = element->nodeName();
            if (name == "DataItem")
            {
                ItemDescriptionPtr item = loadDataItem(codecDescription, *element);
                if (item)
                    codecDescription.addDataItem(item);
            }
        }
    }

    for (auto node = root.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element)
        {
            auto name = element->nodeName();
            if (name == "UAP")
            {
                loadUap(codecDescription, *element);
            }
        }
    }
}

void CodecDeclarationLoader::loadUap(CodecDescription& codecDescription, const Element& parent)
{
    for (auto node = parent.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element)
        {
            auto name = element->nodeName();
            if (name == "UAPItem")
            {
                auto bit = Poco::NumberParser::parse(element->getAttribute("bit"));
                bool mandatory = (element->getAttribute("presence") == "M");
                auto idString = element->innerText();
                int id = 0;
                if (idString == "SP")
                    id = ItemDescription::SP;
                else if (idString == "RE")
                    id = ItemDescription::RE;
                else if (idString == "-")
                    id = ItemDescription::NONE;
                else if (idString == "FX")
                    id = ItemDescription::FX;
                else
                    id = Poco::NumberParser::parse(idString);

                if (id != ItemDescription::FX)
                {
                    codecDescription.addUapItem(bit, id, mandatory);
                    if (_verbose)
                    {
                        std::cout << "Uap bit " << bit << " = item " << id << " mandatory " << (mandatory?"yes":"no") << std::endl;
                    }
                }
            }
        }
    }
}

ItemDescriptionPtr CodecDeclarationLoader::loadDataItem(CodecDescription& codecDescription, const Poco::XML::Element& element)
{
    auto idString = element.getAttribute("id");
    int id = 0;
    if (idString == "SP")
        id = ItemDescription::SP;
    else if (idString == "RE")
        id = ItemDescription::RE;
    else
        id = Poco::NumberParser::parse(idString);

    auto description = element.getChildElement("DataItemName")->innerText();
    Poco::XML::Element* formatElement = dynamic_cast<Poco::XML::Element*>(element.getChildElement("DataItemFormat")->firstChild());
    poco_assert(formatElement);
    
    if (_verbose)
    {
        std::cout << "  " << id << " " << formatElement->nodeName() << " " << description << std::endl;
    }

    return loadFormatElement(codecDescription, id, description, *formatElement);
}

ItemDescriptionPtr CodecDeclarationLoader::loadFixedDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Element& element)
{
    Fixed fixed = loadFixed(codecDescription, element);
    return std::make_shared<FixedItemDescription>(id, description, fixed);
}

Fixed CodecDeclarationLoader::loadFixed(CodecDescription& codecDescription, const Element& element, bool repetitive)
{
    int length = Poco::NumberParser::parse(element.getAttribute("length"));
    BitsDescriptionArray bitsArray = loadBitsDeclaration(codecDescription, element, repetitive);
    poco_assert(bitsArray.size());
    return Fixed(bitsArray, length);
}

ItemDescriptionPtr CodecDeclarationLoader::loadVariableDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Element& parent)
{
    FixedVector fixeds;
    for (auto node = parent.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeName() == "Fixed")
        {
            Fixed fixed = loadFixed(codecDescription, *element);
            fixeds.push_back(fixed);
        }
    }
    return std::make_shared<VariableItemDescription>(id, description, fixeds);
}

ItemDescriptionPtr CodecDeclarationLoader::loadRepetitiveDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Element& parent)
{
    FixedVector fixeds;
    for (auto node = parent.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeName() == "Fixed")
        {
            Fixed fixed = loadFixed(codecDescription, *element, true);
            fixeds.push_back(fixed);
        }
    }
    return std::make_shared<RepetitiveItemDescription>(id, description, fixeds);
}

ItemDescriptionPtr CodecDeclarationLoader::loadCompoundDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Element& parent)
{
    ItemDescriptionVector items;
    for (auto node = parent.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element)
        {
            ItemDescriptionPtr item = loadFormatElement(codecDescription, id, description, *element);
            if (item)
                items.push_back(item);
        }
    }
    return std::make_shared<CompoundItemDescription>(id, description, items);
}

ItemDescriptionPtr CodecDeclarationLoader::loadExplicitDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Element& parent)
{
        FixedVector fixeds;
    for (auto node = parent.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeName() == "Fixed")
        {
            Fixed fixed = loadFixed(codecDescription, *element, true);
            fixeds.push_back(fixed);
        }
    }
    return std::make_shared<ExplicitItemDescription>(id, description, fixeds);
}

BitsDescriptionArray CodecDeclarationLoader::loadBitsDeclaration(CodecDescription& codecDescription, const Element& parent, bool repetitive)
{
    BitsDescriptionArray bitsArray;

    for (auto node = parent.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeType() == Node::ELEMENT_NODE && element->nodeName() == "Bits")
        {
            auto name = dynamic_cast<const Element*>(element->getChildElement("BitsShortName"))->innerText();
            Poco::toLowerInPlace(name);
            Poco::replaceInPlace(name, "_", ".");
            Poco::replaceInPlace(name, "/", "_");

            const AsterixItemCode code(asterixSymbolToCode(name));

         //   if (!code.isValid())
         //       throw Exception("Codec declared symbol '" + name + "' which is no known by current asterix dictionary");

            BitsDescription bits(code);
            bits.name = name;

            if (element->hasAttribute("bit"))
            {
                bits.bit = Poco::NumberParser::parse(element->getAttribute("bit"));
                if (element->hasAttribute("fx"))
                {
                    bits.fx = Poco::NumberParser::parse(element->getAttribute("fx"));
                }

                const Poco::XML::Element* presenceNode = dynamic_cast<const Poco::XML::Element*>(element->getChildElement("BitsPresence"));
                if (presenceNode)
                {
                    bits.presence = Poco::NumberParser::parse(presenceNode->innerText());
                }
            }
            else
            {
                bits.from = Poco::NumberParser::parse(element->getAttribute("from"));
                bits.to = Poco::NumberParser::parse(element->getAttribute("to"));
                if (bits.from < bits.to)
                    std::swap(bits.from, bits.to);

                // Enumerations
                const Element* node = dynamic_cast<const Element*>(element->getChildElement("BitsValue"));
                for(; node; node = dynamic_cast<const Element*>(node->nextSibling()))
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
                bits.encoding = Encoding(str);
            }

            const Element* descrNode = dynamic_cast<const Element*>(element->getChildElement("BitsName"));
            if (descrNode)
            {
                bits.description = descrNode->innerText();
            }

            const Element* unitNode = dynamic_cast<const Element*>(element->getChildElement("BitsUnit"));
            if (unitNode)
            {
                auto units = unitNode->innerText();
                if (Poco::icompare(units, "M") == 0)
                {
                    bits.units = Units::M;
                }
                else if (Poco::icompare(units, "NM") == 0)
                {
                    bits.units = Units::NM;
                }
                else if (Poco::icompare(units, "FL") == 0)
                {
                    bits.units = Units::FL;
                }
                else if (Poco::icompare(units, "FT") == 0)
                {
                    bits.units = Units::FT;
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

            bits.repeat = repetitive;

            //std::cout << "      " << bits.toString() << " enc " << bits.encoding.toString() << std::endl;
            addPrimitiveItem(codecDescription, bits);
            bitsArray.push_back(bits);
        }
    }

    return bitsArray;
}

ItemDescriptionPtr CodecDeclarationLoader::loadFormatElement(CodecDescription& codecDescription, int id, const std::string& description, const Element& formatElement)
{
    ItemFormat format = ItemFormat(formatElement.nodeName());

    switch (format.toValue())
    {
        case ItemFormat::Fixed:
            return loadFixedDeclaration(codecDescription, id, description, formatElement);

        case ItemFormat::Variable:
            return loadVariableDeclaration(codecDescription, id, description, formatElement);

        case ItemFormat::Repetitive:
            return loadRepetitiveDeclaration(codecDescription, id, description, formatElement);

        case ItemFormat::Compound:
            return loadCompoundDeclaration(codecDescription, id, description, formatElement);

        case ItemFormat::Explicit:
            return loadExplicitDeclaration(codecDescription, id, description, formatElement);

        default:
            throw Exception("CodecDeclarationLoader::loadDataItem(): unknown item type " + format.toString());
    }
}

void CodecDeclarationLoader::addPrimitiveItem(CodecDescription& codecDescription, const BitsDescription& bits)
{
    if (Poco::icompare(bits.name,"FX") == 0 ||
        Poco::icompare(bits.name, "spare") == 0 ||
        Poco::icompare(bits.name, "unused") == 0
    )
        return;

    PrimitiveType type;

    if (bits.effectiveBitsWidth() == 1)
    {
        type = PrimitiveType::Boolean;
    }
    else
    {
        if (bits.scale != 1.0)
        {
            type = PrimitiveType::Real;
        }
        else if (bits.encoding == Encoding::Signed)
        {
            type = PrimitiveType::Integer;
        }
        else if (bits.encoding == Encoding::Unsigned)
        {
            type = PrimitiveType::Unsigned;
        }
        else
        {
            type = PrimitiveType::String;
        }

    }
    codecDescription.addPrimitiveItem(bits.name, PrimitiveItem(bits.name, bits.description, type, bits.repeat));
}

} /* namespace codecDescription */
