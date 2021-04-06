#include "dataAQ.h"
#include "parse.h"
#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  
#include <iomanip>
#include "tddFuncs.h"
using namespace std;

int main() {


cout << "Testing Report" << endl;

	  dataAQ theAnswers;
    cout << std::setprecision(2) << std::fixed;
    //read in the hospital data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);
   
    //read in the demographic data
    std::vector<shared_ptr<placeData>> theCountyDemogData = read_csv(
            "county_demographics.csv", DEMOG); 

    //create the state demographic data
    theAnswers.createStateDemogData((std::vector<shared_ptr<demogData>>&)theCountyDemogData);

    //create the state hospital data
    theAnswers.createStateHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    //the report code
    theAnswers.stateReport(21);
    // Use the string value of buffer to compare against expected output
    std::string theReport = buffer.str();

    // Restore original buffer before exiting
    std::cout.rdbuf(prevcoutbuf);

    // report
    string expectReport ="\nSpecial report demog Data:\nDemographics Info (State): MS\nEducation info:\n(\% Bachelor degree or more): 20.43\n(\% high school or more): 81.62\n\% below poverty: 22.63\nSpecial report hospital data:\nHospital Info: MS\nOverall rating (out of 5): 2.57\nGenerated a report for a total of: 1\n";
    
    cout << "difference in characters: " << theReport.compare(expectReport);
    ASSERT_EQUALS(expectReport, theReport);

  return 0;
}