///
/// \package astlib
/// \file TypedValueEncoder.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "TypedValueEncoder.h"
#include "astlib/ByteUtils.h"
#include "astlib/AsterixItemDictionary.h"
#include "astlib/Exception.h"
#include <Poco/NumberParser.h>
#include <iostream>

namespace astlib
{

bool TypedValueEncoder::encode(const CodecContext& ctx, Poco::UInt64& value, int index)
{
    AsterixItemCode code = ctx.bits.code;

/*
    if (code.value == TRAJECTORY_INTENT_TCP_LONGITUDE_CODE.value)
    {
        value = 0x123456;
        return true;
    }
*/
    if (!code.value)
    {
        //std::cout << "Skipped " << ctx.bits.toString() << std::endl;
        return false;
    }

    if (index == -1 && code.isArray())
    {
        throw Exception("TypedValueDecoder::decode: " + asterixCodeToSymbol(code) + " array expects an index");
    }

    if (index != -1 && !code.isArray())
    {
        throw Exception("TypedValueDecoder::decode: " + asterixCodeToSymbol(code) + " scalar value doesn't expects an index");
    }

    Encoding::ValueType encoding = ctx.bits.encoding.toValue();
    bool encoded = false;

    switch(code.type())
    {
        case PrimitiveType::Boolean:
        {
            bool boolean = false;
            encoded = encodeBoolean(ctx, boolean, index);
            if (encoded)
                value = Poco::UInt64(boolean);
            break;
        }

        case PrimitiveType::Real:
        {
            double real;
            encoded = encodeReal(ctx, real, index);
            if (encoded)
            {
                if (ctx.policy.normalizeValues)
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
                    value = Poco::UInt64(real / (ctx.bits.scale * unit));
                }
                else
                {
                    value = Poco::UInt64(real);
                }
            }
            break;
        }

        case PrimitiveType::Integer:
        {
            Poco::Int64 integer = 0;
            encoded = encodeSigned(ctx, integer, index);
            if (encoded)
                value = Poco::UInt64(integer);
            break;
        }

        case PrimitiveType::Unsigned:
        {
            encoded = encodeUnsigned(ctx, value, index);
            if (encoding == Encoding::Octal)
                value = ByteUtils::dec2oct(value);
            break;
        }

        default:
        {
            switch (encoding)
            {
                case Encoding::Ascii:
                {
                    std::string str;
                    encoded = encodeString(ctx, str, index);
                    if (encoded)
                    {
                        //std::reverse(str.begin(), str.end());
                        for(Byte byte: str)
                        {
                            value <<= 8;
                            value |= byte;
                        }
                    }
                    break;
                }
                case Encoding::Octal:
                {
                    Poco::UInt64 aux = 0;
                    encoded = encodeUnsigned(ctx, aux, index);
                    if (encoded)
                    {
                        value = ByteUtils::dec2oct(aux);
                    }
                    break;
                }
                case Encoding::SixBitsChar:
                {
                    std::string str;
                    encoded = encodeString(ctx, str, index);
                    if (encoded)
                    {
                        std::string aux = ByteUtils::toSixBitString(str);
                        std::reverse(aux.begin(), aux.end());
                        for(Byte byte: aux)
                        {
                            value <<= 8;
                            value |= byte;
                        }
                    }
                    break;
                }
                case Encoding::Hex:
                {
                    std::string str;
                    encoded = encodeString(ctx, str, index);
                    if (encoded)
                    {
                        value = Poco::NumberParser::parseHex64(str);
                    }
                    break;
                }
            }
            break;
        }
    }

    return encoded;
}

} /* namespace astlib */
