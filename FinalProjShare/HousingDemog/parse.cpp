/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>

//TODO fix once you have new types 


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
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);

    //turn into mathematical percent
    double popOver65 = stod(getField(ss))/100.0;
    double popUnder18 = stod(getField(ss))/100.0;;
    double popUnder5 = stod(getField(ss))/100.0;;
    double bachelorDegreeUp = stod(getField(ss))/100.0;;
    double highSchoolUp = stod(getField(ss))/100.0;;

    //now skip over some data
    for (int i=0; i < 20; i++)
        getField(ss);

    //turn into mathematical percent
    double belowPoverty = stod(getField(ss))/100;

    //now skip over some data 
    for (int i=0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));
    //store demographic data as counts
    return make_shared<countyDemogData>(name, state, round(popOver65*totalPop2014), 
            round(popUnder18*totalPop2014),
            round(popUnder5*totalPop2014), 
            round(bachelorDegreeUp*totalPop2014), 
            round(highSchoolUp*totalPop2014), 
            round(belowPoverty*totalPop2014), 
            totalPop2014);
}

shared_ptr<housingData> readCSVLineHousing(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);


    //now skip over some data
    for (int i=0; i < 17; i++)
        getField(ss);

    double housingRate = stod(getField(ss));
    int households = stoi(getField(ss)); 
    int housingUnits = stoi(getField(ss));
    int medianValue = stoi(getField(ss));
    double personsPerHouse = stod(getField(ss));
    double multiUnit =  stod(getField(ss));

    return make_shared<housingData>(name, state, housingRate, households, housingUnits, medianValue, personsPerHouse, multiUnit);
}


/* Read one line from a CSV file for hospital data specifically */
shared_ptr<hospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);
    //string temp = getField(ss);

    int overallRate = stoi(getField(ss));
    string mortRate = getField(ss);
    string safety = getField(ss);
    string readmitRate = getField(ss);
    rating mort(mortRate), readmit(readmitRate); 

    return make_shared<cityHospitalData>(name, state, city, type, overallRate, mort, readmit);
}

void read_csv(std::vector<shared_ptr<placeData>> &pileOfData, std::string filename, typeFlag fileType) {
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
        if (fileType == DEMOG) {
            while(std::getline(myFile, line)) {
                pileOfData.push_back(readCSVLineDemog(line));
                pileOfData.push_back(readCSVLineHousing(line));
            }  
        } else if (fileType == HOSPITAL) {
            while(std::getline(myFile, line)) {
                pileOfData.push_back(readCSVLineHospital(line));
            } 
        }
        
        // Close file
        myFile.close();
    }

}