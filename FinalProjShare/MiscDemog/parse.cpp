/* helper routines to read out csv data */
#include "parse.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include <algorithm>
#include <cmath>

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}


string getFieldNQ(std::stringstream &ss) {
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
        //std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);
    //turn into mathematical percent
    double popOver65 = stod(getField(ss))/100.0;
    double popUnder18 = stod(getField(ss))/100.0;
    double popUnder5 = stod(getField(ss))/100.0;
    double bachelorDegreeUp = stod(getField(ss))/100.0;
    double highSchoolUp = stod(getField(ss))/100.0;

    //now skip over some data
    for (int i=0; i < 11; i++)
        getField(ss);

    //not using this demographic for lab04
    
    //now skip over some data 
    for (int i=0; i < 9; i++)
        getField(ss);

    double belowPoverty = (stod(getField(ss)) / 100.0);
    //miscellaneous data begins
    int buildingPermits = stoi(getField(ss));
    double popForeign = (stod(getField(ss)) / 100.0);
    double landArea = stod(getField(ss));
    double popOtherLanguage = (stod(getField(ss)) / 100.0);
    double popSameHouse = (stod(getField(ss)) / 100.0);
    int manufacturerShipments = stoi(getField(ss));
    double meanCommuting = stod(getField(ss));
    double popFemale = (stod(getField(ss)) / 100.0);
    int popVeterans = stoi(getField(ss));

    //now skip over some data 
    getField(ss);

    int totalPop2014 = stoi(getField(ss));

    popForeign *= totalPop2014;
    popOtherLanguage  *= totalPop2014;
    popSameHouse *= totalPop2014;
    popFemale *= totalPop2014;
    
    miscellaneousData miscData(popFemale, popForeign, popSameHouse, meanCommuting,
                               landArea, popOtherLanguage, popVeterans, buildingPermits,
                               manufacturerShipments);    
    
    return make_shared<countyDemogData>(name, state, round(popOver65*totalPop2014), 
            round(popUnder18*totalPop2014),
            round(popUnder5*totalPop2014), 
            round(bachelorDegreeUp*totalPop2014), 
            round(highSchoolUp*totalPop2014), 
            round(belowPoverty*totalPop2014),
            miscData, 
            totalPop2014);
}

shared_ptr<hospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);
    string temp = getField(ss);
    //rating can be encoded -1 (weirdness in their encoding?)
    int overallRating = std::max(0, stoi(temp));
    rating mortal(getField(ss));
    string safety = getField(ss); //ignore for now
    rating readmit(getField(ss));

    return make_shared<cityHospitalData >(name, city, state, type, overallRating, mortal, readmit);
}

// Rewrite as one method - maybe replace typeFlag with functor on readline
void read_csv(vector<shared_ptr<placeData> > &pileOfData, std::string filename, typeFlag fileType) {
    //the actual data
    //std::vector<shared_ptr<placeData>> theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create a county info object
        while(std::getline(myFile, line)) {
            if (fileType == HOSPITAL) {
                pileOfData.push_back(readCSVLineHospital(line));
            } else if (fileType == DEMOG) {
                pileOfData.push_back(readCSVLineDemog(line));
            } else {
                cout << "ERROR exiting in file reading" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }
}