#ifndef COMBOH_H
#define COMBOH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"
#include <vector>

using namespace std;

/*
  aggregated hospital data for a given regional level (county or state)
*/
class comboHospitalData : public hospitalData {
public:
	comboHospitalData(string r, string s) : hospitalData(s), region(r), numHosp(0) {}
	void addHospitaltoRegion(shared_ptr<hospitalData> HI);
	string getRegion() {
		return region;
	}
	double getNumH() const {return numHosp;}
	vector<shared_ptr<hospitalData>> getCounties() { return counties; }

private:
	vector<shared_ptr<hospitalData>> counties;
	string region;
	double numHosp;
};
#endif