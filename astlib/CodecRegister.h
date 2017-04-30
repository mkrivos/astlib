///
/// \package astlib
/// \file CodecRegister.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 9Feb.,2017 
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
 * All codecs are stored by signature (codec.toString()) key, i.e. multiple codecs
 * with the same category but different edition are supported.
 */
class ASTLIB_API CodecRegister
{
public:
    CodecRegister();
    ~CodecRegister();

    /**
     * Loads and registers all XML descriptions from directory.
     * @param path
     */
    //void populateCodecsFromDirectory(const std::string& path);

    void initializeCodecs();

    /**
     * Add one codec description.
     * @param codec
     */
    void addCodec(CodecDescriptionPtr codec);

    /**
     * Enumerates all registered codecs (categories and editions).
     * @return
     */
    CodecDescriptionVector enumerateAllCodecs() const;

    /**
     * Enumerates registered codecs for exact categories, i.e. if more codecs for one category
     * is registered, only latest editions are enumerated.
     * @return
     */
    CodecDescriptionVector enumerateAllCodecsByCategory() const;

    /**
     * Enumerate union of all codecs local symbols.
     * @return
     */
    CodecDescription::Dictionary enumerateGlobalSymbols() const;

    //CodecDescriptionVector enumerateCodecsByCategory(int category) const;

    /**
     * Return latest edition codec for concrete category.
     * @param category
     * @return codec, or nullptr if no registered codec for this category.
     */
    CodecDescriptionPtr getLatestCodecForCategory(int category) const;

    CodecDescriptionPtr getCodecForSignature(const std::string& fullName) const;

private:
    std::map<int, CodecDescriptionPtr> _tableByCategory;
    std::map<std::string, CodecDescriptionPtr> _tableBySignature;
};

} /* namespace astlib */

