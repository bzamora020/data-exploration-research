#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "tddFuncs.h"
#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"
using namespace std;

int main() {


  cout << "Testing stats on Data - new tools" << endl;

  std::vector<shared_ptr<placeData>> pileOfData;

  //read in the hospital data
  read_csv(pileOfData, "hospitals.csv", HOSPITAL);
   
  //read in the demographic data
  read_csv(pileOfData, "county_demographics.csv", DEMOG); 

  visitorCombineCounty theCounties("simple_uscities.csv");
  //use visitor pattern to be able to aggregate
  for (const auto &obj : pileOfData) {
        obj->accept((visitorCombineCounty&)theCounties);
  }

  countyGather fillCounties;

  vector<double> dataX;
  vector<double> dataY;

  fillCounties.gatherPerStats(&theCounties, dataX, dataY, &demogData::getBelowPoverty, &comboHospitalData::getOverallRate);

  double mX = stats::computeMean(dataX); 
  double mY = stats::computeMean(dataY);  
  cout << mY << endl;
  double cc = stats::computeCorCoeffSample(dataX, dataY);

  ASSERT_EQUALS(mX, 16.489);
  ASSERT_EQUALS(mY, 2.5392);
  ASSERT_EQUALS(cc, -0.0948);

  return 0;
}
