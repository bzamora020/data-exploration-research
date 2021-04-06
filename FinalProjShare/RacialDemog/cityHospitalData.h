//
//  cityHospitalData.h
//  
//
//  Created by Sid Majeti on 2/8/21.
//

#ifndef cityHospitalData_h
#define cityHospitalData_h

#include "hospitalData.h"
#include <iostream>
#include <string>

using namespace std;


class cityHospitalData: public hospitalData{
    
public:
    cityHospitalData(int overall, rating mortality, rating readmit, string name, string type, string state, string city): hospitalData(state, "", "", overall, mortality, readmit){
        this->name = name;
        this->type = type;
        this->state = state;
        this->city = city;
    }
    string getHospitalName(){
        return name;
    }
    string getType(){
        return type;
    }
    string getCity(){
        return city;
    }
    
private:
    string name;
    string type;
    string city;
};
#endif /* cityHospitalData_h */
