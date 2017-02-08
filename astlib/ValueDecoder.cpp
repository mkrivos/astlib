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

void TypedValueDecoder::decode(Poco::UInt64 value, const BitsDescription& bits)
{
    const std::string& id = bits.name;

    if (id == "X")
        std::cout << std::endl;

    if (bits.bit != -1)
    {
        decodeBoolean(id, bool(value));
    }
    else
    {
        Encoding::ValueType encoding = bits.encoding.toValue();

        if (bits.scale != 1.0)
        {
            double unit = 1.0;
            switch(bits.units.toValue())
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
            };
            if (encoding == Encoding::Unsigned)
            {
                decodeReal(id, value * bits.scale * unit);
            }
            else
            {
                decodeReal(id, ByteUtils::toSigned(value, bits.effectiveBitsWidth()) * bits.scale * unit);
            }
        }
        else
        {
            switch (encoding)
            {
                case Encoding::Signed:
                    decodeSigned(id, ByteUtils::toSigned(value, bits.effectiveBitsWidth()));
                    break;
                case Encoding::Unsigned:
                    decodeUnsigned(id, value);
                    break;
                case Encoding::Ascii:
                    decodeString(id, "");
                    break;
                case Encoding::Octal:
                    decodeUnsigned(id, ByteUtils::oct2dec(value));
                    break;
                case Encoding::SixBitsChar:
                    decodeString(id, ByteUtils::fromSixBitString((const Byte*)&value));
                    break;
                case Encoding::Hex:
                    decodeString(id, Poco::NumberFormatter::formatHex(value));
                    break;
            }
        }
    }
}

}


