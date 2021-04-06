#ifndef RATING_H
#define RATING_H

#include <string>
#include<iostream>

using namespace std;

class rating {
  public:
    public:
    //constructor that takes in a number
    rating(double inRating)  {
      numRating = inRating;
    }

  rating() {
    numRating = 0;
  }

    //constructor that takes in a string
    rating(string inRating) {
      if (inRating == "Above" )
	numRating = 2;
      else if (inRating == "Same")
	numRating = 1;
      else if (inRating == "Below")
	numRating = 0;
      else
	numRating = -1;
    }

    //a method to return a string based on the current rating TODO complete
    const string getRating() const;
  double getRatingNum() const{
    return numRating;
  }

  friend std::ostream& operator<<(std::ostream &out, const rating &r) {
    if (r.numRating > 1.5)
      out << "Above";
    else if (r.numRating > 0.5)
      out << "Same";
    else if (r.numRating >= 0)
      out << "Below";
    else
      out << "None"; 
    return out;

    }

    
  rating& operator+=(rating r) {
    numRating += r.numRating;
    return *this;
 }

  rating operator/(const int r) {
    rating Rating;
    Rating.numRating = this->numRating/r;
    return Rating;
  }

  bool operator<(const rating r) {
    return numRating < r.numRating;
  }

  bool operator>(const rating r) {
    return numRating > r.numRating;
  }
  
private:
  double numRating;
};
#endif
