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
  hospitalData(string inS, int inOR, rating inMR, rating inRR) :
    placeData{inS}, overallRate(inOR), mortRate(inMR), readmitRate(inRR) {
    }

  hospitalData(string inS) :
    placeData{inS}, overallRate(0), mortRate(0), readmitRate(0) {
  }
  
  double getOverallRate() const {return overallRate;}
  rating getMortality() const {return mortRate;}
  rating getReadmit() const {return readmitRate;}

  friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

  void accept(class Visitor &v) override;

protected:

  double overallRate=0;
  rating mortRate=rating(0);
  rating readmitRate=rating(0);
};

#endif
