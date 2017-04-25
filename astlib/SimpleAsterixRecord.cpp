///
/// \package astlib
/// \file SimpleAsterixMessage.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13. 2. 2017 - 18:54:38
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#include "SimpleAsterixRecord.h"

#include <Poco/Dynamic/Struct.h>

#include "AsterixItemDictionary.h"
#include "Exception.h"

#include <sstream>
#include <iostream>

namespace astlib
{

SimpleAsterixRecord::SimpleAsterixRecord()
{
}

SimpleAsterixRecord::~SimpleAsterixRecord()
{
}

size_t SimpleAsterixRecord::size() const
{
    return _items.size();
}

void SimpleAsterixRecord::clear()
{
    _items.clear();
}

void SimpleAsterixRecord::initializeArray(AsterixItemCode code, size_t size)
{
    _items[code] = Poco::Dynamic::Var(std::vector<Poco::Dynamic::Var>(size));
}

size_t SimpleAsterixRecord::getArraySize(AsterixItemCode code) const
{
    auto iterator = _items.find(code);
    if (iterator != _items.end())
        return iterator->second.size();

    return 0;
    //throw Exception("SimpleAsterixRecord::getArraySize(): invalid access " + asterixCodeToSymbol(code));
}

void SimpleAsterixRecord::setItem(AsterixItemCode code, Poco::Dynamic::Var&& value, int index)
{
    //std::cout << asterixCodeToSymbol(code) << " = " << Poco::NumberFormatter::formatHex(code.value) << " = " << value.toString() << std::endl;
    if (index == -1)
    {
        _items[code] = std::move(value);
    }
    else
    {
        // FIXME: velkost pola musi byt riesena inak a skor
        //if (index == 0) initializeArray(code, 4);
        _items[code][index] = std::move(value);
    }
}

bool SimpleAsterixRecord::hasItem(AsterixItemCode code) const
{
    auto iterator = _items.find(code);
    return (iterator != _items.end());
}

bool SimpleAsterixRecord::getBoolean(AsterixItemCode code, bool& value, int index) const
{
    poco_assert(code.type() == PrimitiveType::Boolean);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    if (index == -1)
    {
        value = iterator->second.convert<bool>();
    }
    else
    {
        poco_assert(iterator->second.isArray());
        value = iterator->second[index].convert<bool>();
    }
    return true;
}

bool SimpleAsterixRecord::getUnsigned(AsterixItemCode code, Poco::UInt64& value, int index) const
{
    poco_assert(code.type() == PrimitiveType::Unsigned);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    if (index == -1)
    {
        value = iterator->second.convert<Poco::UInt64>();

    }
    else
    {
        poco_assert(iterator->second.isArray());
        value = iterator->second[index].convert<Poco::UInt64>();
    }
    return true;
}

bool SimpleAsterixRecord::getSigned(AsterixItemCode code, Poco::Int64& value, int index) const
{
    poco_assert(code.type() == PrimitiveType::Integer);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    if (index == -1)
    {
        value = iterator->second.convert<Poco::Int64>();
    }
    else
    {
        poco_assert(iterator->second.isArray());
        value = iterator->second[index].convert<Poco::Int64>();
    }
    return true;
}

bool SimpleAsterixRecord::getReal(AsterixItemCode code, double& value, int index) const
{
    poco_assert(code.type() == PrimitiveType::Real);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    if (index == -1)
    {
        value = iterator->second.convert<double>();
    }
    else
    {
        poco_assert(iterator->second.isArray());
        value = iterator->second[index].convert<double>();
    }
    return true;
}

bool SimpleAsterixRecord::getString(AsterixItemCode code, std::string& value, int index) const
{
    poco_assert(code.type() == PrimitiveType::String);

    auto iterator = _items.find(code);
    if (iterator == _items.end())
        return false;

    if (index == -1)
    {
        value = iterator->second.convert<std::string>();
    }
    else
    {
        poco_assert(iterator->second.isArray());
        value = iterator->second[index].convert<std::string>();
    }
    return true;
}

std::string SimpleAsterixRecord::toString() const
{
    std::stringstream stream;

    for(auto& entry: _items)
        stream << asterixCodeToSymbol(entry.first) << " = " << entry.second.toString() << std::endl;
    return stream.str();
}

std::string SimpleAsterixRecord::toJson() const
{
    std::stringstream stream;
    bool first = true;

    stream << '{';
    for (auto& item: _items)
    {
        AsterixItemCode code = item.first;

        if (!code.isValid())
            continue;

        if (!first)
            stream << ',';

        stream << '\"' << asterixCodeToSymbol(code) << "\":" << Poco::Dynamic::Var::toString(item.second);
        first = false;
    }
    stream << '}';
    return stream.str();
}

SimpleAsterixRecordPtr SimpleAsterixRecord::fromJson(const std::string& json)
{
    Poco::Dynamic::Var object(Poco::Dynamic::Var::parse(json));
    poco_assert(object.isStruct());
    //std::cout << Poco::Dynamic::Var::toString(object) << std::endl;

    const Poco::DynamicStruct structObject = object.extract<Poco::DynamicStruct>();
    SimpleAsterixRecordPtr instance = std::make_shared<SimpleAsterixRecord>();

    for(auto& record: structObject)
    {
        // TODO: kontrolovat ci je symbol znamy!!!
        instance->_items[asterixSymbolToCode(record.first)] = record.second;
    }

    return instance;
}

} /* namespace astlib */
