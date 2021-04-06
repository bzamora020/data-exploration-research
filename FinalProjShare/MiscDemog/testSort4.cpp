#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


  cout << "Testing demographic income sort..." << endl;

  dataAQ theAnswers;

    //read in the demographic data
    std::vector<shared_ptr<placeData>> theCountyDemogData = read_csv(
            "county_demographics.csv", DEMOG); 

    //create the state demographic data
    theAnswers.createStateDemogData((std::vector<shared_ptr<demogData>>&)theCountyDemogData);

    std::vector<comboDemogData*> povertyLevelHighToLow;
    theAnswers.sortDemogPovLevelHighLow((std::vector<demogData *>& )povertyLevelHighToLow);

  // Test case #1
  string mostPov[] {"MS", "NM", "AR", "LA", "KY"};
  for (int i=0; i < 5; i++) {
    ASSERT_EQUALS(mostPov[i], povertyLevelHighToLow.at(i)->getState());
  }

  return 0;
}
