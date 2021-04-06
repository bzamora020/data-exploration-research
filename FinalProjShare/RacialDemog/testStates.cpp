
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
#include "hospitalData.h"
using namespace std;

int main() {
  cout << "Testing state data aggregation query..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing hospital data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);

    theAnswers.createStateHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    string lowHosp = theAnswers.LowHospRating();
    ASSERT_EQUALS("DC", lowHosp);

    string highHosp = theAnswers.HighHospRating();
  	ASSERT_EQUALS("WI", highHosp);

    string highMort = theAnswers.HighMortHospRating();
    ASSERT_EQUALS("MA", highMort);

  	string highReadmit = theAnswers.HighReadmitHospRating();
  	ASSERT_EQUALS("ID", highReadmit);



  return 0;
}
