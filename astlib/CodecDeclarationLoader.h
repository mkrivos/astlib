///
/// \package astlib
/// \file CodecDeclarationLoader.h
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

class CodecDeclarationLoader
{
public:
    CodecDeclarationLoader();
    ~CodecDeclarationLoader();

    /**
     * Load with Stream parser
     * @param filename
     * @return description object
     */
    CodecDescriptionPtr load(const std::string& filename);

private:
    void loadCategory(CodecDescription& codecDescription, const Poco::XML::Element& root);
    ItemDescriptionPtr loadDataItem(const Poco::XML::Element& root);
    BitsDescriptionArray loadBitsDeclaration(const Poco::XML::Element& element);

};

} /* namespace astlib */

