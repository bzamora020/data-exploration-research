#ifndef COMBOH_H
#define COMBOH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"

/*
  aggregated hospital data for a given regional level (county or state)
*/
class comboHospitalData : public hospitalData {
    
	public:

		comboHospitalData(string regionType, string name, string inS) : hospitalData(name, inS, regionType) {}
		void addHospitaltoRegion(shared_ptr<hospitalData> HI);


		double getNumH() const { return hospitalCount; }

	private:
	   	// counts
		int hospitalCount = 0;
		int validOverall = 0;
		int validMortality = 0;
		int validReadmit = 0;
};
#endif
