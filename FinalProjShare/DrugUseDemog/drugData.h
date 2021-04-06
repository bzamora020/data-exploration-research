
#ifndef DRUG_H
#define DRUG_H


#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "placeData.h"

/*
  aggregated demographic data for a given regional level (state - or larger region)
*/
class drugData : public placeData {

	public:

		drugData(string regionType, string name, string inS) : placeData(name, inS, regionType) {}

		drugData(string regionType, string name, string inS, int inPop, int inAlc, int inCoc, int inPain, int inWeed) : 
			placeData(name, inS, regionType), pop18to25(inPop), alcho18to25(inAlc), coc18to25(inCoc), painrd18to25(inPain), weed18to25(inWeed) {}
		 
		double getAlcohol()  const { return 100.0f*(double)(alcho18to25)/pop18to25; }
    	double getCocaine() const { return 100.0f*(double)(coc18to25)/pop18to25; }
    	double getPain() const{ return 100.0f*(double)(painrd18to25)/pop18to25; }
		double getWeed() const { return 100.0f*(double)(weed18to25)/pop18to25;}

		int getpop18to25() const {return pop18to25;}
		int getAlcoholCount()  const {return alcho18to25;}
    	int getCocaineCount() const {return coc18to25;}
    	int getPainCount() const {return painrd18to25;}
		int getWeedCount() const { return weed18to25; }


		// state #1	 	
        // Population.18-25 #5
		// Pain Relievers Dependence 18-25 #11
		// Alchohol binge past 18-25 column #76
		// Illicit Drug Cocaine Rates 18-25 #99

		friend std::ostream& operator<<(std::ostream &out, const drugData &DD);
		
		void accept(class Visitor &v);
	
    private:
        int pop18to25 = 0;
        int alcho18to25 = 0;
        int coc18to25 = 0;
        int painrd18to25 = 0;
		int weed18to25 = 0;
		
};

#endif




