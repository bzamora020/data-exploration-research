/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"

#include "placeData.h"
#include "visitorReport.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#define DEBUG false

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
	 student - depends on how they map, etc. */
void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData>>& theData) {
	//process the vector in our county data aggregate 
	for (const auto &obj : theData) {

			string stateName = obj->getState();
			//if first state entry, create it
			if (allStateDemogData.count(stateName) < 1) {
					//cout << "Making a new state entry: " << stateName << endl;
					allStateDemogData[stateName] = new comboDemogData("state", stateName, stateName);
			}
			//either way now add this county info 
			//this keeps a running total
			allStateDemogData[stateName]->addDemogtoRegion(obj);
	}
}


void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData>>& theData) {
	for (const auto &obj : theData) {
		string stateName = obj->getState();

		if (allStateHospData.count(stateName) < 1) {
			//cout << "Making a new hospital entry: " << stateName << endl;
			allStateHospData[stateName] = new comboHospitalData("state", stateName, stateName);
		}
		//either way now add this county info 
		//this keeps a running total
		allStateHospData[stateName]->addHospitaltoRegion(obj);
	}
}


void dataAQ::createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData) {

	for (const auto &obj2 : theHospitalData) {
		std::shared_ptr<cityHospitalData> obj = std::static_pointer_cast<cityHospitalData>(obj2);

		string cityName = obj->getCity();
		string stateName = obj->getState();
		string countyName = cityToCounty[cityName + stateName];

		if (allCountyHData.count(countyName) < 1) {
			//cout << "Making a new hospital entry: " << countyName << endl;
			allCountyHData[countyName] = new comboHospitalData(countyName + " County", countyName, stateName);
		}
		//either way now add this county info 
		//this keeps a running total


		allCountyHData[countyName]->addHospitaltoRegion(obj);
	}
}

bool compareNameStr(comboHospitalData* left, comboHospitalData* right) {
	return left->getName() < right->getName();
}




bool compareOverallRating(std::pair<std::string, comboHospitalData *> left, std::pair<std::string, comboHospitalData *> right) {
    return left.second->getOverallRate() < right.second->getOverallRate();
}
bool compareOverallRatingVectorLowHigh(comboHospitalData * left, comboHospitalData * right) {

	rating leftTemp = left->getOverallRate();
	rating rightTemp = right->getOverallRate();

	if (leftTemp.getRatingNum() == rightTemp.getRatingNum()) {
		return compareNameStr(left, right);
	}

    return left->getOverallRate() < right->getOverallRate();
}
bool compareOverallRatingVectorHighLow(comboHospitalData * left, comboHospitalData * right) {

	rating leftTemp = left->getOverallRate();
	rating rightTemp = right->getOverallRate();

	if (leftTemp.getRatingNum() == rightTemp.getRatingNum()) {
		return compareNameStr(left, right);
	}

    return left->getOverallRate() > right->getOverallRate();
}



bool comparePovLevelLowHigh(demogData* left, demogData* right) {
    return left->getBelowPoverty() < right->getBelowPoverty();
}

bool comparePovLevelHighLow(demogData* left, demogData* right) {
    return left->getBelowPoverty() > right->getBelowPoverty();
}






void dataAQ::createComboHospVector(std::vector<comboHospitalData *>& vec, string regionType, string state) {
	std::map<std::string, comboHospitalData*>::iterator it;

	if (regionType == "state") {

		it = allStateHospData.begin();
		while (it != allStateHospData.end()) {
			if (state == "all" || it->second->getState() == state)
				vec.push_back(it->second);

			it++;
		}
	}
	if (regionType == "county") {

		it = allCountyHData.begin();
		while (it != allCountyHData.end()) {
			if (state == "all" || it->second->getState() == state)
				vec.push_back(it->second);

			it++;
		}
	}

}

void dataAQ::createComboDemogVector(std::vector<demogData*>& vec) {
	std::map<std::string, comboDemogData*>::iterator it = allStateDemogData.begin();
	// no county data yet

	while (it != allStateDemogData.end()) {
		vec.push_back(it->second);
		it++;
	}
}


void dataAQ::sortHospRatingLowHigh(std::vector<comboHospitalData *>& hospLowToHigh, 
	string regionType) {

	createComboHospVector(hospLowToHigh, regionType, "all");

	std::sort(hospLowToHigh.begin(), hospLowToHigh.end(), compareOverallRatingVectorLowHigh);
}


void dataAQ::sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow, 
	string regionType) {

	createComboHospVector(hospHighToLow, regionType, "all");

	std::sort(hospHighToLow.begin(), hospHighToLow.end(), compareOverallRatingVectorHighLow);
}


/* for a specific state... */
void dataAQ::sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state) {

	createComboHospVector(hospHighToLow, "county", state);

	std::sort(hospHighToLow.begin(), hospHighToLow.end(), compareOverallRatingVectorHighLow);
	
}




 void dataAQ::sortDemogPovLevelLowHigh(std::vector<demogData *>& povLevelLowHigh) {

	 createComboDemogVector(povLevelLowHigh);

	 sort(povLevelLowHigh.begin(), povLevelLowHigh.end(), comparePovLevelLowHigh);
	 

}




 void dataAQ::sortDemogPovLevelHighLow(std::vector<demogData *>& povLevelHighLow) {

	 createComboDemogVector(povLevelHighLow);

	 sort(povLevelHighLow.begin(), povLevelHighLow.end(), comparePovLevelHighLow);

}



/*functions to parse city to county helper map */
void dataAQ::read_csvCityCounty(std::string filename) {

		// Create an input filestream
		std::ifstream myFile(filename);

		// Make sure the file is open
		if(!myFile.is_open()) {
				throw std::runtime_error("Could not open file");
		}

		if(myFile.good()) {
				consumeColumnNames(myFile);

				// Helper vars
				std::string line, state, junk;

				// Now read data, line by line and enter into the map
				while(std::getline(myFile, line)) {

					std::stringstream ss(line);

					string city = getFieldNQ(ss);
					state = getFieldNQ(ss);
					junk = getFieldNQ(ss);
					string county = getFieldNQ(ss);

					string cityKey = city+state;

					cityToCounty[cityKey] = county;

					//cout << "line: " << line << endl;
					//cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
				}

				// Close file
				myFile.close();
		}

}


// reports

void dataAQ::stateReport(double thresh) {
	std::map<string, comboDemogData*>::iterator itDemog;
	std::map<string, comboHospitalData*>::iterator itHosp;

	VisitorReport visitor;
	int count = 0;

	for (itDemog = allStateDemogData.begin(); itDemog != allStateDemogData.end(); itDemog++) {
		if (itDemog->second->getBelowPoverty() > thresh) {
			itDemog->second->accept(visitor);

			allStateHospData.at(itDemog->second->getState())->accept(visitor);
			count += 1;
		}
	}

	cout << "\nGenerated a report for a total of: " << count << endl;
}