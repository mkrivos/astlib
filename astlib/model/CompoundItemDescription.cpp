///
/// \file CompoundItemDescription
///
/// \author Peter Chriastel <peter.chriastel@r-sys.sk>
/// \date time
/// \brief description
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CompoundItemDescription.h"

namespace astlib
{

CompoundItemDescription::CompoundItemDescription(int id, const std::string& description, const ItemDescriptionVector& items) :
    ItemDescription(id, description),
    _itemsVector(items)
{
}

} /* namespace astlib */
