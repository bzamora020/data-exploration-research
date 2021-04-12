/* helper routines to read out csv data */
#include "parse.h"
#include "placeData.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "shootingData.h"
#include "cityShootingData.h"
#include "comboShootingData.h"
#include <algorithm>
#include <cmath>

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp)
{
    temp.erase(
        remove(temp.begin(), temp.end(), '\"'),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss)
{
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

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

// New getField function for potential new city to county csv
string getFieldNL(std::stringstream &ss)
{
    string temp;
    std::getline(ss ,temp, '|');
    return temp;
}


/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile)
{
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while (std::getline(ss, colname, ','))
    {
        //std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine)
{
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
    for (int i = 0; i < 11; i++)
        getField(ss);

    /* double native = stod(getField(ss))/100.0;
    double asian = stod(getField(ss))/100.0;
    double black = stod(getField(ss))/100.0;
    double hisp = stod(getField(ss))/100.0;
    double haw = stod(getField(ss))/100.0;
    double mix = stod(getField(ss))/100.0;
    double white = stod(getField(ss))/100.0;
    double onlywhite = stod(getField(ss))/100.0; */

    //now skip over some data
    for (int i = 0; i < 9; i++)
        getField(ss);

    double belowPoverty = stod(getField(ss)) / 100;

    //now skip over some data
    for (int i = 0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));

    return make_shared<countyDemogData>(name, state, round(popOver65 * totalPop2014),
                                        round(popUnder18 * totalPop2014),
                                        round(popUnder5 * totalPop2014),
                                        round(bachelorDegreeUp * totalPop2014),
                                        round(highSchoolUp * totalPop2014),
                                        round(belowPoverty * totalPop2014),
                                        totalPop2014);
}

shared_ptr<hospitalData> readCSVLineHospital(std::string theLine)
{
    std::stringstream ss(theLine);

    string name = getField(ss);
    string city = getField(ss);
    string state = getField(ss);
    string type = getField(ss);
    string temp = getField(ss);
    //rating can be encoded -1 (weirdness in their encoding?)
    int overallRating = std::max(0, stoi(temp));
    rating mortal(getField(ss));
    string safety = getField(ss); //ignore for now
    rating readmit(getField(ss));

    return make_shared<cityHospitalData>(name, city, state, type, overallRating, mortal, readmit);
}

shared_ptr<shootingData> readCSVLineShooting(std::string theLine)
{
    std::stringstream ss(theLine);

    string personName = getField(ss);
    int age = stoi(getField(ss));
    string gender = getField(ss);
    string race = getField(ss);

    for (int i = 0; i < 4; i++)
    {
        getField(ss);
    }
    string cityName = getField(ss);
    // cout << cityName << endl;
    string stateName = getField(ss);

    string skippedFactor1 = getField(ss);

    string MI = getField(ss);
    /*
    bool MI = 0;
    if (tmp.compare("True") == 0)
    {
        bool MI = true;
        cout << "was true: " << MI << endl;
    }
    else
    {
        bool MI = false;
        //cout << "twas false" << endl;
    }
*/
    string skippedFactor2 = getField(ss);
    string fleeting = getField(ss);

    return make_shared<cityShootingData>(stateName, cityName, age, race, gender, MI, fleeting);
}
// Rewrite as one method - maybe replace typeFlag with functor on readline
void read_csv(std::vector<shared_ptr<placeData>> &dataV, std::string filename, typeFlag fileType)
{ // I think I fixed this
    //the actual data
    // std::vector<shared_ptr<placeData>> theData = dataV; //Replaced by input of placeData

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    if (myFile.good())
    {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create a county info object
        while (std::getline(myFile, line))
        {
            if (fileType == HOSPITAL)
            {
                dataV.push_back(readCSVLineHospital(line));
            }
            else if (fileType == DEMOG)
            {
                dataV.push_back(readCSVLineDemog(line));
            }
            else if (fileType == SHOOTING)
            {
                dataV.push_back(readCSVLineShooting(line));
            }
            else
            {
                cout << "ERROR exiting in file reading" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    // return theData;
}
