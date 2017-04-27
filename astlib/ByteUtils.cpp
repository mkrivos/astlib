///
/// \package astlib
/// \file ByteUtils.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 7Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "ByteUtils.h"
#include <Poco/NumberFormatter.h>
#include <Poco/String.h>
#include <iostream>

namespace astlib
{

ByteUtils::ByteUtils()
{
}

ByteUtils::~ByteUtils()
{
}

void ByteUtils::pokeBigEndian(Byte buffer[], Poco::UInt64 value, size_t len)
{
    for(int i = len-1; i >= 0; i--)
    {
        buffer[i] = Byte(value);
        value >>= 8;
    }
}

size_t ByteUtils::calculateFspec(const Byte fspecPtr[])
{
    size_t fspecLen = 1;

    for (int k = 0; fspecPtr[k] & FX_BIT; k++)
    {
        fspecLen++;
    }

    return fspecLen;
}

Poco::Int64 ByteUtils::toSigned(Poco::UInt64 value, int effectiveBits)
{
    Poco::UInt64 mask1 = (1ULL << (effectiveBits-1));
    if (mask1 & value)
    {
        Poco::UInt64 mask2 = ~(mask1-1);
        return static_cast<Poco::Int64>(value|mask2);
    }
    return static_cast<Poco::Int64>(value);
}

Poco::UInt64 ByteUtils::oct2dec(Poco::UInt32 modeValue)
{
    Poco::UInt64 val;
    val = modeValue & 00007;
    val += ( (modeValue & 00070 ) >> 3 ) * 10;
    val += ( (modeValue & 00700 ) >> 6 ) * 100;
    val += ( (modeValue & 07000 ) >> 9 ) * 1000;
    return val;
}

Poco::UInt32 ByteUtils::dec2oct(Poco::UInt64 modeValue)
{
    Poco::UInt32 val = 0;

    modeValue %= 10000;
    val += (modeValue / 1000 ) * 01000;

    modeValue %= 1000;
    val += (modeValue / 100 ) * 0100;

    modeValue %= 100;
    val += (modeValue / 10 ) * 010;

    modeValue %= 10;
    val += (modeValue);

    return val;
}

static char ia5ToChar(Byte char6bit)
{
    //                     0.        1.        2.        3.        4.        5.        6.
    // (Table 3-6)         0123456789012345678901234567890123456789012345678901234567890123
    static char IA5[65] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ                     0123456789      ";
    return IA5[char6bit & 0x3F];
}

static Byte charToIa5(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
        return (Byte) (c - 'A' + 1);
    if ((c >= '0') && (c <= '9'))
        return (Byte) (c - '0' + 48);
    if (c == ' ')
        return 32;

    return 0;
}

std::string ByteUtils::fromSixBitString(const Byte buffer[])
{
    std::string aux("          ");
    Byte buf[6];

    // ICAO dokumentacia (Annex 10.pdf):
    // This is ICAO - AIS subfield.
    // Each character shall be coded as a 6-bit subset of the International Alphabet Number 5 (IA-5) as illustrated in
    // Table 3-6. The character code shall be transmitted with the high order unit (b6) first and the reported aircraft
    // identification shall be transmitted with its left-most character first. Characters shall be coded consecutively
    // without intervening SPACE code. Any unused character spaces at the end of the subfield shall contain a SPACE
    // character code.

    buf[0] = buffer[5];
    buf[1] = buffer[4];
    buf[2] = buffer[3];
    buf[3] = buffer[2];
    buf[4] = buffer[1];
    buf[5] = buffer[0];

    aux[0] = ia5ToChar(buf[0] >> 2 & 0x3F);
    aux[1] = ia5ToChar((buf[0] << 4 | buf[1] >> 4) & 0x3F);
    aux[2] = ia5ToChar((buf[1] << 2 | buf[2] >> 6) & 0x3F);
    aux[3] = ia5ToChar(buf[2] & 0x3F);

    aux[4] = ia5ToChar(buf[3] >> 2 & 0x3F);
    aux[5] = ia5ToChar((buf[3] << 4 | buf[4] >> 4) & 0x3F);
    aux[6] = ia5ToChar((buf[4] << 2 | buf[5] >> 6) & 0x3F);
    aux[7] = ia5ToChar(buf[5] & 0x3F);

    return Poco::trimRight(aux);
}

std::string ByteUtils::toSixBitString(const std::string sixbit)
{
    Byte buffer[8] = {32, 32, 32, 32, 32, 32, 32, 32};
    char aux[6];
    size_t size = sixbit.size();

    for (size_t i = 0; (i < size) && (i < sizeof(buffer)); i++)
    {
        buffer[i] = charToIa5(sixbit[i]);
    }

    aux[0] = (buffer[0] << 2) | ((buffer[1] >> 4) & 0x03);
    aux[1] = ((buffer[1] << 4) & 0xF0) | ((buffer[2] >> 2) & 0x0F);
    aux[2] = ((buffer[2] << 6) & 0xC0) | buffer[3];

    aux[3] = (buffer[4] << 2) | ((buffer[5] >> 4) & 0x03);
    aux[4] = ((buffer[5] << 4) & 0xF0) | ((buffer[6] >> 2) & 0x0F);
    aux[5] = ((buffer[6] << 6) & 0xC0) | buffer[7];

    std::swap(aux[0], aux[5]);
    std::swap(aux[1], aux[4]);
    std::swap(aux[2], aux[3]);

    return aux;
}

void ByteUtils::printHex(const std::vector<Byte>& buffer)
{
    for(Byte byte: buffer)
    {
        std::cout << Poco::NumberFormatter::formatHex(byte, 2, false) << ' ';
    }
}

} /* namespace astlib */
