#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class date
{
public:
    date(string inDate) : storedDate(inDate)
    {
        string jan = "01";
        string feb = "02";
        string mar = "03";
        string apr = "04";
        string may = "05";
        string june = "06";
        string july = "07";
        string august = "08";
        string sept = "09";
        string oct = "10";
        string nov = "11";
        string dec = "12";
        
        // Initialize Jan
        counts_2015["01"] = 0;
        counts_2016["01"] = 0;
        counts_2017["01"] = 0;
        counts_2018["01"] = 0;
        counts_2019["01"] = 0;
        counts_2020["01"] = 0;
        counts_2021["01"] = 0;

        // Initialize feb
        counts_2015["02"] = 0;
        counts_2016["02"] = 0;
        counts_2017["02"] = 0;
        counts_2018["02"] = 0;
        counts_2019["02"] = 0;
        counts_2020["02"] = 0;
        counts_2021["02"] = 0;

        // Initialize march
        counts_2015["03"] = 0;
        counts_2016["03"] = 0;
        counts_2017["03"] = 0;
        counts_2018["03"] = 0;
        counts_2019["03"] = 0;
        counts_2020["03"] = 0;
        counts_2021["03"] = 0;

        // Initialize april
        counts_2015["04"] = 0;
        counts_2016["04"] = 0;
        counts_2017["04"] = 0;
        counts_2018["04"] = 0;
        counts_2019["04"] = 0;
        counts_2020["04"] = 0;
        counts_2021["04"] = 0;

        // Initialize may
        counts_2015["05"] = 0;
        counts_2016["05"] = 0;
        counts_2017["05"] = 0;
        counts_2018["05"] = 0;
        counts_2019["05"] = 0;
        counts_2020["05"] = 0;
        counts_2021["05"] = 0;

        // Initialize june
        counts_2015["06"] = 0;
        counts_2016["06"] = 0;
        counts_2017["06"] = 0;
        counts_2018["06"] = 0;
        counts_2019["06"] = 0;
        counts_2020["06"] = 0;
        counts_2021["06"] = 0;

        // Initialize July
        counts_2015["07"] = 0;
        counts_2016["07"] = 0;
        counts_2017["07"] = 0;
        counts_2018["07"] = 0;
        counts_2019["07"] = 0;
        counts_2020["07"] = 0;
        counts_2021["07"] = 0;

        // Initialize Aug
        counts_2015["08"] = 0;
        counts_2016["08"] = 0;
        counts_2017["08"] = 0;
        counts_2018["08"] = 0;
        counts_2019["08"] = 0;
        counts_2020["08"] = 0;
        counts_2021["08"] = 0;

        // Initialize Sept
        counts_2015["09"] = 0;
        counts_2016["09"] = 0;
        counts_2017["09"] = 0;
        counts_2018["09"] = 0;
        counts_2019["09"] = 0;
        counts_2020["09"] = 0;
        counts_2021["09"] = 0;

        // Initialize Oct
        counts_2015["10"] = 0;
        counts_2016["10"] = 0;
        counts_2017["10"] = 0;
        counts_2018["10"] = 0;
        counts_2019["10"] = 0;
        counts_2020["10"] = 0;
        counts_2021["10"] = 0;

        // Initialize Nov
        counts_2015["11"] = 0;
        counts_2016["11"] = 0;
        counts_2017["11"] = 0;
        counts_2018["11"] = 0;
        counts_2019["11"] = 0;
        counts_2020["11"] = 0;
        counts_2021["11"] = 0;

        // Initialize Dec
        counts_2015["12"] = 0;
        counts_2016["12"] = 0;
        counts_2017["12"] = 0;
        counts_2018["12"] = 0;
        counts_2019["12"] = 0;
        counts_2020["12"] = 0;
        counts_2021["12"] = 0;


        if (inDate.compare("") != 0)
        {
            string year = inDate.substr(0, 4);
            string month = inDate.substr(5, 2);
            string date = inDate.substr(8, 2);
            if (year == "2015")
            {
                counts_2015[month]++;
            }
            if (year == "2016")
            {
                counts_2016[month]++;

            }
            if (year == "2017")
            {
                counts_2017[month]++;

            }
            if (year == "2018")
            {
                counts_2018[month]++;


            }
            if (year == "2019")
            {

                counts_2019[month]++;

            }
            if (year == "2020")
            {

                counts_2020[month]++;
            }
            if (year == "2021")
            {
                counts_2021[month]++;
            }
        }
    }
    // Getters for 2015
    int const getNumShootingsJan2015() { return counts_2015.at("01"); }
    int const getNumShootingsFeb2015() { return counts_2015.at("02"); }
    int const getNumShootingsMar2015() { return counts_2015.at("03"); }
    int const getNumShootingsApr2015() { return counts_2015.at("04"); }
    int const getNumShootingsMay2015() { return counts_2015.at("05"); }
    int const getNumShootingsJun2015() { return counts_2015.at("06"); }
    int const getNumShootingsJul2015() { return counts_2015.at("07"); }
    int const getNumShootingsAug2015() { return counts_2015.at("08"); }
    int const getNumShootingsSep2015() { return counts_2015.at("09"); }
    int const getNumShootingsOct2015() { return counts_2015.at("10"); }
    int const getNumShootingsNov2015() { return counts_2015.at("11"); }
    int const getNumShootingsDec2015() { return counts_2015.at("12"); }

    // Getters for 2016
    int const getNumShootingsJan2016() { return counts_2016.at("01"); }
    int const getNumShootingsFeb2016() { return counts_2016.at("02"); }
    int const getNumShootingsMar2016() { return counts_2016.at("03"); }
    int const getNumShootingsApr2016() { return counts_2016.at("04"); }
    int const getNumShootingsMay2016() { return counts_2016.at("05"); }
    int const getNumShootingsJun2016() { return counts_2016.at("06"); }
    int const getNumShootingsJul2016() { return counts_2016.at("07"); }
    int const getNumShootingsAug2016() { return counts_2016.at("08"); }
    int const getNumShootingsSep2016() { return counts_2016.at("09"); }
    int const getNumShootingsOct2016() { return counts_2016.at("10"); }
    int const getNumShootingsNov2016() { return counts_2016.at("11"); }
    int const getNumShootingsDec2016() { return counts_2016.at("12"); }

    //Getters for 2017
    int const getNumShootingsJan2017() { return counts_2017.at("01"); }
    int const getNumShootingsFeb2017() { return counts_2017.at("02"); }
    int const getNumShootingsMar2017() { return counts_2017.at("03"); }
    int const getNumShootingsApr2017() { return counts_2017.at("04"); }
    int const getNumShootingsMay2017() { return counts_2017.at("05"); }
    int const getNumShootingsJun2017() { return counts_2017.at("06"); }
    int const getNumShootingsJul2017() { return counts_2017.at("07"); }
    int const getNumShootingsAug2017() { return counts_2017.at("08"); }
    int const getNumShootingsSep2017() { return counts_2017.at("09"); }
    int const getNumShootingsOct2017() { return counts_2017.at("10"); }
    int const getNumShootingsNov2017() { return counts_2017.at("11"); }
    int const getNumShootingsDec2017() { return counts_2017.at("12"); }

    //Getters for 2018
    int const getNumShootingsJan2018() { return counts_2018.at("01"); }
    int const getNumShootingsFeb2018() { return counts_2018.at("02"); }
    int const getNumShootingsMar2018() { return counts_2018.at("03"); }
    int const getNumShootingsApr2018() { return counts_2018.at("04"); }
    int const getNumShootingsMay2018() { return counts_2018.at("05"); }
    int const getNumShootingsJun2018() { return counts_2018.at("06"); }
    int const getNumShootingsJul2018() { return counts_2018.at("07"); }
    int const getNumShootingsAug2018() { return counts_2018.at("08"); }
    int const getNumShootingsSep2018() { return counts_2018.at("09"); }
    int const getNumShootingsOct2018() { return counts_2018.at("10"); }
    int const getNumShootingsNov2018() { return counts_2018.at("11"); }
    int const getNumShootingsDec2018() { return counts_2018.at("12"); }

    //Getters for 2019
    int const getNumShootingsJan2019() { return counts_2019.at("01"); }
    int const getNumShootingsFeb2019() { return counts_2019.at("02"); }
    int const getNumShootingsMar2019() { return counts_2019.at("03"); }
    int const getNumShootingsApr2019() { return counts_2019.at("04"); }
    int const getNumShootingsMay2019() { return counts_2019.at("05"); }
    int const getNumShootingsJun2019() { return counts_2019.at("06"); }
    int const getNumShootingsJul2019() { return counts_2019.at("07"); }
    int const getNumShootingsAug2019() { return counts_2019.at("08"); }
    int const getNumShootingsSep2019() { return counts_2019.at("09"); }
    int const getNumShootingsOct2019() { return counts_2019.at("10"); }
    int const getNumShootingsNov2019() { return counts_2019.at("11"); }
    int const getNumShootingsDec2019() { return counts_2019.at("12"); }

    //Getters for 2020
    int const getNumShootingsJan2020() { return counts_2020.at("01"); }
    int const getNumShootingsFeb2020() { return counts_2020.at("02"); }
    int const getNumShootingsMar2020() { return counts_2020.at("03"); }
    int const getNumShootingsApr2020() { return counts_2020.at("04"); }
    int const getNumShootingsMay2020() { return counts_2020.at("05"); }
    int const getNumShootingsJun2020() { return counts_2020.at("06"); }
    int const getNumShootingsJul2020() { return counts_2020.at("07"); }
    int const getNumShootingsAug2020() { return counts_2020.at("08"); }
    int const getNumShootingsSep2020() { return counts_2020.at("09"); }
    int const getNumShootingsOct2020() { return counts_2020.at("10"); }
    int const getNumShootingsNov2020() { return counts_2020.at("11"); }
    int const getNumShootingsDec2020() { return counts_2020.at("12"); }

    //Getters for 2021
    int const getNumShootingsJan2021() { return counts_2021.at("01"); }
    int const getNumShootingsFeb2021() { return counts_2021.at("02"); }
    int const getNumShootingsMar2021() { return counts_2021.at("03"); }
    int const getNumShootingsApr2021() { return counts_2021.at("04"); }
    int const getNumShootingsMay2021() { return counts_2021.at("05"); }
    int const getNumShootingsJun2021() { return counts_2021.at("06"); }
    int const getNumShootingsJul2021() { return counts_2021.at("07"); }
    int const getNumShootingsAug2021() { return counts_2021.at("08"); }
    int const getNumShootingsSep2021() { return counts_2021.at("09"); }
    int const getNumShootingsOct2021() { return counts_2021.at("10"); }
    int const getNumShootingsNov2021() { return counts_2021.at("11"); }
    int const getNumShootingsDec2021() { return counts_2021.at("12"); }
    
    date &operator+=(const date &d);

protected:
    string storedDate;

    std::map<string, int> counts_2015; // Month, Count
    std::map<string, int> counts_2016;
    std::map<string, int> counts_2017;
    std::map<string, int> counts_2018;
    std::map<string, int> counts_2019;
    std::map<string, int> counts_2020;
    std::map<string, int> counts_2021;
};

#endif