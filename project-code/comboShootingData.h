#ifndef COMBOSHOOTING_H
#define COMBOSHOOTING_H

#include "placeData.h"
#include "shootingData.h"
#include <iostream>
#include <memory>
#include <string>

class comboShootingData : public shootingData {
public:
  comboShootingData(string inRegtype, string inS)
      : shootingData(inS), region(inRegtype), cases(0) {}

  void addShootingtoRegion(shootingData *inD);

  int getNumCases() { return cases; }
  string getRegionType() { return region; }
  double getPerNumberCases() const { return 100.0f*(double)(cases)/6214 ;}

  double getPerArmedUnknown() const
    {
        /* if(armedUnknown == 0)
        {
            return 0;
        } */
        cout << "Num cases: " << cases << endl
             << "wasArmed num: " << wasArmed << endl;
             
        return (100.0f * (double)(cases - wasArmed) / cases);
    }

private:
  string region;
  int cases;
};

#endif