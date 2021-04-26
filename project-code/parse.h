
#ifndef PARSE_H
#define PARSE_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // std::stringstream
#include "demogData.h"
#include "hospitalData.h"
#include "shootingData.h"

/*static functions to help parse CSV data */

/* For future assignments when we read different types of data */
enum typeFlag {
	DEMOG = 0,
	HOSPITAL = 1,
	POLICE = 2,
	SHOOTING = 3,
};

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) ;

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss);

//for city to county helper
string getFieldNQ(std::stringstream &ss);

//for alt city to county csv
string getFieldNL(std::stringstream &ss);

//for last entry of a csv
string getFieldEND(std::stringstream &ss);

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile);

// Read one line from a CSV file for county demographic data specifically
shared_ptr<demogData> readCSVLineDemog(std::string theLine);

// Functions to read a CSV file - specific to data type - hospital data
shared_ptr<hospitalData> readCSVLineHopstial(std::string theLine);

shared_ptr<shootingData> readCSVLineShooting(std::string theLine);

void read_csv(std::vector<shared_ptr<placeData>> &dataV, std::string filename, typeFlag fileType);

#endif
