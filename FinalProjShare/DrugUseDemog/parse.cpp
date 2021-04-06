/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

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
    return make_shared<demogData>(name, state, "county", round(popOver65*totalPop2014), 
            round(popUnder18*totalPop2014),
            round(popUnder5*totalPop2014), 
            round(bachelorDegreeUp*totalPop2014), 
            round(highSchoolUp*totalPop2014), 
            round(belowPoverty*totalPop2014), 
            totalPop2014);
}


//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 

std::vector<shared_ptr<placeData> >read_csv(std::vector<shared_ptr<placeData>>& pileOfData, std::string filename, typeFlag fileType) {
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

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                pileOfData.push_back(readCSVLineDemog(line));
            
            } else if (fileType == HOSPITAL) {
                pileOfData.push_back(readCSVLineHospital(line));

            } else if (fileType == DRUG) {
                pileOfData.push_back(readCSVLineDrug(line));
                
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    return pileOfData;
}

/* Read one line from a CSV file for hospital data specifically */
shared_ptr<cityHospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);

    double overallRating = stod(getField(ss));
    string mortalityRating = getField(ss);

    //skip safety rating
    getField(ss);

    string readmitRating = getField(ss);
 
    return make_shared<cityHospitalData>(name, city, state, type, overallRating,
        mortalityRating, readmitRating);
}

shared_ptr<drugData> readCSVLineDrug(std::string theLine) {

    // state #1	 	
    // Population.18-25 #5 498410
    // Pain Relievers Dependence 18-25 #11 6469
    // Alchohol binge past 18-25 column #76 17429
    // Illicit Drug Cocaine Rates 18-25 #99 2736
    // Marijuana Rates 18-25 #120

    std::stringstream ss(theLine);
    
    string state = getField(ss);

    //now skip over some data
    for (int i=0; i < 3; i++){ //LOOP WORKS!!!
        getField(ss);
    }

    int pop18to25 = stoi(getField(ss));

    //now skip over some data
    for (int i=0; i < 5; i++){
        getField(ss);
    }

    int painrd18to25 = stoi(getField(ss));

    //now skip over some data
    for (int i=0; i < 64; i++){
        getField(ss);
    }
    
    int alcho18to25 = stoi(getField(ss));

    //now skip over some data
    for (int i=0; i < 22; i++){
        getField(ss);
    }

    int coc18to25 = stoi(getField(ss));

    //now skip over some data
    for (int i=0; i < 20; i++){
        getField(ss);
    }

    int weed18to25 = stoi(getField(ss));


    //cout << state << " " << pop18to25 << " "<< alcho18to25 << " "<< coc18to25 << " "<< painrd18to25 << endl;
 
    return make_shared<drugData>("state", state, state, 
        pop18to25, alcho18to25, coc18to25, painrd18to25, weed18to25);
        
}

