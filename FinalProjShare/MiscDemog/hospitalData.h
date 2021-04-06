#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "placeData.h"

using namespace std;

/*
  class to represent hospital data
*/
class hospitalData : public placeData  {
  public:
    hospitalData(string inState, int inRating, rating inMort, rating inReAdmit) : 
            placeData{inState, 3}, overallRating(inRating),
            mortality(inMort), readmission(inReAdmit){
    }

    string getState() const { return this->getName(); }
    int getOverallRate() const { return overallRating; } // zero means none
    rating getMortality() const { return mortality; }
    rating getReadmit() const { return readmission; }

    void accept(class Visitor &v) override;

   friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

protected:
    int overallRating;
    rating mortality;
    rating readmission;
};

#endif
