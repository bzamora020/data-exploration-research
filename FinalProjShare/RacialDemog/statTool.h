
#ifndef STATTOOL_H
#define STATTOOL_H

#include "demogData.h"
#include "comboHospitalData.h"

#include "visitor.h"
#include "stats.h"
#include "statGatherer.h"

/* wrapper for some useful functions to report necessary data */
class statTool {

public:

  /* call visitor pattern to create state data */
  static void createStateData(std::vector<shared_ptr<placeData>>& theData, Visitor& theStates);

  /* call visitor pattern to create county data */
  static  void createCountyData(std::vector<shared_ptr<placeData>>& theData, Visitor& theCounties);

  /* compute statistics for demographic data for a given region
  expects, the region, a statGatherer and function pointers for the methods to fill in */
  static void computeStatsDemogRegionData(Visitor* theRegions, statGatherer* fillArrays,
                                double (demogData::*f1)() const, double(demogData::*f2)() const,
                                int (demogData::*f3)() const, int (demogData::*f4)() const);
  static void computeStatsMixRegionData(Visitor* theRegions, statGatherer* fillArrays, 
        double (demogData::*f1)() const, double (comboHospitalData::*f2)() const);

};
#endif




