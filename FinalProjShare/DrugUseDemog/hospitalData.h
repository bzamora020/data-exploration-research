#ifndef HOSP_H
#define HOSP_H

#include <memory>
#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "placeData.h"

using namespace std;

/*
  class to represent hospital data
  from CORGIS
*/
class hospitalData : public placeData, public std::enable_shared_from_this<hospitalData> {
  public:

    hospitalData(string inN, string inS, string inR) : placeData(inN, inS, inR) {}

	 //constructor for starting code - make complete by adding rating
    hospitalData(string inN, string inS, string inRegionType, string inType, double inOverall, string inMortality, string inReadmit) : placeData(inN, inS, inRegionType),
            type(inType), overallRating(inOverall), mortalityRating(inMortality), readmitRating(inReadmit) {
    }

    string getType() const { return type; }

    double getOverallRate() const { return overallRating.getRatingNum(); }
    rating getMortality() const { return mortalityRating; }
    rating getReadmit() const { return readmitRating; }

    void accept(class Visitor &v);

    friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

protected:
    const string type;
    
    // ratings
    rating overallRating;
    rating mortalityRating;
    rating readmitRating;
		
};

#endif
