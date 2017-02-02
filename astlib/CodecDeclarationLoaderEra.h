///
/// \package astlib
/// \file CodecDeclarationLoaderEra.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "CodecDescription.h"
#include "ItemDescription.h"

#include <Poco/DOM/Element.h>
#include <string>

namespace astlib
{

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

