///
/// \package astlib
/// \file JsonValueDecoder::.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 10Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "JsonValueDecoder.h"

namespace astlib
{

void JsonValueDecoder::begin()
{
    json = new Poco::JSON::Object();
}

void JsonValueDecoder::dataItem(const astlib::ItemDescription& uapItem)
{
    Poco::JSON::Object::Ptr item = new Poco::JSON::Object();
    json->set(uapItem.getDescription(), item);
    setScope(item);
}

void JsonValueDecoder::beginRepetitive(int count)
{
    Poco::JSON::Array::Ptr array = localArray = new Poco::JSON::Array();
    scope()->set("array", array);

    Poco::JSON::Object::Ptr item = new Poco::JSON::Object();
    addScope(item);
}

void JsonValueDecoder::repetitiveItem(int index)
{
    Poco::JSON::Object::Ptr item = new Poco::JSON::Object();
    setScope(item);
    localArray->add(item);
}

void JsonValueDecoder::endRepetitive()
{
    removeScope();
}

void JsonValueDecoder::decodeBoolean(const std::string& identification, bool value)
{
    scope()->set(identification, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeSigned(const std::string& identification, Poco::Int64 value)
{
    scope()->set(identification, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeUnsigned(const std::string& identification, Poco::UInt64 value)
{
    JsonValueDecoder::scope()->set(identification, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeReal(const std::string& identification, double value)
{
    JsonValueDecoder::scope()->set(identification, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeString(const std::string& identification, const std::string& value)
{
    JsonValueDecoder::scope()->set(identification, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::end()
{
    json->stringify(std::cout, 2);
    std::cout << std::endl;
    json = nullptr;
    removeScope();
}

void JsonValueDecoder::setScope(Poco::JSON::Object::Ptr obj)
{
    if (scopes.empty())
        scopes.push_back(obj);
    else
        scopes.back() = obj;
}

void JsonValueDecoder::addScope(Poco::JSON::Object::Ptr obj)
{
    scopes.push_back(obj);
}

void JsonValueDecoder::removeScope()
{
    auto array = *scopes.back();
    scopes.pop_back();
}

Poco::JSON::Object::Ptr JsonValueDecoder::scope()
{
    poco_assert(!scopes.empty());
    return scopes.back();
}

} /* namespace astlib */
