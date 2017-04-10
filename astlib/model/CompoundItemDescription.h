///
/// \file CompoundItemDescription
///
/// \author Peter Chriastel <peter.chriastel@r-sys.sk>
/// \date 07.02.2016
/// \brief Compound Data field descriptor
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "ItemDescription.h"
namespace astlib
{

class ASTLIB_API CompoundItemDescription :
    public ItemDescription
{
public:
    CompoundItemDescription(int id, const std::string& description, const ItemDescriptionVector& items);
    virtual ~CompoundItemDescription() {};
	
    const ItemDescriptionVector& getItemsVector() const { return _itemsVector; }

private:
    virtual ItemFormat getType() const { return ItemFormat::Compound; }

    ItemDescriptionVector _itemsVector;
};

} /* namespace astlib */
