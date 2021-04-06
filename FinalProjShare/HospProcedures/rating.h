#ifndef RATING_H
#define RATING_H

#include <string>
#include <iostream>
#include <iomanip>

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
  rating(double inRating) :
    useString(false), overall(inRating), general("None"), count(1){
      if (overall == -1.0 ){
        isValid = false;
      } else {
        isValid = true;
      }
  }
  rating(string inRating) :
    useString(true), general(inRating), count(1){

      if (general == "Below") {
        overall = 1.0;
      } else if (general == "Same") {
        overall = 2.0;
      } else if (general == "Above"){
        overall = 3.0;
      } else{
        overall = 0.0;
        isValid = false;
      }

      if (overall != 0.0){
        isValid = true;
      }

  }

  //used to initalize empty ratings
  rating( bool useS ) : overall(0.0), general("None"), count(0), useString(useS), isValid(true) {}

  //required after adding desired ratings, mainly for averaging purposes.
  virtual void updateRating();

  int getCount() { return count; }
  const string getRating() const { return general; }
  double getRatingNum() const { return overall; }


  friend std::ostream& operator<<(std::ostream &out, const rating &r) {
      if (r.useString){
        out << r.general;
      } else {
        out << setprecision(2) << fixed;
        out << r.overall;
      }
      return out;
  }

  rating& operator+=(const rating r) {
      if (!isValid || !r.isValid){
        return *this; //aka do nothing becuase either dont have valid ratings
      }

      if (useString != r.useString){
        return *this; //aka do nothing because of incompatible rating "types" (Rare)
      } else { //regardless of rating type, add and count.
        overall += r.overall;
        count++;
        return *this;
      }
  }

  //Use only when updateRating has been called.
  bool operator<(const rating& r) {
      return overall < r.overall;
  }

  bool operator==(const rating& r) {
      return overall == r.overall;
  }

  bool operator>(const rating& r) {
      return overall > r.overall;
  }



protected:
  double overall;
  string general;
  int count; //number of ratings being held.

  bool useString; //to determine what data types to use, update, and return
  bool isValid; //determine whether or not to use in computations.

/*
Scale;
  1 - below
  2 - same
  3 - above
*/
};
#endif
