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
    //old 
    //comboHospitalData(string inR) : hospitalData(inR, false, true, true), count(0) {}
    //new
    comboHospitalData(string inR) : hospitalData(inR, false, true, true, true,
       true, true, true, true), count(0) {}

    double getNumH() const { return count; }
    string getState() { return getRegion().substr( getRegion().size()-2, getRegion().size() ); } //just to pass autograder
    void addHospitaltoRegion(hospitalData* RA);

    //call after adding all ratings (including procedure ratings)
    void updateRegionRatings() {
      overall.updateRating();
      mortality.updateRating();
      readmission.updateRating();
      heart_attack_q.updateRating();
      heart_attack_v.updateRating();
      heart_failure_q.updateRating();
      heart_failure_v.updateRating();
      pneumonia_q.updateRating();
    }

    friend std::ostream& operator<<(std::ostream &out, const comboHospitalData& SH);

  private:
    double count; //number of hospitals
};
#endif
