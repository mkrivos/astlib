///
/// \package astlib
/// \file CodecRegister.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 9Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "model/CodecDescription.h"

#include <string>
#include <map>

namespace astlib
{

/**
 * Search, register & publish all known codec descriptions.
 */
class CodecRegister
{
public:
    CodecRegister();
    ~CodecRegister();

    void populateCodecsFromDirectory(const std::string& path);

    void addCodec(CodecDescriptionPtr codec);

    CodecDescriptionVector enumerateAllCodecs() const;

    CodecDescriptionVector enumerateCodecsByCategory() const;

private:
    std::map<int, CodecDescriptionPtr> _tableByCategory;
    std::map<std::string, CodecDescriptionPtr> _tableBySignature;
};

} /* namespace astlib */

