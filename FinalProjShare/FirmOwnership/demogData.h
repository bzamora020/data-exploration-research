#ifndef DEMOGD_H
#define DEMOGD_H

#include <memory>
#include <string>
#include <iostream>
#include "placeData.h"
#include "employmentData.h"

/*
  class to represent generic demographic data all regional level
 */
class demogData: public placeData {
public:
	demogData(string inS, double in65, double in18,
		double in5, double inBA, double inHS, double belowPov, int totalPop14,
		double inAIndian, double inAsian,double inBlack,double inHispanic,double inHawaiian,
					int inTotal, double inWomen) :
			placeData{inS},
			popOver65(in65),
			popUnder18(in18),
			popUnder5(in5),
			eduOverBachelor(inBA),
			eduOverHS(inHS),
			belowPoverty(belowPov),
			population2014(totalPop14),
			ed(inAIndian,inAsian,inBlack,inHispanic,inHawaiian,inTotal,inWomen){
			}
	demogData(string inS):
		placeData{inS},
		popOver65(0),
		popUnder18(0),
		popUnder5(0),
		eduOverBachelor(0),
		eduOverHS(0),
		belowPoverty(0),
		population2014(0),
		ed(){}

	//actual value getters
	 int getpopOver65Count() const { return popOver65; }
	 int getpopUnder18Count() const { return popUnder18; }
	/*unsigned*/ int getpopUnder5Count() const { return popUnder5; }
	/*unsigned*/ int getBAupCount() const { return eduOverBachelor; }
	int getHSupCount() const { return eduOverHS; }
	int getBelowPovertyCount() const { return belowPoverty; }
	unsigned int getPop() const { return population2014; }

	//get the proportion of population in these categories
	double getpopOver65() const { return popOver65*100/(double)population2014; }
	double getpopUnder18() const { return popUnder18*100/(double)population2014; }
	double getpopUnder5() const { return popUnder5*100/(double)population2014; }
	double getBAup() const { return eduOverBachelor*100/(double)population2014; }
	double getHSup() const { return eduOverHS*100/(double)population2014; }
	double getBelowPoverty() const { return belowPoverty*100/(double)population2014; }

	employmentData getED() const { return ed;}

	std::ostream& print(std::ostream &out) const override{
		return out;
	}

	virtual void accept(class Visitor &v) override;

protected:
	//stores flat values
	double popOver65;
	double popUnder18;
	double popUnder5;
	double eduOverBachelor;
	double eduOverHS;
	double belowPoverty;
	unsigned int population2014;
	employmentData ed;
};
#endif
