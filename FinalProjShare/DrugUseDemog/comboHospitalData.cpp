
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>


void comboHospitalData::addHospitaltoRegion(shared_ptr<hospitalData> HI) {


    hospitalCount += 1;

    if (HI->getOverallRate() != -1) { 
        validOverall += 1;
        rating tempOverall = rating(HI->getOverallRate());
        overallRating = (overallRating*(validOverall-1) + tempOverall)/validOverall;
      }
      if (HI->getMortality().isValid()) {
        validMortality += 1; 
        rating tempMortality = rating(HI->getMortality());
        mortalityRating = (mortalityRating*(validMortality-1) + tempMortality)/validMortality;
      }
      if (HI->getReadmit().isValid()) { 
        validReadmit += 1; 
        rating tempReadmit = rating(HI->getReadmit());
        readmitRating = (readmitRating*(validReadmit-1) + tempReadmit)/validReadmit;
      }
}   
