#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

//external
class Visitor;

/* very general data type for any kind of place data - also serving as the visitable class */
class placeData {
  public:

    placeData(const string inN, const int numF) : 
    placeName(inN), numFields(numF) {}

    string getName() const { return placeName; }

    //anything that is place data must accept a visitor (aka must be visitable)
    virtual void accept(class Visitor &v) = 0;

    //to be able to print for debug on full vector of placeData
    // virtual void toString(ostream& os) const = 0;

  protected:
  	string placeName; //only field required for lab04
    //Leaving these in for now, but unused
  	int numFields;
};

#endif
