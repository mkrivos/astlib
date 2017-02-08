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

namespace astlib
{

void TypedValueDecoder::decode(Poco::UInt64 value, const BitsDescription& bits)
{
    const std::string& id = bits.name;

    if (bits.bit != -1)
    {
        decodeBoolean(id, bool(value));
    }
    else
    {
        Encoding::ValueType encoding = bits.encoding.toValue();

        if (bits.scale != 1.0)
        {
            if (encoding == Encoding::Signed)
                decodeReal(id, value / bits.scale);
            else
                decodeReal(id, ByteUtils::toSigned(value, (bits.from-bits.to+1)) / bits.scale);
        }
        else
        {
            switch (encoding)
            {
                case Encoding::Signed:
                    decodeSigned(id, ByteUtils::toSigned(value, (bits.from-bits.to+1)));
                    break;
                case Encoding::Unsigned:
                    decodeUnsigned(id, value);
                    break;
                case Encoding::Ascii:
                    decodeString(id, "");
                    break;
                case Encoding::Octal:
                    decodeString(id, "");
                    break;
                case Encoding::SixBitsChar:
                    decodeString(id, "");
                    break;
                case Encoding::Hex:
                    decodeString(id, Poco::NumberFormatter::formatHex(value));
                    break;
            }
        }
    }
}

}


