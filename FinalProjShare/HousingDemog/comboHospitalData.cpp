
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <cassert>
#include <iomanip>
#include "hospitalData.h"

 //note this stores a running total until averageOut 
//just adds the current county info to the running total
void comboHospitalData::addHospitaltoRegion(hospitalData* HI) {
  if (HI->getOverallRate() != -1) {
    if (overallRateTotal != 0) {
      overallRateTotal +=1;
      int overallRateCount = overallRate*(overallRateTotal-1)+ HI->getOverallRate();
      overallRate = (double)overallRateCount/overallRateTotal;
    } else {
      overallRate = HI->getOverallRate();
      overallRateTotal++;
    }
	}
	if (HI->getMortality().getRatingNum() != -1) {
    if (mortRateTotal != 0) {
      mortRateTotal +=1;
      int mortRateCount = mortRate.getRatingNum()*(mortRateTotal-1)+ HI->getMortality().getRatingNum();
      mortRate = (double)mortRateCount/mortRateTotal;
    } else {
      mortRate = HI->getMortality();
      mortRateTotal++;
    }
	}
	if (HI->getReadmit().getRatingNum() != -1) { 
    if (readmitRateTotal != 0) {
      readmitRateTotal +=1;
      int readmitRateCount = readmitRate.getRatingNum()*(readmitRateTotal-1)+ HI->getReadmit().getRatingNum();
      readmitRate = (double)readmitRateCount/readmitRateTotal;
    } else {
      readmitRate = HI->getReadmit();
      readmitRateTotal++;
    }
	}
	numHosp++;
}
/*
void comboHospitalData::avgRates() {
  if (overallRateTotal != 0)
    overallRate = (double)overallRate/overallRateTotal;
  if (mortRateTotal != 0)
    mortRate = mortRate/mortRateTotal;
  if (readmitRateTotal != 0)
    readmitRate = readmitRate/readmitRateTotal;
}*/


std::ostream& operator<<(std::ostream &out, const comboHospitalData &SH) {
  out << SH.getRegionType() << " Hospital Info: " << SH.getRegion();
  out << "\nNumber of Hospitals: " << SH.getNumH();
    out << std::setprecision(2) << std::fixed;
    out << "\nOverall Rating (out of 5): " << SH.getOverallRate();
    out << "\nMortality Rating: " << SH.getMortality()<< ", Num: " << SH.getMortality().getRatingNum();
    out << "\nReadmission Rating: " << SH.getReadmit()<< ", Num: " << SH.getReadmit().getRatingNum();
    return out;
}
