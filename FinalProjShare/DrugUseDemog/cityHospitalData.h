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
			hospitalData(inN, inS, "city", inType, inOverall, inMortality, inReadmit),
			city(inC) {}

		friend std::ostream& operator<<(std::ostream &out, const cityHospitalData &HD) {
			out << "Hosptial Info: " << HD.name << ", " << HD.city << ", " << HD.state;
			out << "\nType: " << HD.type;
			out << "\nOverall rating (out of 5): " << HD.overallRating;
			out << "\nmortality rating: " << HD.mortalityRating;
			out << "\nreadmission rating:" << HD.readmitRating;
			return out;
		}

		string getCity() { return city; }

	private:
		string city;
};

#endif
