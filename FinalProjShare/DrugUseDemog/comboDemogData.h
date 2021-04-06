#ifndef COMBOD_H
#define COMBOD_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "placeData.h"

/*
  aggregated demographic data for a given regional level (state - or larger region)
*/
class comboDemogData : public demogData {

	public:

		comboDemogData(string regionType, string name, string inS) : demogData(name, inS, regionType) {}

		void addDemogtoRegion(shared_ptr<demogData> CD);
};
#endif
