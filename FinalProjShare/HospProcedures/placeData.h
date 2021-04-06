#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

class Visitor;
/* very general data type for any kind of place data - very simple for lab04 */
class placeData {
  public:
    placeData(string inR) : region(inR) {}

    string getRegion() const { return region; }
    string getName() const { return region; } //for autograder

    virtual void accept(class Visitor &v) = 0;
  protected:
    const string region;

};
#endif
