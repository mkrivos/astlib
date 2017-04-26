///
/// \package astlib
/// \file JsonValueDecoder::.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 10Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "JsonValueDecoder.h"

namespace astlib
{

void JsonValueDecoder::begin(int cat)
{
    json = new Poco::JSON::Object();
    json->set("category", cat);
}

void JsonValueDecoder::beginItem(const astlib::ItemDescription& uapItem)
{
    Poco::JSON::Object::Ptr item = new Poco::JSON::Object();
    json->set(uapItem.getDescription(), item);
    setScope(item);
}

void JsonValueDecoder::beginRepetitive(size_t count)
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

void JsonValueDecoder::decodeBoolean(const CodecContext& context, bool value, int index)
{
    scope()->set(context.bits.name, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeSigned(const CodecContext& context, Poco::Int64 value, int index)
{
    scope()->set(context.bits.name, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeUnsigned(const CodecContext& context, Poco::UInt64 value, int index)
{
    JsonValueDecoder::scope()->set(context.bits.name, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeReal(const CodecContext& context, double value, int index)
{
    JsonValueDecoder::scope()->set(context.bits.name, Poco::Dynamic::Var(value));
}

void JsonValueDecoder::decodeString(const CodecContext& context, const std::string& value, int index)
{
    JsonValueDecoder::scope()->set(context.bits.name, Poco::Dynamic::Var(value));
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
