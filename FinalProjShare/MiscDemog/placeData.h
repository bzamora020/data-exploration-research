#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

/* very general data type for any kind of place data - very simple for lab04 */
/* palceholder for visitable for lab05/6*/
class placeData {
  public:

    placeData(const string inN, const int numF) : 
    placeName(inN), numFields(numF) {}

    string getName() const { return placeName; }
    void setName(string inN) {placeName = inN;}

    virtual void accept(class Visitor &v) = 0;

  protected:
  	string placeName; //only field required for lab04
    //Leaving these in for now, but unused
  	int numFields;
};
#endif
