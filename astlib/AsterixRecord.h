///
/// \package astlib
/// \file AsterixRecord.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 6. 4. 2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/AsterixItemCode.h"
#include <Poco/Dynamic/Var.h>
#include <Poco/Timestamp.h>
#include <memory>


namespace astlib
{

class AsterixRecord
{
public:
    virtual ~AsterixRecord() = default;

    /**
     * Set simple scalar data value.
     * @param code identificator of the item (from AsterixItemDictionary.h)
     * @param value value to move to the container
     * @param index index of value into the array (0 up to initialized size) or -1 for non array types
     */
    virtual void setItem(AsterixItemCode code, Poco::Dynamic::Var&& value, int index = -1) = 0;

    /**
     * Initialize item as an array with fixed size.
     * @param code
     * @param size
     */
    virtual void initializeArray(AsterixItemCode code, size_t size) = 0;

    /**
     * @param code
     * @return true if item is already initialized and has value, otherwise false
     */
    virtual bool hasItem(AsterixItemCode code) const = 0;

    /**
     * @param code
     * @return size of the array item, for scalars returns value 1. If item does not exists, throw exception.
     */
    virtual size_t getArraySize(AsterixItemCode code) const = 0;

    /**
     * Get the value of item as boolean.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    virtual bool getBoolean(AsterixItemCode code, bool& value, int index = -1) const = 0;

    /**
     * Get the value of item as 64bit unsigned integer.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    virtual bool getUnsigned(AsterixItemCode code, Poco::UInt64& value, int index = -1) const = 0;

    /**
     * Get the value of item as 64bit signed integer.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    virtual bool getSigned(AsterixItemCode code, Poco::Int64& value, int index = -1) const = 0;

    /**
     * Get the value of item as 64bit double.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    virtual bool getReal(AsterixItemCode code, double& value, int index = -1) const = 0;

    /**
     * Get the value of item as string.
     * @param code item identifier
     * @param value placeholder for a result
     * @param index -1 for scalars, or index of item for array types (0 up to initialized size), if index is out of initialized range, exception is thrown.
     * @return true if value was found, otherwise false, if item is not boolean type, an exception is thrown.
     */
    virtual bool getString(AsterixItemCode code, std::string& value, int index = -1) const = 0;

    /**
     * @return human readable representation of object in form of key/value list
     */
    virtual std::string toString() const = 0;

	Poco::UInt8 getCategory() const
	{
		return _category;
	}

	void setCategory(Poco::UInt8 category)
	{
		_category = category;
	}

	const Poco::Timestamp& getTimestamp() const
	{
		return _timestamp;
	}

	void setTimestamp(const Poco::Timestamp& timestamp)
	{
		_timestamp = timestamp;
	}

private:
    Poco::Timestamp _timestamp;
    Poco::UInt8 _category = 0;
};

using AsterixRecordPtr = std::shared_ptr<AsterixRecord>;

} /* namespace astlib */

