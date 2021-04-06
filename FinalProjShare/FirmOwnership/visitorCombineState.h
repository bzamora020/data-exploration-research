#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "visitor.h"
#include <memory>
#include <iostream>

class visitorCombineState : public Visitor {
	//TODO fill in
public:
	//visits
	virtual void visit(shared_ptr<hospitalData> hospital){
		//if the hospital isn't already in the list, add it to the list
		if(allStateHospData.find(hospital->getState())==allStateHospData.end()){
			allStateHospData[hospital->getState()]=new comboHospitalData(hospital->getState(),hospital->getState(),hospital,false);
			stateHospitalsList.push_back(allStateHospData[hospital->getState()]);
		}
		//if the hospital is already in the list, add the new county's data
		else{
			allStateHospData[hospital->getState()]->addHospital(hospital);
		}
	}
	virtual void visit(shared_ptr<demogData> demog){
		//if the state isn't already in the list, add it to the list
		if(allStateDemogData.find(demog->getState())==allStateDemogData.end()){

			allStateDemogData[demog->getState()]=new comboDemogData(demog->getState(),demog);
			demographicsList.push_back(allStateDemogData[demog->getState()]);
		}
		//if the state is already in the list, add the new county's data
		else{
			allStateDemogData[demog->getState()]->addDemog(demog);
		}
	}

	//getters
	std::map<string, comboDemogData*> stateDmap(){ return allStateDemogData; }
	comboDemogData* stateDmapEntry(string stateN){ return allStateDemogData[stateN]; }
	std::map<string, comboHospitalData*> stateHmap() const{ return allStateHospData; }
	comboHospitalData* stateHmapEntry(string stateN) { return allStateHospData[stateN]; }
	vector<comboHospitalData*> getHList(){ return stateHospitalsList; }
	~visitorCombineState(){
		for(auto data:demographicsList){
			delete data;
		}
		for(auto data:stateHospitalsList){
			delete data;
		}
	}
private:
	//state maps
	std::map<string, comboDemogData*> allStateDemogData;
	std::map<string, comboHospitalData*> allStateHospData;
	vector<comboDemogData*> demographicsList;
	vector<comboHospitalData*> stateHospitalsList;
};

#endif
