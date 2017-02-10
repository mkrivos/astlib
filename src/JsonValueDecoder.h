///
/// \package astlib
/// \file JsonValueDecoder.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 10Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/ValueDecoder.h"

#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/JSONException.h"

#include <deque>

namespace astlib
{

class JsonValueDecoder :
    public TypedValueDecoder
{
    virtual void begin();
    virtual void dataItem(const astlib::ItemDescription& uapItem);
    virtual void beginRepetitive(int count);
    virtual void repetitiveItem(int index);
    virtual void endRepetitive();

    virtual void decodeBoolean(const std::string& identification, bool value);
    virtual void decodeSigned(const std::string& identification, Poco::Int64 value);
    virtual void decodeUnsigned(const std::string& identification, Poco::UInt64 value);
    virtual void decodeReal(const std::string& identification, double value);
    virtual void decodeString(const std::string& identification, const std::string& value);
    virtual void end();

private:
    void setScope(Poco::JSON::Object::Ptr obj);
    void addScope(Poco::JSON::Object::Ptr obj);
    void removeScope();
    Poco::JSON::Object::Ptr scope();

    Poco::JSON::Object::Ptr json;
    std::deque<Poco::JSON::Object::Ptr> scopes;
    Poco::JSON::Array::Ptr localArray;
};

} /* namespace astlib */

