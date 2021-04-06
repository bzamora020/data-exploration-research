#include "comboDemogData.h"
#include "demogData.h"
#include "placeData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


void comboDemogData::addDemogtoRegion(shared_ptr<demogData> CD) {
    
	popOver65 += CD->getpopOver65Count();
	popUnder18 += CD->getpopUnder18Count();
	popUnder5 += CD->getpopUnder5Count();
	bachelorDegreeUp += CD->getBAupCount();
	highSchoolUp += CD->getHSupCount() ;
    belowPoverty += CD->getBelowPovertyCount();
	population2014 += CD->getPop();
}