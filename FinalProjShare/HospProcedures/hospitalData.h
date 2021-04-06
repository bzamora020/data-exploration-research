#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "procedure_quality.h"
#include "procedure_value.h"
#include "placeData.h"

using namespace std;

/*
  class to represent hospital data
*/
class hospitalData : public placeData  {
  public:
    //for old comboHospitalData (in case something goes wrong)
    hospitalData(string inR, bool inOv, bool inMor, bool inRea) :
        placeData(inR), overall(inOv), mortality(inMor), readmission(inRea),
        heart_attack_q(false), heart_attack_v(false), heart_failure_q(false),
        heart_failure_v(false), pneumonia_q(false)  {}
    //for new comboHospitalData (will set all ratings to empty ratings)
    hospitalData(string inR, bool inOv, bool inMor, bool inRea,
      bool inHAQ, bool inHAV, bool inHFQ, bool inHFV, bool inPQ) :
        placeData(inR), overall(inOv), mortality(inMor), readmission(inRea),
        heart_attack_q(inHAQ), heart_attack_v(inHAV), heart_failure_q(inHFQ),
        heart_failure_v(inHFV), pneumonia_q(inPQ) {}
    //for cityHospitalData
    hospitalData(string inR, double inOv, string inMor, string inRea,
      string inHAQ, string inHAV, string inHFQ, string inHFV, string inPQ) :
        placeData(inR), overall(inOv), mortality(inMor), readmission(inRea),
        heart_attack_q(inHAQ), heart_attack_v(inHAV), heart_failure_q(inHFQ),
        heart_failure_v(inHFV), pneumonia_q(inPQ) {}

    double getOverallRate() const { return overall.getRatingNum(); }

    rating getOverallRate_rat() const { return overall; }
    rating getMortRate() const { return mortality; }
    rating getReadRate() const { return readmission; }


    procedure_quality getHeart_attack_q() const { return heart_attack_q; }
    procedure_value getHeart_attack_v() const { return heart_attack_v; }
    procedure_quality getHeart_failure_q() const { return heart_failure_q; }
    procedure_value getHeart_failure_v() const { return heart_failure_v; }
    procedure_quality getPneumonia_q() const { return pneumonia_q; }
    //these return nums so we can compare data
    double getHeart_attack_q_Num() const { return heart_attack_q.getRatingNum(); }
    double getHeart_attack_v_Num() const { return heart_attack_v.getRatingNum(); }
    double getHeart_failure_q_Num() const { return heart_failure_q.getRatingNum(); }
    double getHeart_failure_v_Num() const { return heart_failure_v.getRatingNum(); }
    double getPneumonia_q_Num() const { return pneumonia_q.getRatingNum(); }

    void accept(class Visitor &v) override;
  //  friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

  protected: //for comboHospitalData's updateRating
    rating overall;
    rating mortality;
    rating readmission;

    //procedure ratings
    procedure_quality heart_attack_q;
    procedure_value heart_attack_v;
    procedure_quality heart_failure_q;
    procedure_value heart_failure_v;
    procedure_quality pneumonia_q;
    /*
    q-quality
    v-value
    */

};

#endif
