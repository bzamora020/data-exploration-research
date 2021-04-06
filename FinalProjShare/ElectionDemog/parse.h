
#ifndef PARSE_H
#define PARSE_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // std::stringstream
#include "demogData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "electionData.h"

/*static functions to help parse CSV data */

/* For future assignments when we read different types of data */
enum typeFlag {
	DEMOG = 0,
	HOSPITAL = 1,
	ELECTION = 2
};

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) ;

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss);
string getFieldNQ(std::stringstream& ss);

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile);

//read from a CSV file (for a given data type) return a vector of the data
void read_csv(std::vector<shared_ptr<placeData>> &pileOfData, std::string filename, typeFlag fileType);

// Read one line from a CSV file for county demographic data specifically
shared_ptr<demogData> readCSVLineDemog(std::string theLine);

// Functions to read a CSV file - specific to data type - hospital data
shared_ptr<hospitalData> readCSVLineHospital(std::string theLine);
std::vector<shared_ptr<hospitalData> > read_csvHospital(std::string filename, typeFlag fileType);

shared_ptr<electionData> readCSVLineElection(std::string theLine);

void readCandidateNames(std::ifstream& myFile);

#endif
