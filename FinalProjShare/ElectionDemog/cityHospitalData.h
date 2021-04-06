#ifndef CITYHOSP_H
#define CITYHOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"

using namespace std;

/*
  city hospital data for specifics of CORGIS data
*/
class cityHospitalData : public hospitalData   {
public:
	cityHospitalData(string inN, string inC, string inS, string inType, int o, rating m, rating r) :
		hospitalData(inN, inC, inS, inType, o, m, r), city(inC) {}

private:
	string city;
};

#endif
