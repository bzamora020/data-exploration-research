//
//  Header.h
//  
//
//  Created by Sid Majeti on 2/8/21.
//

#ifndef COMBODEMOGDATA_H
#define COMBODEMOGDATA_H

#include <iostream>
#include <map>
#include <memory>

#include "demogData.h"
#include "placeData.h"

using namespace std;

class comboDemogData: public demogData{
public:
    
    comboDemogData(string name): demogData(name){
        nameOfRegion = name;
    }
    //these are counts
//    int getpopOver65Count() const { return popOver65; }
//    int getpopUnder18Count() const { return popUnder18; }
//    int getpopUnder5Count() const { return popUnder5; }
//    int getBAupCount() const { return bachelorDegreeUp; }
//    int getHSupCount() const { return highSchoolUp; }
//    int getBelowPovertyCount() const { return belowPoverty; }
    
    
    void addCountytoState(shared_ptr<demogData> CI){
        int popNum = CI->getPop();
        popOver65 += CI->getpopOver65Count();
        popUnder18 += CI->getpopUnder18Count();
        popUnder5 += CI->getpopUnder5Count();
        bachelorDegreeUp += CI->getBAupCount();
        highSchoolUp += CI->getHSupCount();
        belowPoverty += CI->getBelowPovertyCount();
        population2014 += popNum;
        racial += CI->getRacialCount();
        numCombined++;
    }
    
    void average(){
        // cout << "Total p:" << totalPop << endl;
        popOver65 = (popOver65)/population2014;
        popUnder18 = (popUnder18)/population2014;
        popUnder5 = (popUnder5)/population2014;
        bachelorDegreeUp = (bachelorDegreeUp)/population2014;
        highSchoolUp = (highSchoolUp)/population2014;
        belowPoverty = (belowPoverty)/population2014;
        racial = racial/population2014;
    }

private:
    string nameOfRegion;
    
    int numCombined = 0;
};



#endif /* Header_h */
