///
/// \package astlib
/// \file CodecDeclarationLoaderEra.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "model/CodecDescription.h"
#include "model/ItemDescription.h"

#include <Poco/DOM/Element.h>
#include <string>

namespace astlib
{

/**
 * Class for loading Asterix description based on 'ERA' format.
 */
class CodecDeclarationLoaderEra
{
public:
    CodecDeclarationLoaderEra();
    ~CodecDeclarationLoaderEra();

    /**
     * Load with Stream parser
     * @param filename
     * @return description object
     */
    CodecDescriptionPtr load(const std::string& filename);

private:
    void loadCodingRules(CodecDescription& codecDescription, const Poco::XML::Element& root);
    void loadCategory(CodecDescription& codecDescription, const Poco::XML::Element& root);
    void loadItems(CodecDescription& codecDescription, const Poco::XML::Element& root);
    ItemDescriptionPtr loadItem(const Poco::XML::Element& root);
};

} /* namespace astlib */

