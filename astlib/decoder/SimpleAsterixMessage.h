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

#include "ValueDecoder.h"
#include "astlib/AsterixItemCode.h"
#include <Poco/Dynamic/Var.h>
#include <map>


namespace astlib
{

class SimpleAsterixMessage
{
public:
    SimpleAsterixMessage();
    ~SimpleAsterixMessage();

    void addSimpleItem(AsterixItemCode code, Poco::Dynamic::Var&& value);
    bool getBoolean(AsterixItemCode code) const;

private:
    std::map<AsterixItemCode, Poco::Dynamic::Var> _items;
};

} /* namespace astlib */
