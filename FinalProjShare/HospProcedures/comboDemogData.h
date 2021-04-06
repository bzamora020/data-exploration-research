#ifndef COMBOD_H
#define COMBOD_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "placeData.h"

/*
  aggregated demographic data for a given regional level (state - or larger region)
*/
class comboDemogData : public demogData  {
  public:
    comboDemogData(string inR) :
        demogData(inR, 0, 0, 0, 0, 0, 0, 0), numDemog(0) {}

    void addDemogtoRegion(demogData* CD);

    int getNumD() const { return numDemog; }
    string getState() {return getRegion(); } //just to pass autograder

    friend std::ostream& operator<<(std::ostream &out, const comboDemogData &DD);

  private:
    int numDemog; // count of sub regions e.g. counties, cities, whatever . . .
};
#endif
