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

#include <Poco/XML/XMLStreamParser.h>
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
        XMLStreamParser p(ifs,
            filename,
            XMLStreamParser::RECEIVE_DEFAULT |
            XMLStreamParser::RECEIVE_ATTRIBUTES_EVENT |
            XMLStreamParser::RECEIVE_NAMESPACE_DECLS);

        for (XMLStreamParser::EventType e(p.next()); e != XMLStreamParser::EV_EOF; e = p.next())
        {
            switch (e)
            {
            case XMLStreamParser::EV_START_ELEMENT:
            {
                //s.startElement(p.getQName());
                break;
            }
            case XMLStreamParser::EV_END_ELEMENT:
            {
                //s.endElement();
                break;
            }
            case XMLStreamParser::EV_START_NAMESPACE_DECL:
            {
                //s.namespaceDecl(p.namespace_(), p.prefix());
                break;
            }
            case XMLStreamParser::EV_END_NAMESPACE_DECL:
            {
                // There is nothing in XML that indicates the end of namespace
                // declaration since it is scope-based.
                //
                break;
            }
            case XMLStreamParser::EV_START_ATTRIBUTE:
            {
                //s.startAttribute(p.getQName());
                break;
            }
            case XMLStreamParser::EV_END_ATTRIBUTE:
            {
                //s.endAttribute();
                break;
            }
            case XMLStreamParser::EV_CHARACTERS:
            {
                //s.characters(p.value());
                break;
            }
            case XMLStreamParser::EV_EOF:
            {
                // Handled in the for loop.
                //
                break;
            }
            }
        }
    }
    catch (const std::ios_base::failure& e)
    {
        throw Poco::IOException(e.what());
    }

    return nullptr;
}

} /* namespace astlib */
