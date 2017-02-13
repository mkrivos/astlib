///
/// \package astlib
/// \file SimpleAsterixMessage.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13. 2. 2017 - 18:54:38
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#include "SimpleAsterixMessage.h"

namespace astlib
{

SimpleAsterixMessage::SimpleAsterixMessage()
{
}

SimpleAsterixMessage::~SimpleAsterixMessage()
{
}

void SimpleAsterixMessage::addSimpleItem(AsterixItemCode code, Poco::Dynamic::Var&& value)
{
    _items[code] = std::move(value);
}

} /* namespace astlib */
