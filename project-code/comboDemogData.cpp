#include "comboDemogData.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

 //note this stores a running total until averageOut 
//just adds the current county info to the running total
void comboDemogData::addDemogtoRegion(demogData *CD) {
    //assert(state.compare(CI->getState()) == 0);
    popOver65 += CD->getpopOver65Count();
    popUnder18 += CD->getpopUnder18Count();
    popUnder5 += CD->getpopUnder5Count();
    bachelorDegreeUp += CD->getBAupCount();
    highSchoolUp += CD->getHSupCount() ;
    belowPoverty += CD->getBelowPovertyCount();
    population2014 += CD->getPop();
    racial += CD->getRacialCount();
    numCombined++;
}
