#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


  cout << "Testing state county sort..." << endl;

  dataAQ theAnswers;

      //read in the helper file to map city to county
    theAnswers.read_csvCityCounty("simple_uscities.csv");

    //read in the demographic data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);

    //create the county hospital data   
    theAnswers.createCountyHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    std::vector<comboHospitalData*> CAhospHighToLow;
    theAnswers.sortHospRatingHighLowForState((std::vector<comboHospitalData *>& )CAhospHighToLow, "CA");


  // Test case #1
  string bestCA[] {"Amador County", "Lassen County", "Placer County", "San Mateo County", "San Diego County"};
  for (int i=0; i < 5; i++) {
    ASSERT_EQUALS(bestCA[i], CAhospHighToLow.at(i)->getRegion());
  }

  return 0;
}
