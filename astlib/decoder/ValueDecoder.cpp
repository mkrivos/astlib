///
/// \package astlib
/// \file ValueDecoder.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 8Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "ValueDecoder.h"
#include "ByteUtils.h"

#include <Poco/NumberFormatter.h>
#include <iostream>

namespace astlib
{

void TypedValueDecoder::decode(const CodecContext& ctx, Poco::UInt64 value)
{
    Encoding::ValueType encoding = ctx.bits.encoding.toValue();

    switch(ctx.bits.code.type())
    {
        case PrimitiveType::Boolean:
            decodeBoolean(ctx, bool(value));
            break;

        case PrimitiveType::Real:
        {
            double unit = 1.0;

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

            if (encoding == Encoding::Unsigned)
            {
                decodeReal(ctx, value * ctx.bits.scale * unit);
            }
            else
            {
                decodeReal(ctx, ByteUtils::toSigned(value, ctx.width) * ctx.bits.scale * unit);
            }
            break;
        }

        case PrimitiveType::Integer:
            decodeSigned(ctx, ByteUtils::toSigned(value, ctx.width));
            break;

        case PrimitiveType::Unsigned:
            decodeUnsigned(ctx, value);
            break;

        default:
        {
            switch (encoding)
            {
                case Encoding::Ascii:
                    decodeString(ctx, "");
                    break;
                case Encoding::Octal:
                    decodeUnsigned(ctx, ByteUtils::oct2dec(value));
                    break;
                case Encoding::SixBitsChar:
                    decodeString(ctx, ByteUtils::fromSixBitString((const Byte*)&value));
                    break;
                case Encoding::Hex:
                    decodeString(ctx, Poco::NumberFormatter::formatHex(value));
                    break;
            }
            break;
        }
    }
}

}


