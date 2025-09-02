#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

#include "Enums.h"

UnitSystem ACTIVE_UNIT_SYSTEM = Metric;
void ToggleUnits()
{
  if (ACTIVE_UNIT_SYSTEM == Metric)
  {
    ACTIVE_UNIT_SYSTEM = Imperial;
  }
  else
  {
    ACTIVE_UNIT_SYSTEM = Metric;
  }
}

#endif