///
/// \package astlib
/// \file SimpleAsterixMessage.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13. 2. 2017 - 18:54:38
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/AsterixItemCode.h"
#include <Poco/Dynamic/Var.h>
#include <map>
#include <memory>


namespace astlib
{

/**
 * Trivial implementation of AsterixRecord based on std::map.
 */
class SimpleAsterixRecord
{
public:
    SimpleAsterixRecord();
    ~SimpleAsterixRecord();

    void addSimpleItem(AsterixItemCode code, Poco::Dynamic::Var&& value, int index = -1);
    void initializeArray(AsterixItemCode code, size_t size);
    bool hasItem(AsterixItemCode code) const;
    size_t getArraySize(AsterixItemCode code) const;

    bool getBoolean(AsterixItemCode code, bool& value, int index = -1) const;
    bool getUnsigned(AsterixItemCode code, Poco::UInt64& value, int index = -1) const;
    bool getSigned(AsterixItemCode code, Poco::Int64& value, int index = -1) const;
    bool getReal(AsterixItemCode code, double& value, int index = -1) const;
    bool getString(AsterixItemCode code, std::string& value, int index = -1) const;

    std::string toString() const;

    size_t size() const;
    void clear();

private:
    std::map<AsterixItemCode, Poco::Dynamic::Var> _items;
};

using SimpleAsterixRecordPtr = std::shared_ptr<SimpleAsterixRecord>;

} /* namespace astlib */
