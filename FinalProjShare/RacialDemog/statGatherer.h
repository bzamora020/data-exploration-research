
#ifndef STATGATHER_H
#define STATGATHER_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include "demogData.h"

#include "comboHospitalData.h"

#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"


/*
helper parent functor to simplify stats gathering - the role of this functor is to gather data
into two arrays.
Takes in:
 -a regional level (county or state) visitor
 -vectors to fill in
 -varying number of function pointers for the class methods to use to fill in data
 */
class statGatherer {
  public:
    //function to gather mixed data (demographic and hospital)
    virtual void gatherPerStats(Visitor* Regions, vector<double> &XPer, vector<double> &YPer, 
                double (demogData::*f1)() const, double (comboHospitalData::*f2)() const) = 0;
    //function to gather two demog datas
    virtual void gatherPerStats(Visitor* Regions, vector<double> &XPer, vector<double> &YPer, 
                double (demogData::*f1)() const, double (demogData::*f2)() const) = 0;
    //function to gather two demog datas (percentages and counts - for accuracy with populations)
    virtual int gatherBothStats(Visitor* Regions, vector<double> &XPer, vector<double> &YPer,
                                    vector<double> &XCount, vector<double> &Ycount,
                                    double (demogData::*f1)() const, double (demogData::*f2)() const,
                                    int (demogData::*f3)() const, int (demogData::*f4)() const) = 0;
};


/* actual functor implementation to gather county level stats (dervied from statGatherer)
into two arrays.
Takes in:
 -a regional level county  visitor
 -vectors to fill in
 -varying number of function pointers for the class methods to use to fill in data
 */
class countyGather : public statGatherer {
  public:

    //function to gather mixed data (demographic and hospital)
    void gatherPerStats(Visitor* theCounties, vector<double> &XPer, vector<double> &YPer, 
            double (demogData::*f1)() const, double (comboHospitalData::*f2)() const) {
        //for all demographic data
        for (auto entry : ((visitorCombineCounty *)theCounties)->countyDmap()) {
            //make sure there is valid hospital data!
            comboHospitalData* hospForCounty= ((visitorCombineCounty *)theCounties)->countyHmapEntry(entry.first);
            if ( hospForCounty != NULL ) {
                double xP = (entry.second->*f1)();
                double yP = (hospForCounty->*f2)();
                if (!isnan(xP) && !isnan(yP)) {
                    YPer.push_back(yP);
                    XPer.push_back(xP);
                }
            }
        }
    }
    //function to gather two demog datas
    void gatherPerStats(Visitor* theCounties, vector<double> &XPer, vector<double> &YPer, 
                        double (demogData::*f1)() const, double (demogData::*f2)() const) { {
         //for all demographic data
        for (auto entry : ((visitorCombineCounty *)theCounties)->countyDmap()) {
                double xP = (entry.second->*f1)();
                double yP = (entry.second->*f2)();
                if (!isnan(xP) && !isnan(yP)) {
                    YPer.push_back(yP);
                    XPer.push_back(xP);
                }
            }
        }
    }

    //function to gather two demog datas (percentages and counts)
    int gatherBothStats(Visitor* theCounties, vector<double> &XPer, vector<double> &YPer,
                                    vector<double> &XCount, vector<double> &Ycount,
                                    double (demogData::*f1)() const, double (demogData::*f2)() const,
                                    int (demogData::*f3)() const, int (demogData::*f4)() const) {

        //first functions for percentages
        gatherPerStats(theCounties, XPer, YPer, f1, f2);

        //now fill in the counts
        int totPop = 0;
        for (auto entry : ((visitorCombineCounty *)theCounties)->countyDmap()) {
            demogData* demogForC = entry.second;
            double xC = (entry.second->*f3)();
            double yC = (entry.second->*f4)();
            if (!isnan(xC) && !isnan(yC)) {
                XCount.push_back(xC);
                Ycount.push_back(yC);
                totPop += (entry.second)->getPop();
            }
        }
        return totPop;
    }
};

/* actual functor implementation to gather state level stats (dervied from statGatherer)
into two arrays.
Takes in:
 -a regional level state  visitor
 -vectors to fill in
 -varying number of function pointers for the class methods to use to fill in data
 */
class stateGather : public statGatherer {
  public:

    //function to gather mixed data (demographic and hospital)
    void gatherPerStats(Visitor* theStates, vector<double> &XPer, vector<double> &YPer, 
            double (demogData::*f1)() const, double(comboHospitalData::*f2)() const) {
        for (auto entry : ((visitorCombineState *)theStates)->stateDmap()) {
          comboHospitalData* hospForState = ((visitorCombineState *)theStates)->stateHmapEntry(entry.first);
            if (hospForState  != NULL) {
                XPer.push_back(((entry.second)->*f1)());
                YPer.push_back((hospForState->*f2)());
            }
        }
    }
    //function to gather two demog datas
    void gatherPerStats(Visitor* theStates, vector<double> &XPer, vector<double> &YPer, 
            double (demogData::*f1)() const, double(demogData::*f2)() const) {
        for (auto entry : ((visitorCombineState *)theStates)->stateDmap()) {
            XPer.push_back((entry.second->*f1)());
            YPer.push_back((entry.second->*f2)());
        }
    }

    //function to gather two demog datas (percentages and counts)
    int gatherBothStats(Visitor* theStates, vector<double> &XPer, vector<double> &YPer,
                                    vector<double> &XCount, vector<double> &Ycount,
                                    double (demogData::*f1)() const, double(demogData::*f2)() const,
                                    int (demogData::*f3)() const, int (demogData::*f4)() const) {
        //fill in the percentage stats
        gatherPerStats(theStates, XPer, YPer, f1, f2);

        int totPop = 0;
        for (auto entry : ((visitorCombineState *)theStates)->stateDmap()) {
            XCount.push_back((entry.second->*f3)());
            Ycount.push_back((entry.second->*f4)());
            totPop += entry.second->getPop(); 
        }
        return totPop;
    }
};
#endif