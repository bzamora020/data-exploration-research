#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "visitor.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <algorithm>

using namespace std;

class visitorCombineCounty : public Visitor {
public:
	visitorCombineCounty(string filename):Visitor{}{

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
			vector<string> counties;
			while(std::getline(myFile, line)) {

				std::stringstream ss(line);

				string city = getFieldNQ(ss);
				state = getFieldNQ(ss);
				junk = getFieldNQ(ss);
				string county = getFieldNQ(ss);
				county=county+state;
				string cityKey = city+state;
				if(std::find(counties.begin(), counties.end(), county) == counties.end()) {
    				counties.push_back(county);
				}
				if(county!="")
					cityToCounty[cityKey] = county;
			}
			//cout<<"Unique Counties: "<<counties.size()<<endl;
			// Close file
			myFile.close();
		}
	}

	//visit
	virtual void visit(shared_ptr<hospitalData> h){
		shared_ptr<cityHospitalData> hospital= static_pointer_cast<cityHospitalData>(h);
		string county=cityToCounty[hospital->getCity()+hospital->getState()];
		//if the hospital isn't already in the list, add it to the list
		if(allCountyHData.find(county)==allCountyHData.end()){
			allCountyHData[county]=new comboHospitalData(hospital->getState(),county,hospital,true);
			countyHospitalsList.push_back(allCountyHData[county]);
		}
		//if the hospital is already in the list, add the new county's data
		else{
			allCountyHData[county]->addHospital(hospital);
		}
		/*TODO add to statTool later
		for(auto county:countyHospitalsList){
			county->makeRatings();
		}
		 */
	}

	virtual void visit(shared_ptr<demogData> d){
		shared_ptr<countyDemogData> d2=static_pointer_cast<countyDemogData>(d);
		vector<string> badNames;
		badNames.push_back(" County");
		string county=d2->getCounty();
		std::size_t found = 0;
		for(auto str:badNames){
			found = county.find(str);
			if(found!=std::string::npos)break;
		}
		if(found!=std::string::npos){
			county.erase(county.begin()+found, county.end());
		}
		//cout<<county<<endl;
		string countyState=county+d2->getState();

		comboDemogData* demog = new comboDemogData(d2->getState(),d2);
		allCountyDData[countyState]=demog;
		countyDemogsList.push_back(demog);
	}

	//getters
	std::map<string, comboDemogData*> countyDmap() { return allCountyDData; }
	comboDemogData* countyDmapEntry(string countyN) { return allCountyDData[countyN]; }

	std::map<string, comboHospitalData*> countyHmap() { return allCountyHData; }
	comboHospitalData* countyHmapEntry(string countyN) { return allCountyHData[countyN]; }

	vector<comboHospitalData*> getHList(){ return countyHospitalsList; }

	~visitorCombineCounty(){
		for(auto data:countyDemogsList){
			delete data;
		}
		for(auto data:countyHospitalsList){
			delete data;
		}
	}
private:
	//map for county name to demog data
	std::map<string, comboDemogData*> allCountyDData;
	//map for county hospital data
	std::map<string, comboHospitalData*> allCountyHData;

	//helper map to create aggregates from city -> county
	std::map<string, string> cityToCounty;

	vector<comboDemogData*> countyDemogsList;
	vector<comboHospitalData*> countyHospitalsList;
};

#endif
