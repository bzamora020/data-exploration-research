#ifndef COMBOH_H
#define COMBOH_H

#include <memory>
#include <string>
#include <iostream>

#include "cityHospitalData.h"
#include "hospitalData.h"

/*
  aggregated hospital data for a given regional level (county or state)
 */
class comboHospitalData : public hospitalData {
public:
	//creating 2 different constructors cause i'm not sure which one i want to use yet
	comboHospitalData(string inS,string inN,shared_ptr<hospitalData> hosp,bool isCounty);
	comboHospitalData(string inS,string inN,bool isCounty);
	//adds a hospital to the combo
	void addHospital(shared_ptr<hospitalData> hospital);
	//creates the ratings for the combo based off of totals
	void makeRatings();
	string getCounty();
	string getRegion();
	string getName(){ return name; }
	double getNumH() const{ return numHospitals; }

	//friend std::ostream& operator<<(std::ostream &out, const comboHospitalData &HD);
	//getregion in combo returns the name of the aggregated region
protected:
	std::ostream& print(std::ostream &out) const override;

private:
	string name;
	string title;
	bool isCounty;
	int sumOverall;
	int sumMortality;
	int sumReadmit;
	int numOverallHosps;
	int numMortalityHosps;
	int numReadmitHosps;
	int numHospitals;
};
#endif
