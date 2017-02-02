///
/// \package astlib
/// \file CodecDeclarationLoader.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CodecDeclarationLoader.h"
#include "CodecDescription.h"
#include "CategoryDescription.h"
#include "Exception.h"

#include "Poco/XML/XMLStreamParser.h"
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

#include <fstream>

#include "FixedItemDescription.h"
using namespace Poco::XML;

namespace astlib
{

CodecDeclarationLoader::CodecDeclarationLoader()
{
}

CodecDeclarationLoader::~CodecDeclarationLoader()
{
}

CodecDescriptionPtr CodecDeclarationLoader::load(const std::string& filename)
{
    CodecDescriptionPtr codecDescription(new CodecDescription);
    Poco::XML::InputSource src(filename);
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
        throw Poco::DataFormatException("in CodecDeclarationLoader::load() - no 'Category' element at top level");
    }

    loadCategory(*codecDescription, *root);

    return codecDescription;
}

void CodecDeclarationLoader::loadCategory(CodecDescription& codecDescription, const Element& root)
{
    CategoryDescription categoryDescription;

    int cat = Poco::NumberParser::parse(root.getAttribute("id"));
    categoryDescription.setCategory(cat);
    categoryDescription.setEdition(root.getAttribute("ver"));
    categoryDescription.setFamily("ast");
    categoryDescription.setDescription(root.getAttribute("name"));
    codecDescription.addCategoryDescription(categoryDescription);

    for (auto node = root.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeType() == Node::ELEMENT_NODE)
        {
            auto name = element->nodeName();
            std::cout << " " << name << std::endl;
            if (name == "DataItem")
            {
                auto item = loadDataItem(*element);
            }
        }
    }
}

ItemDescriptionPtr CodecDeclarationLoader::loadDataItem(const Element& element)
{
    auto idString = element.getAttribute("id");
    int id = 0;
    if (idString == "SP")
        id = -1;
    else if (idString == "RE")
        id = -2;
    else
        id = Poco::NumberParser::parse(idString);

    auto description = element.getChildElement("DataItemName")->innerText();
    ItemFormat format = ItemFormat(element.getChildElement("DataItemFormat")->innerText());

    switch(format.toValue())
    {
        case ItemFormat::Fixed:
        {
            BitsDescriptionArray bitsArray = loadBitsDeclaration(element);
            ItemDescriptionPtr item(std::make_shared<FixedItemDescription>(id, description, bitsArray));
            return item;
        }

        default:
            throw Exception("CodecDeclarationLoader::loadDataItem(): unknown item type " + format.toString());
    }

    return nullptr;
}

BitsDescriptionArray CodecDeclarationLoader::loadBitsDeclaration(const Element& element)
{
    BitsDescriptionArray bitsArray;
    return bitsArray;
}

} /* namespace codecDescription */
