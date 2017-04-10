///
/// \package astlib
/// \file CodecDeclarationLoader.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 31Jan.,2017 
/// \brief Formal XML Description Loader (ASTERIXED format)
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "PrimitiveItem.h"
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
class ASTLIB_API CodecDeclarationLoader
{
public:
    CodecDeclarationLoader(bool verbose = false);
    ~CodecDeclarationLoader();

    /**
     * Load with Stream parser
     * @param filename
     * @return description object
     */
    CodecDescriptionPtr load(const std::string& filename);

private:
    void loadCategory(CodecDescription& codecDescription, const Poco::XML::Element& root);
    ItemDescriptionPtr loadDataItem(CodecDescription& codecDescription, const Poco::XML::Element& root);
    void loadUap(CodecDescription& codecDescription, const Poco::XML::Element& element);
    ItemDescriptionPtr loadFixedDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadVariableDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadRepetitiveDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadCompoundDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Poco::XML::Element& element);
    ItemDescriptionPtr loadExplicitDeclaration(CodecDescription& codecDescription, int id, const std::string& description, const Poco::XML::Element& element);
    BitsDescriptionArray loadBitsDeclaration(CodecDescription& codecDescription, const Poco::XML::Element& element, bool repetitive);
    Fixed loadFixed(CodecDescription& codecDescription, const Poco::XML::Element& element, bool repetitive = false);
    ItemDescriptionPtr loadFormatElement(CodecDescription& codecDescription, int id, const std::string& description, const Poco::XML::Element& element);
    void addPrimitiveItem(CodecDescription& codecDescription, const BitsDescription& bits);

    bool _verbose = true;
    int _category = 0;
};

} /* namespace astlib */

