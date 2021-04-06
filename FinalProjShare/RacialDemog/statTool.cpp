#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <math.h>
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"

#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"

/* statTool:: wrapper for some useful functions to report necessary data */
/* call visitor pattern to create state data */
void statTool::createStateData(std::vector<shared_ptr<placeData>>& theData, Visitor& theStates) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCombineState&)theStates);
    }
}

/* call visitor pattern to create county data */
void statTool::createCountyData(std::vector<shared_ptr<placeData>>& theData, Visitor& theCounties) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCombineCounty&)theCounties);
    }
}

/* compute statistics for demographic data for a given region
expects, the region, a statGatherer and function pointers for the methods to fill in */
void statTool::computeStatsDemogRegionData(Visitor* theRegions, statGatherer* fillArrays,
                                double (demogData::*f1)() const, double(demogData::*f2)() const,
                                int (demogData::*f3)() const, int (demogData::*f4)() const) {
    //data for both percents and counts
    vector<double> dataXcount;
    vector<double> dataYcount;
    vector<double> dataXpercent;
    vector<double> dataYpercent;

    //fill in the datausing a statGatherer
    int totPop = fillArrays->gatherBothStats(theRegions, dataXpercent, dataYpercent, 
        dataXcount, dataYcount, f1, f2, f3, f4);

    double mX = stats::computePopMean(dataXcount, totPop); 
    double mY = stats::computePopMean(dataYcount, totPop);  
    cout << "REGION demographic statistics:" << endl;
    cout << "stats mean X: " << mX    << " size of vector: " << dataXcount.size() << endl;
    cout << "stats mean Y: " << mY << " size of vector: " << dataYcount.size() << endl;

    cout << "std dev mean X: " << stats::computeStdDevPop(dataXpercent, mX) << endl;
    cout << "std dev mean Y: " << stats::computeStdDevPop(dataYpercent, mY) << endl;
    // cout << "Pearson Coeff: "<<stats::computeCorCoeff(dataXpercent, dataYpercent)<< endl;
    cout << "Population Coeff: " <<stats::computeCorCoeffPop(dataXpercent, dataYpercent, mX, mY)<< endl;

}

/* compute statistics for mixed data, demographic and hospital
expects, the region, a statGatherer and function pointers for the methods to fill in */
void statTool::computeStatsMixRegionData(Visitor* theRegions, statGatherer* fillArrays, 
        double (demogData::*f1)() const, double (comboHospitalData::*f2)() const) {

    vector<double> dataX;
    vector<double> dataY;

    fillArrays->gatherPerStats(theRegions, dataX, dataY, f1, f2);

    cout << "size of dataX: " << dataX.size() << endl;
    cout << "size of dataY: " << dataY.size() << endl;

    double mX = stats::computeMean(dataX); 
    double mY = stats::computeMean(dataY);  
    cout << "REGION stats comparing demographic and hospital data " << endl;
    cout << "stats mean X: " << mX    << " size of vector: " << dataX.size() << endl;
    cout << "stats mean Y: " << mY << " size of vector: " << dataY.size() << endl;

    cout << "std dev mean X: " << stats::computeStdDevSample(dataX) << endl;
    cout << "std dev mean Y: " << stats::computeStdDevSample(dataY) << endl;
    cout << "Correlation Coeff (sample): " <<stats::computeCorCoeffSample(dataX, dataY)<< endl;

}

