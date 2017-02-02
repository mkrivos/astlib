///
/// \package astlib
/// \file CodecDeclarationLoaderEra.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CodecDeclarationLoaderEra.h"
#include "CodecDescription.h"
#include "CategoryDescription.h"

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

using namespace Poco::XML;

namespace astlib
{

CodecDeclarationLoaderEra::CodecDeclarationLoaderEra()
{
}

CodecDeclarationLoaderEra::~CodecDeclarationLoaderEra()
{
}

CodecDescriptionPtr CodecDeclarationLoaderEra::load(const std::string& filename)
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

    if (root->nodeName() != "CodingRules")
    {
        throw Poco::DataFormatException("in CodecDeclarationLoaderEra::load() - no 'CodingRules' element at top level");
    }

    loadCodingRules(*codecDescription, *root);

    return codecDescription;
}

void CodecDeclarationLoaderEra::loadCodingRules(CodecDescription& codecDescription, const Element& root)
{
    for (auto node = root.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeType() == Node::ELEMENT_NODE)
        {
            auto name = element->nodeName();
            std::cout << name << std::endl;
            if (name == "Category")
            {
                loadCategory(codecDescription, *element);
            }
        }
    }
}

void CodecDeclarationLoaderEra::loadCategory(CodecDescription& codecDescription, const Element& root)
{
    CategoryDescription categoryDescription;

    int cat = Poco::NumberParser::parse(root.getAttribute("cat"));
    categoryDescription.setCategory(cat);
    categoryDescription.setEdition(root.getAttribute("edition"));
    categoryDescription.setFamily(root.getAttribute("messageHeaderId"));
    categoryDescription.setDescription(root.getAttribute("description"));
    codecDescription.addCategoryDescription(categoryDescription);

    for (auto node = root.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeType() == Node::ELEMENT_NODE)
        {
            auto name = element->nodeName();
            std::cout << "  " << name << std::endl;
            if (name == "Items")
            {
                loadItems(codecDescription, *element);
            }
        }
    }
}

void CodecDeclarationLoaderEra::loadItems(CodecDescription& codecDescription, const Element& root)
{
    for (auto node = root.firstChild(); node; node = node->nextSibling())
    {
        const Element* element = dynamic_cast<Element*>(node);
        if (element && element->nodeType() == Node::ELEMENT_NODE)
        {
            auto name = element->nodeName();
            std::cout << "   " << name << std::endl;
            if (name == "Item")
            {
                auto item = loadItem(*element);
            }
        }
    }
}

ItemDescriptionPtr CodecDeclarationLoaderEra::loadItem(const Element& root)
{

}
} /* namespace codecDescription */
