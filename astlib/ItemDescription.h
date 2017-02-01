///
/// \package astlib
/// \file ItemDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 1. 2. 2017 - 18:45:34
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#pragma once

namespace artus
{

class ItemDescription
{
public:
    ItemDescription();
    virtual ~ItemDescription();

private:
    std::string _id;
    std::string _description;
};

} /* namespace artus */
