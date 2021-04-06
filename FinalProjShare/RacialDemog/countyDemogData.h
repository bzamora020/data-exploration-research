//
//  demogCouunt.h
//  
//
//  Created by Sid Majeti on 2/8/21.
//

#ifndef countyDemogData_h
#define countyDemogData_h

#include <string>
#include <iostream>
#include "demogData.h"
#include "racialData.h"

using namespace std;

class countyDemogData: public demogData{

public:
    countyDemogData(string state, string city, double in65, double in18,
                double in5, double inBA, double inHS, double belowPov, int totalPop14, RacialData r): demogData(state,in65, in18, in5, inBA, inHS, belowPov, totalPop14, r){
        countyName = city;
    }
    countyDemogData(string state, string city, double in65 = 0, double in18 = 0,
                double in5 = 0, double inBA = 0, double inHS = 0, double belowPov = 0, int totalPop14 = 0): demogData(state,in65, in18, in5, inBA, inHS, belowPov, totalPop14){
        countyName = city;
    }
    string getCountyName(){
        return countyName;
    }
    

private:
    string countyName;
    
};

#endif /* demogCouunt_h */
