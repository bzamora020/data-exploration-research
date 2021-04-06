#ifndef COMBOH_H
#define COMBOH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"

/*
  aggregated hospital data for a given regional level (county or state)
*/
class comboHospitalData : public hospitalData {
  public:
    comboHospitalData(string inRegion, string inState) : hospitalData{inState, 0, 0, 0}, 
            region(inRegion), numHospitals(0),
            numNZOHospitals(0), numNZMHospitals(0), numNZRHospitals(0)  {
  }

  string getRegion() const { return region; }
  double getOverallRate() const { 
    if (numNZOHospitals > 0)
      return overallRating/(double)numNZOHospitals; 
    return overallRating;
  } // zero means none
  rating getMortality() const {
    if (numNZMHospitals > 0) 
      return rating(mortality.getRatingNum()/(double)numNZMHospitals); 
    return rating(mortality.getRatingNum());
  }
  rating getReadmit() const { 
    if (numNZRHospitals > 0) 
      return rating(readmission.getRatingNum()/(double)numNZRHospitals); 
    return rating(readmission.getRatingNum());
  }

  //Change to double to fix
  double getNumH() const { return numHospitals; } // OKAY WE EDITED THIS, FIXED ERROR BUT ???? happened

  //note this stores a running total until averageOut - lots of ways to do this
  void addHospitaltoRegion(hospitalData  *HI);

  friend std::ostream& operator<<(std::ostream &out, const comboHospitalData &HD) {
      out << "Combined hospital data at level: " << HD.getRegion() << " in "<< HD.getState();
      cout << "\nincludes num hospitals: " << HD.getNumH();
      out << "\nOverall rating (out of 5): " << HD.getOverallRate();
      out << "\nmortality rating: " << HD.getMortality();
      out << "\nreadmit rating: " << HD.getReadmit();
      //debug
      //cout << "\nnon zero (O M R): " << HD.numNZOHospitals << " " << HD.numNZMHospitals << " " << HD.numNZRHospitals <<endl;
      return out;
  }

private:

    string region; //either state or county
    int numHospitals;
    /* a bit ugly but accurate averages without 'unknown' */
    int numNZOHospitals;
    int numNZMHospitals; //number of hospitals with known mortality data
    int numNZRHospitals;//number of hospitals with known readmission data
};
#endif
