
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>

//add in another hospital data
void comboHospitalData::addHospitaltoRegion(hospitalData * HI) {
	//assert(state.compare(HI->getState()) == 0);
	overallRating += HI->getOverallRate();
	mortality += HI->getMortality().getRatingNum();
	readmission += HI->getReadmit().getRatingNum();
	numHospitals++;
	/* don't count 'unknown' data in averages */
	if (HI->getOverallRate() > 0)
		numNZOHospitals++;
	if (HI->getMortality().getRatingNum() > 0)
		numNZMHospitals++;
	if (HI->getReadmit().getRatingNum() > 0)
		numNZRHospitals++;
}
