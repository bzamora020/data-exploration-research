
#include "comboHospitalData.h"

#include <sstream>
#include <string>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include "visitor.h"


comboHospitalData::comboHospitalData(string inS,string inN,shared_ptr<hospitalData> hosp,bool isC) : hospitalData{inS},
name(inN),
isCounty(isC),
sumOverall(0),
sumMortality(0),
sumReadmit(0),
numOverallHosps(0),
numMortalityHosps(0),
numReadmitHosps(0),
numHospitals(0)
{

	if(isCounty){
		title = getCounty()+" County in "+region;
	}else{
		title = region;
	}
	addHospital(hosp);
}

comboHospitalData::comboHospitalData(string inS,string inN,bool isC) : hospitalData{inS},
		name(inN),
		isCounty(isC),
		sumOverall(0),
		sumMortality(0),
		sumReadmit(0),
		numOverallHosps(0),
		numMortalityHosps(0),
		numReadmitHosps(0),
		numHospitals(0){}

//note this stores a running total until averageOut
//just adds the current county info to the running total
void comboHospitalData::addHospital(shared_ptr<hospitalData> hospital) {
	//make sure the rating isn't N/A before adding
	if(!hospital->getOverall().isEmpty()){
		sumOverall+=hospital->getOverallRate();
		numOverallHosps++;
	}
	//cout<<"  |  "<<hospital->/*getMortalityStr();*/getMortalityNum();
	if(!hospital->getMortality().isEmpty()){
		sumMortality+=hospital->getMortalityNum();
		numMortalityHosps++;
	}
	//cout<<"  |  "<<hospital->/*getReadmitStr();*/getReadmitNum();
	if(!hospital->getReadmit().isEmpty()){
		sumReadmit+=hospital->getReadmitNum();
		numReadmitHosps++;
	}
	//cout<<endl;
	numHospitals++;
}
void comboHospitalData::makeRatings(){
	overall.setNumRating(sumOverall/(double)numOverallHosps);
	mortality.setNumRating(sumMortality/(double)numMortalityHosps);
	readmit.setNumRating(sumReadmit/(double)numReadmitHosps);
}
string comboHospitalData::getCounty(){
	return name.substr(0,name.length()-2);
}
string comboHospitalData::getRegion(){
	if(isCounty){
		return getCounty()+" County";
	}
	else{
		return getState();
	}
}

std::ostream& comboHospitalData::print(std::ostream &out) const{
	out << "Combined hospital data at level: " << this->title;
	out << "\nincludes num hospitals: " << this->numHospitals;
	out << "\nOverall rating (out of 5): " << this->getOverallRate();
	out << "\nmortality rating: " << this->mortality;
	out << " num " << this->mortality.getRatingNum();
	out << "\nreadmit rating: " << this->readmit;
	out << " num " << this->readmit.getRatingNum();
	return out;
}
/*
std::ostream& operator<<(std::ostream &out, const comboHospitalData &HD) {
	out << "Regional Hospital info: " << HD.region;
	out << "\nNumber of hospitals: " << HD.numHospitals;
	//out<< "\n[for debug]sumOverall: "<< HD.sumOverall;
	//out<< "\n[for debug]numOverallHosps: "<<HD.numOverallHosps;
	out << "\noverall rating: " << HD.getOverallRate();
	//out << "\n[for debug]mortality rating num: " << HD.mortality.getRating();
	out << "\nmortality rating: " << HD.mortality;
	//out << "\n[for debug]readmission rating: " << HD.readmit.getRating();
	out << "\nreadmission rating: " << HD.readmit;
	return out;
}*/
