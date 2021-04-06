#ifndef RATING_H
#define RATING_H

#include <string>
#include <iostream>
#include <map>

using namespace std;

class rating {
  public:
    rating(){}
    //constructor that takes in a number
    rating(double inRating) {
        ratingNum = inRating;
        this->updateRating();
    }

    //constructor that takes in a string
    rating(string inRating) {
        ratingStr = inRating;
        ratingNum = ratingValues[ratingStr];
    }

    //a method to return a string based on the current rating TODO complete
    const string getRating() const { return ratingStr; }
    double getRatingNum() const { return ratingNum; }

    friend std::ostream& operator<<(std::ostream &out, const rating &r);

    // method to update string rating based on number rating
    void updateRating() {

        double BELOW = ratingValues["Below"];

        if (ratingNum > BELOW && ratingNum <= BELOW + 0.5)
            ratingStr = "Below";
        else if (BELOW + 0.5 < ratingNum && ratingNum <= BELOW + 1.5)
            ratingStr = "Same";
        else if (BELOW + 1.5 < ratingNum && ratingNum <= BELOW + 2.5)
            ratingStr = "Above";
        else if (ratingNum < 0)
            ratingStr = "None";
    }

    bool isValid() {
        return !(ratingStr == "None");
    }

    // operator overloads
    rating& operator+=(const rating &r) {
        ratingNum += r.ratingNum;
        this->updateRating();
        
        return *this;
    }

    rating& operator/=(const int &r) {
        ratingNum /= (double)r;
        this->updateRating();

        return *this; 
    }

    rating& operator*=(const int &r) {
        ratingNum *= (double)r;
        this->updateRating();

        return *this;
    }

    bool operator<(const rating &r) {
        return ratingNum < r.ratingNum;
    }

    bool operator>(const rating &r) {
        return ratingNum > r.ratingNum;
    }


private:
    string ratingStr;
    double ratingNum;

    map<string, double> ratingValues {
        {"None", -1},
        {"Below", 1.0},
        {"Same", 2.0},
        {"Above", 3.0}
    };
};

inline rating operator+(rating l, const rating &r) {
	l += r;
	return l;
}

inline rating operator/(rating l, const int &r) {
	l /= r;;
	return l;
}

inline rating operator*(rating l, const int &r) {
	l *= r;;
	return l;
}
#endif

