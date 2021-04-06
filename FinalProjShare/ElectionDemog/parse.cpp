/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>
#include "rating.h"
#include "electionData.h"

using namespace std;

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

string getFieldNQ(std::stringstream& ss) {
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

void readCandidateNames(std::ifstream& myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);
    for (int i = 0; i < 3; i++)
        getField(ss);
    std::string name;
    name = getField(ss);
    name = name.substr(10, name.find_last_of(".") - 10);
    electionData::candidateNames.push_back(name);
    while (name.compare("Uncommitted") != 0) {
        getField(ss);
        getField(ss);
        name = getField(ss);
        name = name.substr(10, name.find_last_of(".") - 10);
        electionData::candidateNames.push_back(name);
    }
}

//read from a CSV file (for a given data type) return a vector of the data
void read_csv(std::vector<shared_ptr<placeData>> &pileOfData, std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<placeData> > theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        if(fileType != ELECTION)
            consumeColumnNames(myFile);
        else
            readCandidateNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                pileOfData.push_back(readCSVLineDemog(line));
            }
            else if (fileType == HOSPITAL) {
                pileOfData.push_back(readCSVLineHospital(line));
            }
            else if (fileType == ELECTION) {
                pileOfData.push_back(readCSVLineElection(line));
            }
            else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }
        // Close file
        myFile.close();
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);

    string name = getField(ss);
    string state = getField(ss);

    //turn into mathematical percent
    double popOver65 = stod(getField(ss)) / 100.0;
    double popUnder18 = stod(getField(ss)) / 100.0;
    double popUnder5 = stod(getField(ss)) / 100.0;
    double bachelorDegreeUp = stod(getField(ss)) / 100.0;
    double highSchoolUp = stod(getField(ss)) / 100.0;

    //now skip over some data
    for (int i = 0; i < 20; i++)
        getField(ss);

    //turn into mathematical percent
    double belowPoverty = stod(getField(ss)) / 100;

    //now skip over some data 
    for (int i = 0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));

    //store demographic data as counts
    return make_shared<demogData>(name, state, round(popOver65 * totalPop2014),
        round(popUnder18 * totalPop2014),
        round(popUnder5 * totalPop2014),
        round(bachelorDegreeUp * totalPop2014),
        round(highSchoolUp * totalPop2014),
        round(belowPoverty * totalPop2014),
        totalPop2014);
}

/* Read one line from a CSV file for hospital data specifically */
shared_ptr<hospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);
    //string temp = getField(ss);
    string overall = getField(ss);
    string mortality = getField(ss);
    string safety = getField(ss);
    string readmission = getField(ss);

    int o;
    try {o = stoi(overall);} 
    catch (const std::invalid_argument& e) {}
    catch (const std::out_of_range& e) {}
    rating *m = new rating(mortality);
    rating *r = new rating(readmission);

    return make_shared<cityHospitalData>(name, city, state, type, o, *m, *r);
}

shared_ptr<electionData> readCSVLineElection(std::string theLine) {
    std::stringstream ss(theLine);
    string name = getField(ss);
    if (name.find("County") == string::npos){
        name += " County";
    }
    getField(ss);
    string state = getField(ss);
    shared_ptr<electionData> elecD = make_shared<electionData>(name, state);
    for (int i = 0; i < electionData::candidateNames.size(); i++) {
        int total = 0;
        try { total = stoi(getField(ss)); }
        catch (const std::invalid_argument& e) {}
        catch (const std::out_of_range& e) {}
        string party = getField(ss);
        /*
        double percent = 0;
        try { percent = stod(getField(ss)); }
        catch (const std::invalid_argument& e) {}
        catch (const std::out_of_range& e) {}
        */
        getField(ss); //skipping percent
        name = electionData::candidateNames.at(i);
        elecD->addCandidate(make_shared<candidate>(name, total, party));
    }
    return elecD;
}

//read from a CSV file (for a given data type) return a vector of the 
//hospital data
// DO NOT modify 
std::vector<shared_ptr<hospitalData> > read_csvHospital(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<hospitalData> > theData;

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
            theData.push_back(readCSVLineHospital(line));
        }

        // Close file
        myFile.close();
    }

    return theData;
}
