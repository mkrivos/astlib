#include <v8.h>
#include <node.h>
#include <v8pp/convert.hpp>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <v8pp/function.hpp>
#include <v8pp/object.hpp>

#include "astlib/SimpleAsterixRecord.h"
#include "astlib/CodecRegister.h"
#include "astlib/Exception.h"


template <typename T>
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

v8::Handle<v8::Object> createAsterixRecord(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    AsterixRecordWrapper* obj = new AsterixRecordWrapper(args);
    return v8pp::class_<AsterixRecordWrapper>::import_external(args.GetIsolate(), obj);
}

v8::Handle<v8::Array> enumerateAllCodecs()
{
    astlib::CodecRegister codecRegister;
    codecRegister.populateCodecsFromDirectory("../specs");
    auto codecs = codecRegister.enumerateAllCodecsByCategory();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    // We will be creating temporary handles so we use a handle scope.
    v8::EscapableHandleScope handleScope(isolate);
    v8::Local<v8::Array> array = v8::Array::New(isolate, 2);

    int index = 0;
    for(auto codec: codecs)
    {
        array->Set(index++, v8::String::NewFromUtf8(isolate, codec->getCategoryDescription().toString().c_str()));
    }

    return handleScope.Escape(array);
}

v8::Handle<v8::Object> createCodecBySignature(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    astlib::CodecRegister codecRegister;
    codecRegister.populateCodecsFromDirectory("../specs");
    auto codec = codecRegister.getCodecForSignature("");

    CodecWrapper* obj = new CodecWrapper(args);
    return v8pp::class_<CodecWrapper>::import_external(args.GetIsolate(), obj);
}

std::string toString(AsterixRecordWrapper& obj)
{
    return obj.value.toString();
}

bool hasItem(AsterixRecordWrapper& obj, int code)
{
    return obj.value.hasItem(code);
}

void setNumberItem(AsterixRecordWrapper& obj, int code, double value)
{
    obj.value.setItem(code, value);
}

void setStringItem(AsterixRecordWrapper& obj, int code, std::string value)
{
    obj.value.setItem(code, value);
}

void setBooleanItem(AsterixRecordWrapper& obj, int code, bool value)
{
    obj.value.setItem(code, value);
}

bool getBooleanItem(AsterixRecordWrapper& obj, int code)
{
    bool value = false;
    obj.value.getBoolean(code, value);
    return value;
}

void InitAll(v8::Handle<v8::Object> exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    v8pp::class_<AsterixRecordWrapper> MyObject_class(isolate);

    v8pp::module addon(isolate);
    addon.set("MyObject", MyObject_class);
    addon.set("createAsterixRecord", &createAsterixRecord);
    addon.set("enumerateAllCodecs", &enumerateAllCodecs);
    addon.set("createCodecBySignature", &createCodecBySignature);

    addon.set("hasItem", &hasItem);
    addon.set("setNumberItem", &setNumberItem);
    addon.set("setStringItem", &setStringItem);
    addon.set("setBooleanItem", &setBooleanItem);
    addon.set("getBooleanItem", &getBooleanItem);
    addon.set("toString", &toString);

    exports->SetPrototype(addon.new_instance());

    node::AtExit([](void* param)
    {
        v8pp::cleanup(static_cast<v8::Isolate*>(param));
    }, isolate);
}

NODE_MODULE(addon, InitAll)
