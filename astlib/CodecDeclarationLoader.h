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

#include "model/CodecDescription.h"
#include "model/ItemDescription.h"
#include "model/Fixed.h"

#include <Poco/DOM/Element.h>
#include <string>

namespace astlib
{

/**
 * Class for loading Asterix description based on 'ASTERIXED' format.
 */
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
    void loadUap(CodecDescription& codecDescription, const Poco::XML::Element& element);
    ItemDescriptionPtr loadFixedDeclaration(int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadVariableDeclaration(int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadRepetitiveDeclaration(int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadCompoundDeclaration(int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadExplicitDeclaration(int id, const std::string& description, const Poco::XML::Element& element);
    BitsDescriptionArray loadBitsDeclaration(const Poco::XML::Element& element);
    Fixed loadFixed(const Poco::XML::Element& element);
    ItemDescriptionPtr loadFormatElement(int id, const std::string& description, const Poco::XML::Element& element);
};

} /* namespace astlib */

