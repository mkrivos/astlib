///
/// \package astlib
/// \file loader.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
/// See LICENCE file in project root directory
///

#include "astlib/CodecDeclarationLoader.h"
#include "astlib/CodecDeclarationLoaderEra.h"
#include "astlib/Exception.h"
#include <iostream>

using namespace astlib;

int main(int argc, char* argv[])
{
    try
    {
        CodecDeclarationLoader loader;
        loader.load("specs/asterix_cat048_1_14.xml");

        CodecDeclarationLoaderEra loader2;
        loader2.load("specs/uniEnc_Ast_48_1.14.xml");
    }
    catch(Exception& e)
    {
        std::cerr << e.displayMessage() << std::endl;
    }

    return 0;
}
