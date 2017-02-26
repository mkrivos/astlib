///
/// \package astlib
/// \file CodecPolicy.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 24Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CodecPolicy.h"

namespace astlib
{

CodecPolicy::CodecPolicy(Code mandatoryItems, bool verbose) :
    mandatoryItems(mandatoryItems),
    verbose(verbose)
{
}

} /* namespace astlib */
