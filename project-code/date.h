#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class date{
    public:
        date(string inDate) : storedDate(inDate) {
            string year = inDate.substr(0,4);
            string month = inDate.substr(5,2);
            string date = inDate.substr(8,2);
            if(year == "2015"){
                if(counts_2015.count(month) == 0){
                    counts_2015[month] = 1;
                }
                else{
                    counts_2015[month] = counts_2015[month]++;
                }
            }
            if(year == "2016"){
                if(counts_2016.count(month) == 0){
                    counts_2016[month] = 1;
                }
                else{
                    counts_2016[month] = counts_2016[month]++;
                }
            }
            if(year == "2017"){
                if(counts_2017.count(month) == 0){
                    counts_2017[month] = 1;
                }
                else{
                    counts_2017[month] = counts_2017[month]++;
                }
            }
            if(year == "2018"){
                if(counts_2018.count(month) == 0){
                    counts_2018[month] = 1;
                }
                else{
                    counts_2018[month] = counts_2018[month]++;
                }
            }
            if(year == "2019"){
                if(counts_2019.count(month) == 0){
                    counts_2019[month] = 1;
                }
                else{
                    counts_2019[month] = counts_2019[month]++;
                }
            }
            if(year == "2020"){
                if(counts_2020.count(month) == 0){
                    counts_2020[month] = 1;
                }
                else{
                    counts_2020[month] = counts_2020[month]++; 
                }
            }
            if(year == "2021"){
                if(counts_2021.count(month) == 0){
                    counts_2021[month] = 1;
                }
                else{
                    counts_2021[month] = counts_2021[month]++;
                }
            }
        }

        date &operator+=(const date &d);

           
    protected:
        string storedDate; 

        std::map<string,int> counts_2015; // Month, Count
        std::map<string,int> counts_2016;
        std::map<string,int> counts_2017;
        std::map<string,int> counts_2018;
        std::map<string,int> counts_2019;
        std::map<string,int> counts_2020;
        std::map<string,int> counts_2021;
};

#endif