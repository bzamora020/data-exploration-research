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
    string sept = "09";
    string oct = "10";
    string nov = "11";
    string dec = "12";

    // January counts

    this->counts_2015[jan] += d.counts_2015.at(jan);
    this->counts_2016[jan] += d.counts_2016.at(jan);
    this->counts_2017[jan] += d.counts_2017.at(jan);
    this->counts_2018[jan] += d.counts_2018.at(jan);
    this->counts_2019[jan] += d.counts_2019.at(jan);
    this->counts_2020[jan] += d.counts_2020.at(jan);
    this->counts_2021[jan] += d.counts_2021.at(jan);

    // February counts
    this->counts_2015[feb] += d.counts_2015.at(feb);
    this->counts_2016[feb] += d.counts_2016.at(feb);
    this->counts_2017[feb] += d.counts_2017.at(feb);
    this->counts_2018[feb] += d.counts_2018.at(feb);
    this->counts_2019[feb] += d.counts_2019.at(feb);
    this->counts_2020[feb] += d.counts_2020.at(feb);
    this->counts_2021[feb] += d.counts_2021.at(feb);

    // March counts
    this->counts_2015[mar] += d.counts_2015.at(mar);
    this->counts_2016[mar] += d.counts_2016.at(mar);
    this->counts_2017[mar] += d.counts_2017.at(mar);
    this->counts_2018[mar] += d.counts_2018.at(mar);
    this->counts_2019[mar] += d.counts_2019.at(mar);
    this->counts_2020[mar] += d.counts_2020.at(mar);
    this->counts_2021[mar] += d.counts_2021.at(mar);

    // April counts
    this->counts_2015[apr] += d.counts_2015.at(apr);
    this->counts_2016[apr] += d.counts_2016.at(apr);
    this->counts_2017[apr] += d.counts_2017.at(apr);
    this->counts_2018[apr] += d.counts_2018.at(apr);
    this->counts_2019[apr] += d.counts_2019.at(apr);
    this->counts_2020[apr] += d.counts_2020.at(apr);
    this->counts_2021[apr] += d.counts_2021.at(apr);

    // May counts
    this->counts_2015[may] += d.counts_2015.at(may);
    this->counts_2016[may] += d.counts_2016.at(may);
    this->counts_2017[may] += d.counts_2017.at(may);
    this->counts_2018[may] += d.counts_2018.at(may);
    this->counts_2019[may] += d.counts_2019.at(may);
    this->counts_2020[may] += d.counts_2020.at(may);
    this->counts_2021[may] += d.counts_2021.at(may);

    // June counts
    this->counts_2015[june] += d.counts_2015.at(june);
    this->counts_2016[june] += d.counts_2016.at(june);
    this->counts_2017[june] += d.counts_2017.at(june);
    this->counts_2018[june] += d.counts_2018.at(june);
    this->counts_2019[june] += d.counts_2019.at(june);
    this->counts_2020[june] += d.counts_2020.at(june);
    this->counts_2021[june] += d.counts_2021.at(june);

    // July counts
    this->counts_2015[july] += d.counts_2015.at(july);
    this->counts_2016[july] += d.counts_2016.at(july);
    this->counts_2017[july] += d.counts_2017.at(july);
    this->counts_2018[july] += d.counts_2018.at(july);
    this->counts_2019[july] += d.counts_2019.at(july);
    this->counts_2020[july] += d.counts_2020.at(july);
    this->counts_2021[july] += d.counts_2021.at(july);

    // August counts
    this->counts_2015[august] += d.counts_2015.at(august);
    this->counts_2016[august] += d.counts_2016.at(august);
    this->counts_2017[august] += d.counts_2017.at(august);
    this->counts_2018[august] += d.counts_2018.at(august);
    this->counts_2019[august] += d.counts_2019.at(august);
    this->counts_2020[august] += d.counts_2020.at(august);
    this->counts_2021[august] += d.counts_2021.at(august);

    // September counts
    this->counts_2015[sept] += d.counts_2015.at(sept);
    this->counts_2016[sept] += d.counts_2016.at(sept);
    this->counts_2017[sept] += d.counts_2017.at(sept);
    this->counts_2018[sept] += d.counts_2018.at(sept);
    this->counts_2019[sept] += d.counts_2019.at(sept);
    this->counts_2020[sept] += d.counts_2020.at(sept);
    this->counts_2021[sept] += d.counts_2021.at(sept);

    // October counts
    this->counts_2015[oct] += d.counts_2015.at(oct);
    this->counts_2016[oct] += d.counts_2016.at(oct);
    this->counts_2017[oct] += d.counts_2017.at(oct);
    this->counts_2018[oct] += d.counts_2018.at(oct);
    this->counts_2019[oct] += d.counts_2019.at(oct);
    this->counts_2020[oct] += d.counts_2020.at(oct);
    this->counts_2021[oct] += d.counts_2021.at(oct);

    // November counts
    this->counts_2015[nov] += d.counts_2015.at(nov);
    this->counts_2016[nov] += d.counts_2016.at(nov);
    this->counts_2017[nov] += d.counts_2017.at(nov);
    this->counts_2018[nov] += d.counts_2018.at(nov);
    this->counts_2019[nov] += d.counts_2019.at(nov);
    this->counts_2020[nov] += d.counts_2020.at(nov);
    this->counts_2021[nov] += d.counts_2021.at(nov);

    // December counts
    this->counts_2015[dec] += d.counts_2015.at(dec);
    this->counts_2016[dec] += d.counts_2016.at(dec);
    this->counts_2017[dec] += d.counts_2017.at(dec);
    this->counts_2018[dec] += d.counts_2018.at(dec);
    this->counts_2019[dec] += d.counts_2019.at(dec);
    this->counts_2020[dec] += d.counts_2020.at(dec);
    this->counts_2021[dec] += d.counts_2021.at(dec);

    return *(this);
};