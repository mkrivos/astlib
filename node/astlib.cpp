#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <v8pp/convert.hpp>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <v8pp/function.hpp>
#include <v8pp/object.hpp>

#include "astlib/SimpleAsterixRecord.h"
#include "astlib/CodecRegister.h"
#include "astlib/Exception.h"
#include "astlib/decoder/SimpleValueDecoder.h"
#include "astlib/decoder/BinaryAsterixDecoder.h"
#include "astlib/encoder/SimpleValueEncoder.h"
#include "astlib/encoder/BinaryAsterixEncoder.h"

#include <type_traits> // C++0x
#include <exception>
#include <iostream>

static int itemType(int value)
{
    return (value>>24) & 0xF;
}

template<typename T>
T fromV8Value(v8::Handle<v8::Value> value)
{
    if (std::is_same<T, std::string>::value)
    {
        v8::String::Utf8Value stringValue(value);
        return std::string(*stringValue, stringValue.length());
    }
    else if (std::is_same<T, int>::value)
        return value->IntegerValue();
    else
        throw new std::bad_cast();
}

std::string fromV8String(v8::Handle<v8::Value> value)
{
    v8::String::Utf8Value stringValue(value);
    return std::string(*stringValue, stringValue.length());
}

/*
v8::Handle<v8::Value> toV8Value(v8::Isolate* isolate, std::string& value)
{
    return v8::String::New(isolate, value.c_str(), value.length());
}

v8::Handle<v8::Value> toV8Object(v8::Isolate* isolate, int value)
{
    return v8::Number::New(isolate, value);
}
*/
template<typename T>
class Wrapper
{
public:
    explicit Wrapper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
    }

    T value;
};

using AsterixRecordWrapper = Wrapper<astlib::SimpleAsterixRecord>;
using CodecWrapper = Wrapper<astlib::CodecDescriptionPtr>;

static astlib::CodecRegister codecRegister;
static astlib::CodecDescriptionVector codecDescriptions;

static void loadCodecs()
{
    if (codecDescriptions.empty())
    {
        codecRegister.populateCodecsFromDirectory("../specs");
        codecDescriptions = codecRegister.enumerateAllCodecsByCategory();
    }
}

// TODO init kde sa nacitaju kodeky, error ak ziadny nenajde

v8::Handle<v8::Object> createAsterixRecord(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    AsterixRecordWrapper* obj = new AsterixRecordWrapper(args);
    return v8pp::class_<AsterixRecordWrapper>::import_external(args.GetIsolate(), obj);
}

v8::Handle<v8::Array> enumerateAllCodecs()
{
    loadCodecs();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    // We will be creating temporary handles so we use a handle scope.
    v8::EscapableHandleScope handleScope(isolate);
    v8::Local < v8::Array > array = v8::Array::New(isolate, 2);

    int index = 0;
    for (auto codec : codecDescriptions)
    {
        array->Set(index++, v8::String::NewFromUtf8(isolate, codec->getCategoryDescription().toString().c_str()));
    }

    return handleScope.Escape(array);
}

// AsterixRecord[] decodeAsterixBuffer(codecName, Buffer, Policy);
v8::Handle<v8::Value> decodeAsterixBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    loadCodecs();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::EscapableHandleScope handleScope(isolate);

    std::string fullName = fromV8String(args[0]);

    astlib::CodecDescriptionPtr codec = codecRegister.getCodecForSignature(fullName);

    if (codec)
    {
        class MySimpleValueDecoder: public astlib::SimpleValueDecoder
        {
        public:
            virtual void onMessageDecoded(astlib::SimpleAsterixRecordPtr ptr)
            {
                msgs.push_back(ptr);
            }

            std::vector<astlib::SimpleAsterixRecordPtr> msgs;
        } myDecoder;

        astlib::Byte* buf = (astlib::Byte*) node::Buffer::Data(args[1]);
        size_t bytes = node::Buffer::Length(args[1]);
std::cout << "dec " << fullName << " len " << bytes << std::endl;
        astlib::BinaryAsterixDecoder decoder;

        try
        {
            decoder.decode(*codec, myDecoder, buf, bytes);
        }
        catch(astlib::Exception& e)
        {
            std::cerr << e.displayText() << std::endl;
        }

        if (myDecoder.msgs.size())
        {
            //zakoduj pole
        }
    }

    return handleScope.Escape(v8::Null(isolate)); // v8::Object::New(isolate)
}

// Buffer encodeAsterixRecord(codecName, AsterixRecord, Policy);
v8::Handle<v8::Value> encodeAsterixRecord(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    loadCodecs();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::EscapableHandleScope handleScope(isolate);

    std::string fullName = fromV8String(args[0]);

    astlib::CodecDescriptionPtr codec = codecRegister.getCodecForSignature(fullName);

    if (codec)
    {
        std::vector<astlib::Byte> buffer;
        astlib::BinaryAsterixEncoder encoder;
/*
        try
        {
            astlib::SimpleValueEncoder valueEncoder;
            encoder.encode(*codec, valueEncoder, buffer);
        }
        catch(astlib::Exception& e)
        {
            std::cerr << e.displayText() << std::endl;
        }
        */
    }

    return handleScope.Escape(v8::Null(isolate)); // v8::Object::New(isolate)
}

std::string toString(AsterixRecordWrapper& obj)
{
    std::string value(obj.value.toString());
    return value;
}

bool hasItem(AsterixRecordWrapper& obj, int code)
{
    return obj.value.hasItem(code);
}

void allocateArray(AsterixRecordWrapper& obj, int code, int size)
{
    return obj.value.initializeArray(code, size);
}

double getNumberAt(AsterixRecordWrapper& obj, int code, int index)
{
    double value;
    Poco::Int64 value1 = 0;
    Poco::UInt64 value2 = 0;

    switch(itemType(code))
    {
        case astlib::PrimitiveType::Real:
            obj.value.getReal(code, value, index);
            break;

        case astlib::PrimitiveType::Integer:
            obj.value.getSigned(code, value1, index);
            value = value1;
            break;

        case astlib::PrimitiveType::Unsigned:
            obj.value.getUnsigned(code, value2, index);
            value = value2;
            break;

        default:
            throw std::bad_cast();
    }

    return value;
}

double getNumber(AsterixRecordWrapper& obj, int code)
{
    return getNumberAt(obj, code, -1);
}

void setNumberAt(AsterixRecordWrapper& obj, int code, double value, int index)
{
    switch(itemType(code))
    {
        case astlib::PrimitiveType::Real:
            obj.value.setItem(code, value, index);
            break;

        case astlib::PrimitiveType::Integer:
            obj.value.setItem(code, Poco::Int64(value), index);
            break;

        case astlib::PrimitiveType::Unsigned:
            obj.value.setItem(code, Poco::UInt64(value), index);
            break;

        default:
            throw std::bad_cast();
    }
}

void setNumber(AsterixRecordWrapper& obj, int code, double value)
{
    setNumberAt(obj, code, value, -1);
}

void setString(AsterixRecordWrapper& obj, int code, std::string value)
{
    obj.value.setItem(code, value);
}

void setStringAt(AsterixRecordWrapper& obj, int code, std::string value, int index)
{
    obj.value.setItem(code, value, index);
}

std::string getString(AsterixRecordWrapper& obj, int code)
{
    std::string value;
    obj.value.getString(code, value);
    return value;
}

std::string getStringAt(AsterixRecordWrapper& obj, int code, int index)
{
    std::string value;
    obj.value.getString(code, value, index);
    return value;
}

void setBoolean(AsterixRecordWrapper& obj, int code, bool value)
{
    obj.value.setItem(code, value);
}

bool getBoolean(AsterixRecordWrapper& obj, int code)
{
    bool value = false;
    obj.value.getBoolean(code, value);
    return value;
}

void setBooleanAt(AsterixRecordWrapper& obj, int code, bool value, int index)
{
    obj.value.setItem(code, value, index);
}

bool getBooleanAt(AsterixRecordWrapper& obj, int code, int index)
{
    bool value = false;
    obj.value.getBoolean(code, value, index);
    return value;
}

// TODO: ostatne gettery pre record

void InitAll(v8::Handle<v8::Object> exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    v8pp::class_<AsterixRecordWrapper> MyObject_class(isolate);

    v8pp::module addon(isolate);
    addon.set("MyObject", MyObject_class);
    addon.set("createAsterixRecord", &createAsterixRecord);
    addon.set("enumerateAllCodecs", &enumerateAllCodecs);

    addon.set("decodeAsterixBuffer", &decodeAsterixBuffer);
    addon.set("encodeAsterixRecord", &encodeAsterixRecord);

    addon.set("hasItem", &hasItem);
    addon.set("allocateArray", &allocateArray);
    addon.set("setNumber", &setNumber);
    addon.set("getNumber", &getNumber);
    addon.set("setNumberAt", &setNumberAt);
    addon.set("getNumberAt", &getNumberAt);
    addon.set("setString", &setString);
    addon.set("getString", &getString);
    addon.set("setStringAt", &setStringAt);
    addon.set("getStringAt", &getStringAt);
    addon.set("setBoolean", &setBoolean);
    addon.set("getBoolean", &getBoolean);
    addon.set("setBooleanAt", &setBooleanAt);
    addon.set("getBooleanAt", &getBooleanAt);
    addon.set("toString", &toString);

    exports->SetPrototype(addon.new_instance());

    node::AtExit([](void* param)
    {
        v8pp::cleanup(static_cast<v8::Isolate*>(param));
    }, isolate);
}

NODE_MODULE(addon, InitAll)
