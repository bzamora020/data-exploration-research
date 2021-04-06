//
//  comboHospitalData.h
//  
//
//  Created by Sid Majeti on 2/8/21.
//

#ifndef comboHospitalData_h
#define comboHospitalData_h

#include "hospitalData.h"
#include <memory>
#include "rating.h"
#include "placeData.h"
#include <sstream>
#include <iostream>
#include <string>


class comboHospitalData: public hospitalData{
    
public:
    
    comboHospitalData(string name, string county, string region): hospitalData(name, county, region){
    }
    void addCountytoState(shared_ptr<hospitalData>  CI){
        if(CI->getOverallRate() != -1.0){
            overallRate += CI->getOverallRate();
            validRatHops += 1;
        }
        if(CI->getMortality().getRating() != "None"){
            mortality += CI->getMortality();
            validMHops += 1;
        }
        if(CI->getReadmit().getRating() != "None"){
            readmit += CI->getReadmit();
            validReHops += 1;
        }
        hospCount += 1;
    }
    
    double getOverallRate() const{ 
        if (validRatHops > 0)
            return overallRate/double(validRatHops); 
        return double(overallRate);
    } // zero means none
    rating getMortality() {
        if (validMHops > 0) 
            return mortality/double(validMHops); 
        return mortality;
    }
    rating getReadmit(){ 
        if (validReHops > 0) 
            return readmit/double(validReHops); 
        return readmit;
    }

    void average(){
        mortality = mortality/double(validMHops);
        readmit = readmit/double(validReHops);
        overallRate = overallRate/double(validRatHops);
    }

    double getNumH() const{
        return hospCount;
    }

    friend std::ostream& operator<<(std::ostream &out, comboHospitalData &CH);

    
private:
    int hospCount = 0;
    int validRatHops = 0;
    int validMHops = 0;
    int validReHops = 0;
    // rating totalRating{};
    // rating totalMortality{};
    // rating totalReadmit{};
};


#endif /* comboHospitalData_h */
