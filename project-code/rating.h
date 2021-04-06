#ifndef RATING_H
#define RATING_H

#include <string>
#include<iostream>
#include <cassert>

using namespace std;

class rating {
  public:
    rating(double inRating)  {
        numericRating = std::max(0.0,inRating);
    }
    rating(string inRating) {
        //default to 'unknown'
        numericRating = 0;
        if (inRating.compare("Below") == 0)
            numericRating = 1.0;
        else if (inRating.compare("Same") == 0)
            numericRating = 2.0;
        else if (inRating.compare("Above") == 0)
            numericRating = 3.0;
    }

    const string getRating() const;
    double getRatingNum() const { return numericRating; }

    friend std::ostream& operator<<(std::ostream &out, const rating &r) {
        out << r.getRating();
        return out;
    }

    rating& operator/=(const double Sc) {
        numericRating/=Sc;
        return *(this);
    }

    rating& operator/=(const int Sc) {
        numericRating/=Sc;
        return *(this);
    }

    rating& operator/(const int Sc) {
        numericRating/=Sc;
        return *(this);
    }

    rating& operator+=(const rating r) {
        if (r.numericRating > 0) {
            numericRating += r.numericRating;
        }
        return *(this);
    }
    
    bool operator < (const rating& r) {
        //validity check
        if (numericRating < r.numericRating)
            return true;
        return false;
    }
    
private:
    double numericRating;
};
#endif
