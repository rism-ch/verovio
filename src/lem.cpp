/////////////////////////////////////////////////////////////////////////////
// Name:        lem.cpp
// Author:      Laurent Pugin
// Created:     2018
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "lem.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// Lem
//----------------------------------------------------------------------------

Lem::Lem() : EditorialElement("lem-"), AttSource()
{
    RegisterAttClass(ATT_SOURCE);

    Reset();
}

Lem::~Lem() {}

void Lem::Reset()
{
    EditorialElement::Reset();
    ResetSource();
}

//----------------------------------------------------------------------------
// functor methods
//----------------------------------------------------------------------------

} // namespace vrv
