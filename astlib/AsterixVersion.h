///
/// \package astlib
/// \file AsterixVersion.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date Apr 2, 2015 - 11:40:47 AM
/// \brief definicia typu
///
/// (C) Copyright 2015 R-SYS,s.r.o
/// All rights reserved.
///


#pragma once

#include <Poco/NumberParser.h>
#include <Poco/StringTokenizer.h>
#include <string>
#include <vector>

namespace astlib
{

/**
 * Dataholder pre popis verzie asterixu vo forme MAJOR.MINOR,
 * verzia sa sklada z dvoch integer cisel.
 */
struct AsterixVersion
{
    AsterixVersion(int major=0, int minor=0) :
        majorVersion(major),
        minorVersion(minor)
    {
    }

    AsterixVersion(const std::string& versionString)
    {
        Poco::StringTokenizer tokenizer(versionString, ".");
        majorVersion = Poco::NumberParser::parse(tokenizer[0]);
        minorVersion = Poco::NumberParser::parse(tokenizer[1]);
    }

    /// Specialna hodnota verzie s vyznamom "posledna dostupna verzia".
    static AsterixVersion Latest;

    int majorVersion;
    int minorVersion;

    std::string toString() const
    {
        return std::to_string(majorVersion)  + "." + std::to_string(minorVersion);
    }
};

inline bool operator == (const AsterixVersion left, const AsterixVersion right)
{
    if (left.majorVersion == right.majorVersion)
        if (left.minorVersion == right.minorVersion)
        return true;
    return false;
}

inline bool operator != (const AsterixVersion left, const AsterixVersion right)
{
    return ! (left == right);
}

inline bool operator > (const AsterixVersion left, const AsterixVersion right)
{
    if (left.majorVersion > right.majorVersion)
        return true;

    if (left.majorVersion == right.majorVersion)
        if (left.minorVersion > right.minorVersion)
        return true;

    return false;
}

inline bool operator < (const AsterixVersion left, const AsterixVersion right)
{
    if (left.majorVersion < right.majorVersion)
        return true;

    if (left.majorVersion == right.majorVersion)
        if (left.minorVersion < right.minorVersion)
        return true;

    return false;
}

inline bool operator >= (const AsterixVersion left, const AsterixVersion right)
{
    if (left > right || left == right)
        return true;

    return false;
}

inline bool operator <= (const AsterixVersion left, const AsterixVersion right)
{
    if (left < right || left == right)
        return true;

    return false;
}

using AsterixVersionArray = std::vector<AsterixVersion>;

/**
 * Popisovac kategorie asterixu pre urcity rozsah min a max verziu.
 * Jedna kategoria asterixu moze popisovat niekolko roznych verzii specifikacii.
 */
struct AsterixCodecDescriptor
{
    AsterixCodecDescriptor(unsigned char category, AsterixVersion  minVersion, AsterixVersion maxVersion) :
        minimum(minVersion),
        maximum(maxVersion),
        category(category)
    {
    }

    AsterixVersion minimum;
    AsterixVersion maximum;
    AsterixVersion ref;
    unsigned char category = 0;
};

using AsterixDescriptorArray = std::vector<AsterixCodecDescriptor>;

}
