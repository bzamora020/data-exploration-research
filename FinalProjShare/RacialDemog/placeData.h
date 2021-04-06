//
//  placeData.hpp
//  
//
//  Created by Sid Majeti on 2/8/21.
//

#ifndef PLACEDATA_H
#define PLACEDATA_H

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class placeData{
public:
    placeData(string name = "", string c = "", string r = ""){
        state = name;
        county = c;
        region = r;
    }
    string getName() const{
        if(region == "state"){
            return state;
        }
        return county;
    }

    string getCounty() const{return county;}

    string getState() const{return state;}

    string getRegion() const{ 
        if(region == "state"){
            return state + " " + "State";
        }
        else{
            return county + " " + "County";
        }
    }
    
    virtual void accept(class Visitor &v) = 0;
    
protected:
    string state = "";
    string county = "";
    string region = "";
};

#endif /* placeData_hpp */
