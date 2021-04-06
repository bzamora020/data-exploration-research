#ifndef CITYHOSP_H
#define CITYHOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "hospitalData.h"

using namespace std;

/*
  city hospital data for specifics of CORGIS data
 */
class cityHospitalData : public hospitalData   {
public:
	cityHospitalData(string inN, string inC, string inS, string inType, double inOverall, string inMortality, string inReadmit) :
		hospitalData{inS,inOverall,inMortality,inReadmit},
		name(inN),city(inC), type(inType){
	}
	string getCity() const { return city; }
	string getType() const { return type; }

	virtual std::ostream& print(std::ostream &out) const override{
		out << "Hosptial Info: " << this->name << ", " << this->region;
		out << "\nType: " << this->type;
		out << "\nOverall rating (out of 5): " << this->getOverallRate();
		out << "\nmortality rating: " << this->mortality;
		out << "\nreadmission rating:" << this->readmit;
		return out;
	}
	/*friend std::ostream& operator<<(std::ostream &out, const cityHospitalData &HD){
		out << "Hosptial Info: " << HD.name << ", " << HD.region;
		out << "\nType: " << HD.type;
		out << "\nOverall rating (out of 5): " << HD.getOverallRate();
		out << "\nmortality rating: " << HD.mortality;
		out << "\nreadmission rating:" << HD.readmit;
		return out;
	}*/
private:
	string name;
	const string city;
	const string type;
};

#endif
