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
#include "Poco/XML/XMLStreamParser.h"
#include <string>

namespace astlib
{

class CodecDeclarationLoader
{
public:
    CodecDeclarationLoader();
    ~CodecDeclarationLoader();

    /**
     *
     * @param filename
     * @return
     */
    CodecDescriptionPtr load(const std::string& filename);
};

} /* namespace astlib */

