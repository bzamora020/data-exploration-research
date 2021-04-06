/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "parse.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#define DEBUG false

using namespace std;

dataAQ::dataAQ() {}

//TODO fill in with your lab03 solutions but use the new data types!

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
			county=county+state;
			string cityKey = city+state;

			cityToCounty[cityKey] = county;
			//cout << "line: " << line << endl;
			//cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
		}

		// Close file
		myFile.close();
	}

}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData>>& theData) {
	for(auto demog:theData){
		//if the state isn't already in the list, add it to the list
		if(allStateDemogData.find(demog->getState())==allStateDemogData.end()){
			allStateDemogData[demog->getState()]=make_shared<comboDemogData>(demog->getState(),demog);
			demographicsList.push_back(allStateDemogData[demog->getState()]);
		}
		//if the state is already in the list, add the new county's data
		else{
			allStateDemogData[demog->getState()]->addDemog(demog);
		}
	}

}

void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData>>& theData) {
	for(auto hospital:theData){
		//if the hospital isn't already in the list, add it to the list
		if(allStateHospData.find(hospital->getState())==allStateHospData.end()){
			allStateHospData[hospital->getState()]=make_shared<comboHospitalData>(hospital->getState(),hospital->getState(),hospital,false);
			stateHospitalsList.push_back(allStateHospData[hospital->getState()]);
		}
		//if the hospital is already in the list, add the new county's data
		else{
			allStateHospData[hospital->getState()]->addHospital(hospital);
		}
	}
	for(auto state:stateHospitalsList){
		state->makeRatings();
	}
}

void dataAQ::createCountyHospData(std::vector<shared_ptr<hospitalData>>& theData) {
	read_csvCityCounty("simple_uscities.csv");
	for(auto place:theData){
		auto hospital = static_pointer_cast<cityHospitalData>(place);
		string county=cityToCounty[hospital->getCity()+hospital->getState()];
		//if the hospital isn't already in the list, add it to the list
		if(allCountyHData.find(county)==allCountyHData.end()){
			allCountyHData[county]=make_shared<comboHospitalData>(hospital->getState(),county,hospital,true);
			countyHospitalsList.push_back(allCountyHData[county]);
		}
		//if the hospital is already in the list, add the new county's data
		else{
			allCountyHData[county]->addHospital(hospital);
		}
	}
	for(auto county:countyHospitalsList){
		county->makeRatings();
	}
}

//return the name of the state with the largest population under age 5
std::string dataAQ::youngestPop(){
	//save the first state in the list
	shared_ptr<comboDemogData> save=allStateDemogData.begin()->second;
	for(auto state:allStateDemogData){
		//check if the iterated state has a better value
		if(state.second->getpopUnder5Count()>save->getpopUnder5Count())
			save=state.second;
	}
	return save->getState();
}
//return the name of the state with the largest population under age 18
std::string dataAQ::teenPop(){
	//save the first state in the list
	shared_ptr<comboDemogData> save=allStateDemogData.begin()->second;
	for(auto state:allStateDemogData){
		//check if the iterated state has a better value
		if(state.second->getpopUnder18Count()>save->getpopUnder18Count())
			save=state.second;
	}
	return save->getState();
}
//return the name of the state with the largest population over age 65
std::string dataAQ::wisePop(){
	//save the first state in the list
	shared_ptr<comboDemogData> save=allStateDemogData.begin()->second;
	for(auto state:allStateDemogData){
		//check if the iterated state has a better value
		if(state.second->getpopOver65Count()>save->getpopOver65Count())
			save=state.second;
	}
	return save->getState();
}
//return the name of the state with the largest population who did not finish high school
std::string dataAQ::underServeHS(){
	//save the first state in the list
	shared_ptr<comboDemogData> save=allStateDemogData.begin()->second;
	for(auto state:allStateDemogData){
		//check if the iterated state has a better value
		if(state.second->getHSupCount()<save->getHSupCount())
			save=state.second;
	}
	return save->getState();
}
//return the name of the state with the largest population who completed college
std::string dataAQ::collegeGrads(){
	//save the first state in the list
	shared_ptr<comboDemogData> save=allStateDemogData.begin()->second;
	for(auto state:allStateDemogData){
		//check if the iterated state has a better value
		if(state.second->getBAupCount()>save->getBAupCount())
			save=state.second;
	}
	return save->getState();
}

string dataAQ::LowHospRating(){
	shared_ptr<comboHospitalData> toReturn =
			*min_element(stateHospitalsList.begin(),stateHospitalsList.end(),compareOverallRating);
	return toReturn->getState();
}
string dataAQ::HighHospRating(){
	shared_ptr<comboHospitalData> toReturn =
			*max_element(stateHospitalsList.begin(),stateHospitalsList.end(),compareOverallRating);
	return toReturn->getState();
}
string dataAQ::HighMortHospRating(){
	shared_ptr<comboHospitalData> toReturn =
			*max_element(stateHospitalsList.begin(),stateHospitalsList.end(),compareMortalityRating);
	return toReturn->getState();
}
string dataAQ::HighReadmitHospRating(){
	shared_ptr<comboHospitalData> toReturn =
			*max_element(stateHospitalsList.begin(),stateHospitalsList.end(),compareReadmitRating);
	return toReturn->getState();
}

void dataAQ::sortHospRating(std::vector<comboHospitalData *>& fillVector,string regionType,sortOrder order){
	vector<shared_ptr<comboHospitalData>> toSort;
	//if it's by state i want to sort all the states
	if(regionType=="state"){
		//fill toSort vector with all of the states
		toSort=stateHospitalsList;
	}
	//otherwise it's sorting by counties in a state
	else{
		//populate toSort vector with all counties in wanted state
		for(auto county:countyHospitalsList){
			if(county->getState()==regionType){
				//cout<<county->getCounty()<<" "<<county->getOverallRate()<<endl;
				if(!county->getOverall().isEmpty())
					toSort.push_back(county);
			}
		}
	}
	//sort by correct order
	if(order==HIGHLOW){
		sort(toSort.begin(),toSort.end(),compareOverallRatingReverse);
	}else{
		sort(toSort.begin(),toSort.end(),compareOverallRating);
	}
	//fill the given vector with the first 10 results in the sorted vector
	for(int i=0;i<(int)toSort.size();i++){
		if(i>=(int)toSort.size())
			break;
		fillVector.push_back(toSort[i].get());
	}
}

/* Lab04 fill in */
void dataAQ::sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow,  string regionType){
	//sort all the counties
	sortHospRating(hospHighToLow,regionType,HIGHLOW);

}
void dataAQ::sortHospRatingLowHigh(std::vector<comboHospitalData  *>& hospLowToHigh,  string regionType){
	sortHospRating(hospLowToHigh,regionType,LOWHIGH);
}

void dataAQ::sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state){
	sortHospRating(hospHighToLow,state,HIGHLOW);
}


void dataAQ::sortPovLevel(std::vector<demogData *>& fillVector,sortOrder order){
	if(order==HIGHLOW){
		sort(demographicsList.begin(),demographicsList.end(),comparePovertyReverse);
	}else{
		sort(demographicsList.begin(),demographicsList.end(),comparePoverty);
	}
	//fill the given vector with the first 10 results in the sorted vector
	for(int i=0;i<(int)demographicsList.size();i++){
		fillVector.push_back(demographicsList[i].get());
	}
}
void dataAQ::sortDemogPovLevelLowHigh(std::vector<demogData *>& incomeHighLow){
	sortPovLevel(incomeHighLow,LOWHIGH);
}
void dataAQ::sortDemogPovLevelHighLow(std::vector<demogData *>& povLevelHighLow){
	sortPovLevel(povLevelHighLow,HIGHLOW);
}

void dataAQ::stateReport(double thresh){
	//create sorted vector of states by poverty
	std::vector<demogData*> povSort;
	sortDemogPovLevelHighLow(povSort);

	int counter=0;

	visitorReport report;
	for(demogData* demog:povSort){
		//if one is less than threshhold, all future states in vector will be too
		if(demog->getBelowPoverty()<thresh){
			break;
		}
		cout<<"\nSpecial report demog Data:";
		demog->accept(report);
		cout<<"\nSpecial report hospital data:";
		allStateHospData[demog->getState()]->accept(report);
		counter++;
	}
	cout<<"\nGenerated a report for a total of: "<<counter<<endl;
}


