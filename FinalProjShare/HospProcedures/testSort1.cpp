#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include <vector>
#include "tddFuncs.h"
using namespace std;

int main() {


cout << "Testing hospital sort..." << endl;

	dataAQ theAnswers;

    //Would like to add test to query between the two (may need to specify more)

    //read in a csv file and create a vector of objects representing hospital data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);

		vector<shared_ptr<hospitalData>> tempHD;
		for (auto obj: theHospitalData){
			shared_ptr<hospitalData> tempD = std::static_pointer_cast<hospitalData>(obj);
			tempHD.push_back(tempD);
		}

    theAnswers.createStateHospData(tempHD);

    std::vector<comboHospitalData*> hospHighToLow;


    theAnswers.sortHospRatingHighLow(hospHighToLow);

    // Test case #1
    string topHosp[] {"WI", "SD", "UT", "HI", "ID"};

    //only test if vector valid
    if (hospHighToLow.size() > 5 ) {
      for (int i=0; i < 5; i++) {
  	   ASSERT_EQUALS(topHosp[i], hospHighToLow.at(i)->getRegion());
      }
    } else {
      cout << "FAIL due to invalid vector size" << endl;
    }

  return 0;
}
