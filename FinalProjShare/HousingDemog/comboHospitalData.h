#ifndef COMBOH_H
#define COMBOH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"

/*
  aggregated hospital data for a given regional level (county or state)
*/
class comboHospitalData : public hospitalData {
public:
  // if region and largest place name are the same
  comboHospitalData(string inRT, string inS) :
    hospitalData{inS}, numHosp(0), overallRateTotal(0), mortRateTotal(0), readmitRateTotal(0), region(inS), 
    regionType(inRT) {}
  // if region and largest place name are different
  comboHospitalData(string inRT, string inS, string inN) :
    hospitalData{inS}, numHosp(0), overallRateTotal(0), mortRateTotal(0), readmitRateTotal(0), region(inN),
    regionType(inRT) {}
  double getNumH() const {return numHosp;}
friend std::ostream& operator<<(std::ostream &out, const comboHospitalData &SH);
void addHospitaltoRegion(hospitalData* HI);
void avgRates();
string getRegion() const {return region;}
string getRegionType() const {return regionType;}
string getName() const {return place;}

private:
  double numHosp;
  int overallRateTotal;
  int mortRateTotal;
  int readmitRateTotal;
  string region;
  string regionType;
  
};
#endif
