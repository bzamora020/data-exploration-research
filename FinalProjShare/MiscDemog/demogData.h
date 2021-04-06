#ifndef DEMOGD_H
#define DEMOGD_H

#include <memory>
#include <string>
#include <iostream>
#include "placeData.h"
#include "MiscellaneousData.h"

/*
  class to represent generic demographic data all regional level
*/
class demogData: public placeData {
  public:
    demogData(string inS, double in65, double in18,
        double in5, double inBA, double inHS,
        double belowPov, int totalPop14, miscellaneousData MD) : placeData{inS, 8},
            popOver65(in65), popUnder18(in18),
            popUnder5(in5), bachelorDegreeUp(inBA), highSchoolUp(inHS),
            belowPoverty(belowPov), population2014(totalPop14), misc(MD) {
    }
    demogData(string inS) : placeData{inS, 8},
            popOver65(0), popUnder18(0),
            popUnder5(0), bachelorDegreeUp(0), highSchoolUp(0),
            belowPoverty(0), population2014(0), misc() {
    }

  string getState() const { return this->getName(); } //call placeName
  /* these return percentages */
  double getpopOver65() const  { return 100.0f*(double)(popOver65)/population2014; }
  double getpopUnder18() const  { return 100.0f*(double)(popUnder18)/population2014; }
  double getpopUnder5() const  { return 100.0f*(double)(popUnder5)/population2014; }
  double getBAup() const { return 100.0f*(double)(bachelorDegreeUp)/population2014; }
  double getHSup() const  { return 100.0f*(double)(highSchoolUp)/population2014; }
  double getBelowPoverty() const  { return 100.0f*(double)(belowPoverty)/population2014; }
   
  //Final Project Miscellaneous; percents
  double getPopFemale() const { return 100.0f*(double)(misc.getPopFemaleCount() / population2014); }
  double getPopForeign() const { return 100.0f*(double)(misc.getPopForeignCount()) / population2014; }
  double getPopSameHouse() const { return 100.0f*(double)(misc.getPopSameHouseCount()) / population2014; }
  double getPopOtherLang() const { return 100.0f*(double)(misc.getPopOtherLangCount()) / population2014; }
  double getMeanCommute() const { return misc.getMeanCommute(); }
  double getLandArea() const { return misc.getLandArea(); }
  double getPercentVeterans() const { return 100.0f*(double)(misc.getVeterans()) / population2014; }

  //these are counts
  int getpopOver65Count() const { return popOver65; }
  int getpopUnder18Count() const { return popUnder18; }
  int getpopUnder5Count() const { return popUnder5; }
  int getBAupCount() const { return bachelorDegreeUp; }
  int getHSupCount() const { return highSchoolUp; }
  int getBelowPovertyCount() const { return belowPoverty; }
  
  double getPopFemaleCount() const { return misc.getPopFemaleCount(); }
  double getPopForeignCount() const { return misc.getPopForeignCount(); }
  double getPopSameHouseCount() const { return misc.getPopSameHouseCount(); }
  double getPopOtherLangCount() const { return misc.getPopOtherLangCount(); }
  int getVeteranCount() const { return misc.getVeterans(); }
  int getShipmentsCount() const { return misc.getManufacturerShipments(); }
  int getBuildingPermitCount() const { return misc.getBuildingPerm(); }

  int getPop() const { return population2014; }
  
  void accept(class Visitor &v) override;

  miscellaneousData getMisc() { return misc; }

  friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

protected:
    /* store counts */
    int popOver65;
    int popUnder18;
    int popUnder5;
    int bachelorDegreeUp;
    int highSchoolUp;
    int belowPoverty;
    int population2014;
    miscellaneousData misc;
  };
#endif
