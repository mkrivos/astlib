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

size_t SimpleAsterixMessage::size() const
{
    return _items.size();
}

void SimpleAsterixMessage::clear()
{
    _items.clear();
}

void SimpleAsterixMessage::addSimpleItem(AsterixItemCode code, Poco::Dynamic::Var&& value)
{
    //std::cout << asterixCodeToSymbol(code) << " = " << Poco::NumberFormatter::formatHex(code.value) << " = " << value.toString() << std::endl;
    _items[code] = std::move(value);
}

bool SimpleAsterixMessage::hasItem(AsterixItemCode code) const
{
    auto iterator = _items.find(code);
    return (iterator != _items.end());
}

bool SimpleAsterixMessage::getBoolean(AsterixItemCode code, bool& value) const
{
    poco_assert(code.type() == PrimitiveType::Boolean);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    value = iterator->second.convert<bool>();
    return true;
}

bool SimpleAsterixMessage::getUnsigned(AsterixItemCode code, Poco::UInt64& value) const
{
    poco_assert(code.type() == PrimitiveType::Unsigned);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    value = iterator->second.convert<Poco::UInt64>();
    return true;
}

bool SimpleAsterixMessage::getSigned(AsterixItemCode code, Poco::Int64& value) const
{
    poco_assert(code.type() == PrimitiveType::Integer);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    value = iterator->second.convert<Poco::Int64>();
    return true;
}

bool SimpleAsterixMessage::getReal(AsterixItemCode code, double& value) const
{
    poco_assert(code.type() == PrimitiveType::Real);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    value = iterator->second.convert<double>();
    return true;
}

bool SimpleAsterixMessage::getString(AsterixItemCode code, std::string& value) const
{
    poco_assert(code.type() == PrimitiveType::String);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    value = iterator->second.convert<std::string>();
    return true;
}

} /* namespace astlib */
