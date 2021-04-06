#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include <iostream>
#include "placeData.h"

using namespace std;

/*
  class to represent county demographic data
  from CORGIS
*/
class demogData : public placeData{
  public:
    demogData(string inN, string inS, double in65, double in18,
        double in5, double tPop) :
            placeData(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), percentUndergraduate(-1), percentHighSchool(-1), totalPop(tPop), belowPoverty(0) {} 

    demogData(string inN, string inS, double in65, double in18,
        double in5, double percU, double percH, double bp, double tPop) :
            placeData(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), percentUndergraduate(percU), percentHighSchool(percH), totalPop(tPop), belowPoverty(bp) {}

    demogData(demogData &d) : placeData(d.getName()), state(d.state), popOver65(d.popOver65), popUnder18(d.popUnder18),
        popUnder5(d.popUnder5), percentUndergraduate(d.percentUndergraduate), percentHighSchool(d.percentHighSchool), totalPop(d.totalPop), belowPoverty(d.belowPoverty) {}

    demogData(string name, string s) : placeData(name), state(s), popOver65(0), popUnder18(0),
        popUnder5(0), percentUndergraduate(0), percentHighSchool(0), totalPop(0), belowPoverty(0) {}

    int getBAupCount() const { return (int)percentUndergraduate; }
    int getHSupCount() const { return (int)percentHighSchool; }
    string const getState() const { return state; }
    int getpopOver65Count() const { return (int)popOver65; }
    int getpopUnder18Count() const { return (int)popUnder18; }
    int getpopUnder5Count() const { return (int)popUnder5; }
    int getPop() const { return (int)totalPop; }
    int getBelowPovertyCount() const { return (int)belowPoverty; }

    double getPopDouble() const {return totalPop; }

    double getBAup() const { return (100*(percentUndergraduate / totalPop)); }
    double getHSup() const { return (100* (percentHighSchool / totalPop)); }
    double getpopOver65() const { return (100*popOver65 / totalPop); }
    double getpopUnder18() const { return (100*popUnder18 / totalPop); }
    double getpopUnder5() const { return (100*popUnder5 / totalPop); }
    double getBelowPoverty() const { return (100*belowPoverty / totalPop); }

    void setBAupCount(double d) { percentUndergraduate = d; }
    void setHSupCount(double d) { percentHighSchool = d;  }
    void setpopOver65Count(double d) { popOver65 = d; }
    void setpopUnder18Count(double d) { popUnder18 = d; }
    void setpopUnder5Count(double d) { popUnder5 = d; }
    void setPop(double d) { totalPop = d; }
    void setBelowPovertyCount(double d) { belowPoverty = d; }

    static bool compareP(demogData* ps1, demogData* ps2) { return ps1->belowPoverty / ps1->totalPop < ps2->belowPoverty / ps2->totalPop; }

    friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

    void accept(class Visitor& v);
  private:
    //all these are totals
    const string state;
    double popOver65;
    double popUnder18;
    double popUnder5;
    double percentUndergraduate;
    double percentHighSchool;
    double totalPop;
    double belowPoverty;
};
#endif
