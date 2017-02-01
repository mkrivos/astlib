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

CodecDeclarationLoader::CodecDeclarationLoader()
{
}

CodecDeclarationLoader::~CodecDeclarationLoader()
{
}

CodecDescriptionPtr CodecDeclarationLoader::load(const std::string& filename)
{
    CodecDescriptionPtr codecDescription(new CodecDescription);

    try
    {
        // Enable stream exceptions so that io failures are reported
        // as stream rather than as parsing exceptions.
        //
        std::ifstream ifs;
        ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        ifs.open(filename, std::ifstream::in | std::ifstream::binary);

        // Configure the parser to receive attributes as events as well
        // as to receive prefix-namespace mappings (namespace declarations
        // in XML terminology).
        //
        XMLStreamParser parser(ifs,
            filename,
            XMLStreamParser::RECEIVE_DEFAULT |
            XMLStreamParser::RECEIVE_ATTRIBUTE_MAP |
            XMLStreamParser::RECEIVE_NAMESPACE_DECLS);

        std::string currentElement;

        for (XMLStreamParser::EventType e(parser.next()); e != XMLStreamParser::EV_EOF; e = parser.next())
        {
            auto event = parser.peek();
            if(event == XMLStreamParser::EV_START_ELEMENT)
            {
                currentElement = parser.getQName().localName();
                std::cout << currentElement << std::endl;
                if (currentElement == "CodingRules")
                {

                }
                else if (currentElement == "Parameter")
                {
                    parser.nextExpect(Poco::XML::XMLStreamParser::EV_START_ELEMENT, "Parameter", Poco::XML::Content::Simple);

                    auto name = parser.attribute(QName("name"));
                    auto valueType = parser.attribute(QName("valueType"));
                }
                else if (currentElement == "Category")
                {
                    parser.nextExpect(Poco::XML::XMLStreamParser::EV_START_ELEMENT, "Category", Poco::XML::Content::Complex);

                    CategoryDescription categoryDescription;
                    int cat = parser.attribute<int>(QName("cat"));
                    categoryDescription.setCategory(cat);
                    codecDescription->addCategoryDescription(categoryDescription);
                }
                else if (currentElement == "Uint")
                {
                    parser.nextExpect(Poco::XML::XMLStreamParser::EV_START_ELEMENT, "Uint", Poco::XML::Content::Complex);

                    auto description = parser.attribute(QName("description"));
                }
                else if (currentElement == "Values")
                {
                    parser.nextExpect(Poco::XML::XMLStreamParser::EV_START_ELEMENT, "Values", Poco::XML::Content::Complex);

                    auto link = parser.attribute(QName("ibLink"));
                }
            }
        }
    }
    catch (const std::ios_base::failure& e)
    {
        throw Poco::IOException(e.what());
    }

    return codecDescription;
}

CodecDescriptionPtr CodecDeclarationLoader::load2(const std::string& filename)
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
        throw Poco::DataFormatException("in CodecDeclarationLoader::load() - no 'CodingRules' element at top level");
    }

    loadCodingRules(*codecDescription, *root);

    return codecDescription;
}

void CodecDeclarationLoader::loadCodingRules(CodecDescription& codecDescription, const Element& root)
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

void CodecDeclarationLoader::loadCategory(CodecDescription& codecDescription, const Element& root)
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

void CodecDeclarationLoader::loadItems(CodecDescription& codecDescription, const Element& root)
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
                //auto item = loadItem(*element);
            }
        }
    }
}

} /* namespace codecDescription */
