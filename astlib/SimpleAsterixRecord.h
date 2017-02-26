///
/// \package astlib
/// \file SimpleAsterixMessage.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13. 2. 2017 - 18:54:38
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/AsterixItemCode.h"
#include <Poco/Dynamic/Var.h>
#include <map>
#include <memory>


namespace astlib
{

/**
 * Trivial implementation of AsterixRecord based on std::map.
 */
class SimpleAsterixRecord
{
public:
    SimpleAsterixRecord();
    ~SimpleAsterixRecord();

    /**
     * Set simple scalar data value.
     * @param code identificator of the item (from AsterixItemDictionary.h)
     * @param value value to move to the container
     * @param index index of value into the array (0 up to initialized size) or -1 for non array types
     */
    void setItem(AsterixItemCode code, Poco::Dynamic::Var&& value, int index = -1);

    /**
     * Initialize item as an array with fixed size.
     * @param code
     * @param size
     */
    void initializeArray(AsterixItemCode code, size_t size);

    /**
     * @param code
     * @return true if item is already initialized and has value, otherwise false
     */
    bool hasItem(AsterixItemCode code) const;

    /**
     * @param code
     * @return size of the array item, for scalars returns value 1. If item does not exists, throw exception.
     */
    size_t getArraySize(AsterixItemCode code) const;

    /**
     * Get the value of item as boolean.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    bool getBoolean(AsterixItemCode code, bool& value, int index = -1) const;

    /**
     * Get the value of item as 64bit unsigned integer.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    bool getUnsigned(AsterixItemCode code, Poco::UInt64& value, int index = -1) const;

    /**
     * Get the value of item as 64bit signed integer.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    bool getSigned(AsterixItemCode code, Poco::Int64& value, int index = -1) const;

    /**
     * Get the value of item as 64bit double.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    bool getReal(AsterixItemCode code, double& value, int index = -1) const;

    /**
     * Get the value of item as string.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    bool getString(AsterixItemCode code, std::string& value, int index = -1) const;

    /**
     * @return human readable representation of object in form of key/value list
     */
    std::string toString() const;

    /**
     * @return initialized items count
     */
    size_t size() const;

    /**
     * Clears all existing items.
     */
    void clear();

private:
    std::map<AsterixItemCode, Poco::Dynamic::Var> _items;
};

using SimpleAsterixRecordPtr = std::shared_ptr<SimpleAsterixRecord>;

} /* namespace astlib */
