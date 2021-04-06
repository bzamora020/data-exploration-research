/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>
#include "placeData.h"

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
    for (int i=0; i < 4; i++)
        getField(ss);
 
    double native = stod(getField(ss))/100.0;
    double asian = stod(getField(ss))/100.0;
    double black = stod(getField(ss))/100.0;
    double hisp = stod(getField(ss))/100.0;
    double haw = stod(getField(ss))/100.0;
    double mix = stod(getField(ss))/100.0;
    double white = stod(getField(ss))/100.0;
    double onlywhite = stod(getField(ss))/100.0;
    
 
    for (int i=0; i < 8; i++)
        getField(ss);
    //turn into mathematical percent
    double belowPoverty = stod(getField(ss))/100;
 
    //now skip over some data 
    for (int i=0; i < 10; i++)
        getField(ss);
    
    // cout<<"county: "<<name<<", "<<state<<endl;
    // cout<<"native: "<<native<<endl;
    // cout<<"only white: "<<onlywhite<<endl;
    // cout<<"below Pov: "<<belowPoverty<<endl;
    // cout<<endl;
    int totalPop2014 = stoi(getField(ss));
    RacialData r{native*totalPop2014, asian*totalPop2014, black*totalPop2014, hisp*totalPop2014, haw*totalPop2014, mix*totalPop2014, white*totalPop2014, onlywhite*totalPop2014};
    //store demographic data as counts
    return make_shared<countyDemogData>(name, state, round(popOver65*totalPop2014), 
            round(popUnder18*totalPop2014),
            round(popUnder5*totalPop2014), 
            round(bachelorDegreeUp*totalPop2014), 
            round(highSchoolUp*totalPop2014), 
            round(belowPoverty*totalPop2014), 
            totalPop2014, r);

}


//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 
void read_csv(vector<shared_ptr<placeData> > &pileOfData, std::string filename, typeFlag fileType) {
    //the actual data
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
            }
            else if(fileType == HOSPITAL){
                pileOfData.push_back(readCSVLineHospital(line));
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

/* Read one line from a CSV file for hospital data specifically */
shared_ptr<hospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);
    // string temp = getField(ss);
 
    //TODO you need to read rating data
//    cout << getField(ss) << endl;
    // cout << temp << endl;
    int overall = stoi(getField(ss));
    rating mort{getField(ss)};
    getField(ss);
    rating readmit{getField(ss)};

    return make_shared<cityHospitalData>(overall, mort, readmit, name, type, state, city);
}

std::vector<shared_ptr<hospitalData>> read_csvHospital(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<hospitalData>> theData;

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


