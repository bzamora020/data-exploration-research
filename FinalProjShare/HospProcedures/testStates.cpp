
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing state data aggregation query..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing hospital data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);

    vector<shared_ptr<hospitalData>> tempHD;
    for (auto obj: theHospitalData){
			shared_ptr<hospitalData> tempD = std::static_pointer_cast<hospitalData>(obj);
			tempHD.push_back(tempD);
		}
    theAnswers.createStateHospData(tempHD);

    string lowHosp = theAnswers.LowHospRating();
    ASSERT_EQUALS("DC", lowHosp);

    string highHosp = theAnswers.HighHospRating();
  	ASSERT_EQUALS("WI", highHosp);

    string highMort = theAnswers.HighMortHospRating();
    ASSERT_EQUALS("MA", highMort);

  	string highReadmit = theAnswers.HighReadmitHospRating();

    ASSERT_EQUALS("UT", highReadmit);




  return 0;
}
