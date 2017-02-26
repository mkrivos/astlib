///
/// \package astlib
/// \file FspecGenerator.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/ByteUtils.h"
#include <vector>


namespace astlib
{

/**
 * Class for clever FSPEC handling.
 * After creating contains zero items.
 * User can add item bits or skip bits by simple calling addItem(), skipItem() and skipItems(int).
 * FX bit is added automaticaly when needed.
 * When done, user can ask for binary representation by calling data() and size() methods.
 */
class FspecGenerator
{
public:
    FspecGenerator();
    ~FspecGenerator();

    /**
     * Add bit with value 1 and forward to next item.
     */
    void addItem();

    /**
     * Add bit with value 0 and forward to next item.
     */
    void skipItem();

    /**
     * Calls 'count' times skipItem() method.
     * @param count
     */
    void skipItems(int count);

    /**
     * @return effective size of encoded FSPEC data.
     */
    size_t size() const;

    /**
     * FSPEC data representation.
     * @return
     */
    const Byte* data() const;

    std::vector<Byte> getArray() const;

    static std::vector<Byte> reduce(const std::vector<Byte>& sequence);

private:
    std::vector<Byte> _fspec;
    int _byteMask = 0x100;
};

} /* namespace astlib */

