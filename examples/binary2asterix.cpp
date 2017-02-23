///
/// \package astlib
/// \file BinaryDataDekoderTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/CodecRegister.h"
#include "astlib/decoder/SimpleValueDecoder.h"
#include "astlib/decoder/BinaryAsterixDecoder.h"
#include "astlib/Exception.h"
#include "astlib/AsterixItemDictionary.h"
#include <iostream>

using namespace astlib;

static constexpr int PACKET_SIZE = 1+2+3+2+3+2+4+2+2+8+3+6+2+4+2+2;
unsigned char standardMessage[PACKET_SIZE] = {
    48, // CAT
    0, PACKET_SIZE,
    0xFF, 0xDB, 0x08,// FSPEC

    5, 6,  // 10 - sac sic
    0, 0, 200, // 140 - time of day
    0xFF, 0xFE, // 20 - Target Report Descriptor
    0xFF, 0xFF,0xFF, 0xFF, // 40 - polar coords
    0xFF, 0xFF, // 70 - mode 3A
    0xFF, 0xFF, // 90 - mode C
    0xFE, 0x88, 0x44,0x88, 0x44, 0x88, 0x44, 0x88, // 130 - plot characteristics

    0xFF, 0xFF, 0xFF, // 220 - aircraft address
    0x42, 0x55, 0x12, 0x45, 0x42, 0x24, // 240 - Aircraft Identification
    1,0, // 161 - track number
    0xFF, 0xFF, 0x00, 0x01, // 42 - cartes coords
    0xFF, 0xFE, // 170 - track status

    0xFF, 0xFF, // 110 - 3d height
};

using namespace astlib;

int main(int, char**)
{
    CodecRegister codecRegister;
    // Populate codecs
    codecRegister.populateCodecsFromDirectory("specs");

    // Find latest category 48 codec
    CodecDescriptionPtr codecCat48 = codecRegister.getLatestCodecForCategory(48);

    // Use defualt trivial asterix container implemntation
    class MySimpleValueDecoder :
        public SimpleValueDecoder
    {
    public:
        virtual void onMessageDecoded(SimpleAsterixRecordPtr ptr)
        {
            msg = ptr;
        }

        SimpleAsterixRecordPtr msg;
    } myDecoder;


    BinaryAsterixDecoder dekoder;

    // Decode binary data stream ...
    dekoder.decode(*codecCat48, myDecoder, standardMessage, sizeof(standardMessage));

    bool sacIsPresent = myDecoder.msg->hasItem(TRACK_ALTITUDE_HEIGHT3D_CODE);

    if (sacIsPresent)
    {
        // Get SAC value from message
        double sac;
        myDecoder.msg->getReal(TRACK_ALTITUDE_HEIGHT3D_CODE, sac);
        std::cout << "3D_HEIGHT code is " << sac << " " << asterixCodeToSymbol(TRACK_ALTITUDE_HEIGHT3D_CODE) << " hex = " << Poco::NumberFormatter::formatHex(TRACK_ALTITUDE_HEIGHT3D_CODE.value) << std::endl;
    }
    return 0;
}
