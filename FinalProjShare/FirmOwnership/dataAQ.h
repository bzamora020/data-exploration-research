#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitorReport.h"

/*
  data aggregator and query for testing
 */
class dataAQ {
public:
	dataAQ();

	enum sortOrder {
		HIGHLOW = 0,
		LOWHIGH = 1
	};
	/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
	void createStateDemogData(std::vector<shared_ptr<demogData>>& theData);
	//createStateDemogData((std::vector<shared_ptr<demogData>>&)theCountyDemogData);

	void createStateHospData(std::vector<shared_ptr<hospitalData>>& theData);

	void createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData);


	static bool compareOverallRating(shared_ptr<comboHospitalData> l, shared_ptr<comboHospitalData> r){
		if(l->getOverall()==r->getOverall()){
			return l->getRegion()<r->getRegion();
		}

		return l->getOverall()<r->getOverall();
	}
	static bool compareOverallRatingReverse(shared_ptr<comboHospitalData> l, shared_ptr<comboHospitalData> r){
		if(l->getOverall()==r->getOverall()){
			return l->getRegion()<r->getRegion();
		}
		return l->getOverall()>r->getOverall();
	}
	static bool compareMortalityRating(shared_ptr<comboHospitalData> l, shared_ptr<comboHospitalData> r){
		return l->getMortality()<r->getMortality();
	}
	static bool compareReadmitRating(shared_ptr<comboHospitalData> l, shared_ptr<comboHospitalData> r){
		return l->getReadmit()<r->getReadmit();
	}
	static bool comparePoverty(shared_ptr<comboDemogData> l, shared_ptr<comboDemogData> r){
		return l->getBelowPoverty()<r->getBelowPoverty();
	}
	static bool comparePovertyReverse(shared_ptr<comboDemogData> l, shared_ptr<comboDemogData> r){
		return l->getBelowPoverty()>r->getBelowPoverty();
	}


	//return the name of the state with the largest population under age 5
	string youngestPop();
	//return the name of the state with the largest population under age 18
	string teenPop();
	//return the name of the state with the largest population over age 65
	string wisePop();
	//return the name of the state with the largest population who did not finish high school
	string underServeHS();
	//return the name of the state with the largest population who completed college
	string collegeGrads();

	string getMinTeenPop();

	string LowHospRating();
	string HighHospRating();
	string HighMortHospRating();
	string HighReadmitHospRating();

	//sort hosp rating by given order
	void sortHospRating(std::vector<comboHospitalData *>& fillVector,string regionType,sortOrder order);
	void sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow,  string regionType);
	void sortHospRatingLowHigh(std::vector<comboHospitalData  *>& hospLowToHigh,  string regionType);
	void sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state);

	//sort poverty by given order
	void sortPovLevel(std::vector<demogData *>& fillVector,sortOrder order);
	void sortDemogPovLevelLowHigh(std::vector<demogData *>& incomeHighLow);
	void sortDemogPovLevelHighLow(std::vector<demogData *>& povLevelHighLow);

	//not in parser because this is helper data
	void read_csvCityCounty(std::string filename);

	void stateReport(double thresh);

	//helper to create aggregates from city -> county
	std::map<string, string> cityToCounty;

	//state maps
	std::map<string, shared_ptr<comboDemogData>> allStateDemogData;

	std::map<string, shared_ptr<comboHospitalData>> allStateHospData;


	std::map<string, shared_ptr<comboDemogData>> getDemogs(){
		return allStateDemogData;
	}

	std::map<string, shared_ptr<comboHospitalData>> getHosps(){
		return allStateHospData;
	}

	//map for county hospital data
	std::map<string, shared_ptr<comboHospitalData>> allCountyHData;

	vector<shared_ptr<comboDemogData>> demographicsList;
	vector<shared_ptr<comboHospitalData>> stateHospitalsList;
	vector<shared_ptr<comboHospitalData>> countyHospitalsList;

};
#endif
