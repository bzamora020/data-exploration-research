#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

/* very general data type for any kind of place data - very simple for lab04 */
class placeData {
public: 
    placeData(string p) {
      place = p;
    }
    string getState() const {return place;}
    virtual void accept(class Visitor &v);
  virtual ~placeData() {}
protected:
    string place;
};
#endif
