///
/// \package astlib
/// \file CodecRegister.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 9Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CodecRegister.h"
#include "CodecDeclarationLoader.h"

#include <Poco/DirectoryIterator.h>
#include <Poco/File.h>
#include <Poco/Path.h>

namespace astlib
{

CodecRegister::CodecRegister()
{
}

CodecRegister::~CodecRegister()
{
}

void CodecRegister::populateCodecsFromDirectory(const std::string& path)
{
    auto dir = Poco::DirectoryIterator(path);
    auto end = Poco::DirectoryIterator();
    CodecDeclarationLoader loader;

    while(dir != end)
    {
        Poco::File file = *dir;
        if (file.isFile())
        {
            Poco::Path filename = file.path();
            if (Poco::startsWith(filename.getBaseName(), std::string("asterix_cat")))
            {
                CodecDescriptionPtr codec = loader.load(file.path());
                if (codec)
                {
                    addCodec(codec);
                }
            }
        }
        ++dir;
    }
}

void CodecRegister::addCodec(CodecDescriptionPtr codec)
{
    if (codec)
    {
        const CategoryDescription& catDesc = codec->getCategoryDescription();
        _tableBySignature[catDesc.toString()] = codec;

        auto currentCodec = _tableByCategory[catDesc.getCategory()];
        if (!currentCodec || currentCodec->getCategoryDescription().getEdition() < catDesc.getEdition())
        {
            _tableByCategory[catDesc.getCategory()] = codec;
        }
    }
}

CodecDescriptionVector CodecRegister::enumerateAllCodecs() const
{
    CodecDescriptionVector enumerations;

    for(auto& record: _tableBySignature)
    {
        enumerations.push_back(record.second);
    }

    return enumerations;
}

CodecDescriptionVector CodecRegister::enumerateCodecsByCategory() const
{
    CodecDescriptionVector enumerations;

    for(auto& record: _tableByCategory)
    {
        enumerations.push_back(record.second);
    }

    return enumerations;
}

} /* namespace astlib */
