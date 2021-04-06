#ifndef COMBOD_H
#define COMBOD_H

#include <memory>
#include <string>
#include <iostream>

#include "countyDemogData.h"
#include "demogData.h"
#include "placeData.h"

/*
  aggregated demographic data for a given regional level (state - or larger region)
 */
class comboDemogData : public demogData  {
public:
	//constructor with just region name
	comboDemogData(string region) : demogData{region},
		numCounties(0){

	}
	//constructor with region name and first county
	comboDemogData(string region, shared_ptr<demogData> demog): demogData{region},
		numCounties(0)  {
		addDemog(demog);
	}
	//adds a county to the region
	void addDemog(shared_ptr<demogData> demog);

	int getNumCounties() const { return numCounties; }

protected:
	std::ostream& print(std::ostream &out) const override;

private:
	int numCounties;
};
#endif
