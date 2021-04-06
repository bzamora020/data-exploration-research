#ifndef RATING_H
#define RATING_H

#include <string>
#include <iostream>

using namespace std;

/* 
A class to represent a rating system that uses both words and numbers
(see CORGIS hospital data for an example)
Rating.Overall  Integer     Overall rating between 1 and 5 stars, with 5 stars being the highest rating; -1 represents no rating.
Rating.Mortality    String  Above, Same, Below, or Unknown comparison to national hospital mortality
Rating.Safety   String  Above, Same, Below, or Unknown comparison to national hospital safety 
*/
class rating {
  public:
      //default is 0
    rating() : inR(0) {}
    rating(double inRating) {
        update(inRating);
    }
    /*
    n < “below” <= n+0.5
    n+.5 < “same” <= n+1.5
    n+1.5 < “above” <= n+2.5
    */
    rating(string inRating){ 
        update(inRating);
    }

    const string getRating() const { return inRS; }
    void setRating(double d) { inR = d; update(d); }
    void setRating(string s) { inRS = s; update(s); }
    void setRating(rating r) { inR = r.getRatingNum(); inRS = r.getRating(); }
    double getRatingNum() const { return inR; }

    rating& operator=(const double Sc) { inR = Sc; return *this; }
    rating& operator*=(const double Sc) { inR *= Sc; return *this; }
    rating& operator*(const double Sc) { inR *= Sc; return *this; }
    rating& operator/=(const double Sc) { inR /= Sc; return *this; }
    rating& operator/(const int Sc) { inR /= Sc; return *this; }
    rating& operator+(const rating r) { inR += r.inR; return *this; }
    rating& operator+=(const rating r) { inR += r.inR; return *this; }
    rating& operator+(const double Sc) { inR += Sc; return *this; }
    rating& operator+=(const double Sc) { inR += Sc; return *this; }
    bool operator < (const rating& r) { return this->getRatingNum() < r.getRatingNum(); }
    
    void update(string inRating){
        inRS = inRating;
        if (inRating.compare("Below") == 0)
            inR = 0;
        else if (inRating.compare("Same") == 0)
            inR = 1;
        else if (inRating.compare("Above") == 0)
            inR = 2;
        else
            inR = -1; //last option is undefined
    }

    void update(double inRating){
        inR = inRating;
        if (inRating == -1)
            inRS = "Unknown";
        else if (inRating > 0 && inRating <= 0.5)
            inRS = "Below";
        else if (inRating > 0.5 && inRating <= 1.5)
            inRS = "Same";
        else
            inRS = "Above";
    }
    friend ostream& operator<<(ostream& out, const rating &r);
private:
    double inR;
    string inRS; //string version of rating
};
#endif
