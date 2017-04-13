///
/// \package astlib
/// \file TypedValueDecoder.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 8Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "TypedValueDecoder.h"
#include "ByteUtils.h"
#include "astlib/AsterixItemDictionary.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include <iostream>

namespace astlib
{

void TypedValueDecoder::decode(const CodecContext& ctx, Poco::UInt64 value, int index)
{
    AsterixItemCode code = ctx.bits.code;

    //if (!code.value) std::cout << "ZERO " << ctx.bits.toString() << std::endl;

    if (index == -1 && code.isArray())
    {
        throw Exception("TypedValueDecoder::decode: " + asterixCodeToSymbol(code) + " array expects an index");
    }

    if (index != -1 && !code.isArray())
    {
        throw Exception("TypedValueDecoder::decode: " + asterixCodeToSymbol(code) + " scalar value doesn't expects an index");
    }

    Encoding::ValueType encoding = ctx.bits.encoding.toValue();

    switch(code.type())
    {
        case PrimitiveType::Boolean:
            decodeBoolean(ctx, bool(value), index);
            break;

        case PrimitiveType::Real:
        {
            double unit = 1.0;

            if (ctx.policy.normalizeValues)
            {
                switch(ctx.bits.units.toValue())
                {
                    case Units::FT:
                        unit = 0.3048;
                        break;
                    case Units::NM:
                        unit = 1852.0;
                        break;
                    case Units::FL:
                        unit = 0.3048 * 100.0;
                        break;
                }
            }

            if (encoding == Encoding::Unsigned)
            {
                decodeReal(ctx, value * ctx.bits.scale * unit, index);
            }
            else
            {
                decodeReal(ctx, ByteUtils::toSigned(value, ctx.width) * ctx.bits.scale * unit, index);
            }
            break;
        }

        case PrimitiveType::Integer:
            decodeSigned(ctx, ByteUtils::toSigned(value, ctx.width), index);
            break;

        case PrimitiveType::Unsigned:
            if (encoding == Encoding::Octal)
                decodeUnsigned(ctx, ByteUtils::oct2dec(value), index);
            else
                decodeUnsigned(ctx, value, index);
            break;

        default:
        {
            switch (encoding)
            {
                case Encoding::Ascii:
                    decodeString(ctx, "", index);
                    break;
                case Encoding::Octal:
                    decodeUnsigned(ctx, ByteUtils::oct2dec(value), index);
                    break;
                case Encoding::SixBitsChar:
                    decodeString(ctx, ByteUtils::fromSixBitString((const Byte*)&value), index);
                    break;
                case Encoding::Hex:
                    decodeString(ctx, Poco::NumberFormatter::formatHex(value, ctx.width/8*2), index);
                    break;
            }
            break;
        }
    }
}

}


