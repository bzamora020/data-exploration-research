#include "date.h"

date &date::operator+=(const date &d)
{
    string jan = "01";
    string feb = "02";
    string mar = "03";
    string apr = "04";
    string may = "05";
    string june = "06";
    string july = "07";
    string august = "08";


    this->counts_2015[jan] += d.counts_2015.at(jan);
    this->counts_2016[jan] += d.counts_2016.at(jan);     
    this->counts_2017[jan] += d.counts_2017.at(jan);     
    this->counts_2018[jan] += d.counts_2018.at(jan);     
    this->counts_2019[jan] += d.counts_2019.at(jan);     
    this->counts_2020[jan] += d.counts_2020.at(jan);     
    this->counts_2021[jan] += d.counts_2021.at(jan);                                                                                                                        
    return *(this);
};