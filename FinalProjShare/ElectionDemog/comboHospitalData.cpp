
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>

#include <iostream>
using namespace std;


void comboHospitalData::addHospitaltoRegion(shared_ptr<hospitalData> HI) {
	counties.push_back(HI);
	if (HI->getOverallRate() < 0)
		return;
	setOverallRate(getOverallRate() * numHosp + HI->getOverallRate());
	setMortality(getMortality() * numHosp + HI->getMortality());
	setReadmit(getReadmit() * numHosp + HI->getReadmit());

	numHosp++;
	setOverallRate(getOverallRate() / numHosp);
	setMortality(getMortality() / numHosp);
	setReadmit(getReadmit() / numHosp);
}
