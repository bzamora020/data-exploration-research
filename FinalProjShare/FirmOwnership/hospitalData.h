#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "placeData.h"
#include <limits>

using namespace std;

/*
  class to represent hospital data
 */
class hospitalData : public placeData  {
public:
	hospitalData(string inS) :
		placeData{inS}, overall(0),
		mortality(0), readmit(0){
	}
	hospitalData(string inS, double inOverall, string inMortality, string inReadmit) :
		placeData{inS}, overall(inOverall),
		mortality(inMortality), readmit(inReadmit){
	}


	rating getOverall() const { return overall; }
	rating getMortality() const { return mortality; }
	rating getReadmit() const { return readmit; }

	string getMortalityStr() const { return mortality.getRating(); }
	string getReadmitStr() const { return readmit.getRating(); }

	double getOverallRate() const {
		return overall.getRatingNum();
	}
	int getMortalityNum() const { return mortality.getRatingNum(); }
	int getReadmitNum() const { return readmit.getRatingNum(); }

	std::ostream& print(std::ostream &out) const override{
		return out;
	}

	virtual void accept(class Visitor &v) override;

protected:
	rating overall;
	rating mortality;
	rating readmit;
};

#endif
