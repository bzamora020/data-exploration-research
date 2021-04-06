#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

/* very general data type for any kind of place data - very simple for lab04 */
class placeData {
  public:

    placeData(string inN, string inS, string inRegionType) :
      name(inN), state(inS), region(inRegionType) {}

    virtual ~placeData() {}

    string getName() { return name; }
    string getState() { return state; }
    string getRegion() { return region; }

    virtual void accept(class Visitor &v) = 0;

    //to be able to print for debug on full vector of placeData
    void toString(ostream& os) const {}

  protected:

    string name;
    string state;
    string region;

};
#endif
