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

    std::vector<comboDemogData*> povertyLevelLowToHigh;
    theAnswers.sortDemogPovLevelLowHigh((std::vector<demogData *>& )povertyLevelLowToHigh);

  // Test case #1
  string leastPov[] {"NH", "MD", "AK", "CT", "NJ"};
  for (int i=0; i < 5; i++) {
  	ASSERT_EQUALS(leastPov[i], povertyLevelLowToHigh.at(i)->getState());
  }

  return 0;
}
