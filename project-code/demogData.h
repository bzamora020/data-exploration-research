#ifndef DEMOGD_H
#define DEMOGD_H

#include <memory>
#include <string>
#include <iostream>
#include "placeData.h"
#include "racialDemogData.h"

/*
  class to represent generic demographic data all regional level
*/
class demogData: public placeData {
  public:
    demogData(string inS, double in65, double in18,
        double in5, double inBA, double inHS,
        double belowPov, int totalPop14, RacialData rIn) : placeData{inS, 8},
            popOver65(in65), popUnder18(in18),
            popUnder5(in5), bachelorDegreeUp(inBA), highSchoolUp(inHS),
            belowPoverty(belowPov), population2014(totalPop14)  {
                racial = rIn;
    }
    demogData(string inS) : placeData{inS, 8},
            popOver65(0), popUnder18(0),
            popUnder5(0), bachelorDegreeUp(0), highSchoolUp(0),
            belowPoverty(0), population2014(0) {
    }

  string getState() const { return this->getName(); } //call placeName
  /* these return percentages */
  double getpopOver65() const  { return 100.0f*(double)(popOver65)/population2014; }
  double getpopUnder18() const  { return 100.0f*(double)(popUnder18)/population2014; }
  double getpopUnder5() const  { return 100.0f*(double)(popUnder5)/population2014; }
  double getBAup() const { return 100.0f*(double)(bachelorDegreeUp)/population2014; }
  double getHSup() const  { return 100.0f*(double)(highSchoolUp)/population2014; }
  double getBelowPoverty() const  { return 100.0f*(double)(belowPoverty)/population2014; }

  //these are counts
  int getpopOver65Count() const { return popOver65; }
  int getpopUnder18Count() const { return popUnder18; }
  int getpopUnder5Count() const { return popUnder5; }
  int getBAupCount() const { return bachelorDegreeUp; }
  int getHSupCount() const { return highSchoolUp; }
  int getBelowPovertyCount() const { return belowPoverty; }

  int getPop() const { return population2014; }

   RacialData getRacialCount() const { return racial;}
 
    double getNativePerc()const{ return 100.0f*racial.getNative()/population2014; }
    double getAsianPerc() const{ return 100.0f*racial.getAsian()/population2014; }
    double getBlackPerc() const{ return 100.0f*racial.getBlack()/population2014; }
    double getHispanicPerc() const{ return 100.0f*racial.getHispanic()/population2014; }
    double getHawaiianPerc() const{ return 100.0f*racial.getHawaiian()/population2014; }
    double getMixedPerc() const { return 100.0f*racial.getMixed()/population2014; }
    double getWhitePerc() const{ return 100.0f*racial.getWhite()/population2014; }
    double getOnlyWhitePerc() const{ return 100.0f*racial.getOnlyWhite()/population2014; } 

  int getNativeCount()const{ return racial.getNative();}
    int getAsianCount() const{ return racial.getAsian(); }
    int getBlackCount() const{ return racial.getBlack(); }
    int getHispanicCount() const{ return racial.getHispanic(); }
    int getHawaiianCount() const{ return racial.getHawaiian(); }
    int getMixedCount() const { return racial.getMixed(); }
    int getWhiteCount() const{ return racial.getWhite(); }
    int getOnlyWhiteCount() const{ return racial.getOnlyWhite(); }

  friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

  void accept(class Visitor &v) override;

  // void toString(ostream& os) const;

protected:
    /* store counts */
    int popOver65;
    int popUnder18;
    int popUnder5;
    int bachelorDegreeUp;
    int highSchoolUp;
    int belowPoverty;
    int population2014;
    RacialData racial;
  };
#endif
