/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2017 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>
#include "astlib/AsterixRecord.h"

using namespace Nan;
// NOLINT(build/namespaces)
using namespace astlib;

class AsterixRecord:
    public ObjectWrap
{
public:
    static NAN_MODULE_INIT(Init)
    {
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("AsterixRecord").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        SetPrototypeMethod(tpl, "getHandle", GetHandle);
        SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);
        SetPrototypeMethod(tpl, "getValue", GetValue);

        constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
        Set(target, Nan::New("AsterixRecord").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

private:
    explicit AsterixRecord(double value = 0) : value_(value)
    {}
    ~AsterixRecord()
    {}

    static NAN_METHOD(New)
    {
        if (info.IsConstructCall())
        {
            double value =
            info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
            AsterixRecord *obj = new AsterixRecord(value);
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
            const int argc = 1;
            v8::Local<v8::Value> argv[argc] =
            {   info[0]};
            v8::Local<v8::Function> cons = Nan::New(constructor());
            info.GetReturnValue().Set(cons->NewInstance(argc, argv));
        }
    }

    static NAN_METHOD(GetHandle)
    {
        AsterixRecord* obj = ObjectWrap::Unwrap<AsterixRecord>(info.Holder());
        info.GetReturnValue().Set(obj->handle());
    }

    static NAN_METHOD(GetHandleConst)
    {
        AsterixRecord const *obj = ObjectWrap::Unwrap<AsterixRecord>(info.Holder());
        info.GetReturnValue().Set(obj->handle());
    }

    static NAN_METHOD(GetValue)
    {
        AsterixRecord* obj = ObjectWrap::Unwrap<AsterixRecord>(info.Holder());
        info.GetReturnValue().Set(obj->value_);
    }

    static inline Persistent<v8::Function> & constructor()
    {
        static Persistent<v8::Function> my_constructor;
        return my_constructor;
    }

    double value_;
};

NODE_MODULE(objectwraphandle, AsterixRecord::Init)
