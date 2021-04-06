#ifndef CDEMOG_H
#define CDEMOG_H

#include <string>
#include <iostream>
#include "demogData.h"

using namespace std;

/*
  county demographic data used to represent the CORGIS data
 */
class countyDemogData : public demogData {
public:
	//initializes county with all flat values being stored
	//takes the proportions passed in and converts them to flat values by multiplying by pop
	countyDemogData(string inN, string inS, double in65, double in18, double in5, double inBA, double inHS, double belowPov, int totalPop14,
			double inAIndian, double inAsian,double inBlack,double inHispanic,double inHawaiian,
								int inTotal, double inWomen) :
		demogData{inS,in65,
		in18,in5,
		inBA,inHS,
		belowPov,
		totalPop14,
		inAIndian,inAsian,inBlack,inHispanic,inHawaiian,inTotal,inWomen},
		name(inN){
		}
	/*friend std::ostream& operator<<(std::ostream &out, const countyDemogData &DD) {
		out << "County Demographics Info: " << DD.name << ", " << DD.region;
		out << "\nPopulation info: \n(\% over 65): " << DD.popOver65;
	    out << "\n(\% under 18): " << DD.popUnder18;
	    out << "\n(\% under 5): " << DD.popUnder5;
	    out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.eduOverBachelor;
	    out << "\n(\% high school or more): " << DD.eduOverHS;
	    out << "\n\% below poverty: " << DD.belowPoverty;
	    out << "\nTotal population: " << DD.population2014;
	    return out;
	}*/
	std::ostream& print(std::ostream &out) const override{
		out << "County Demographics Info: " << this->name << ", " << this->region;
		out << "\nPopulation info: \n(\% over 65): " << this->getpopOver65();
		out << "\n(\% under 18): " << this->getpopUnder18();
	    out << "\n(\% under 5): " << this->getpopUnder5();
	    out << "\nEducation info: \n(\% Bachelor degree or more): " << this->getBAup();
	    out << "\n(\% high school or more): " << this->getHSup();
	    out << "\n\% below poverty: " << this->getBelowPoverty();
	    out << "\nTotal population: " << this->population2014;
	    return out;
	}

	string getCounty(){ return name; }
private:
	string name;

};
#endif
