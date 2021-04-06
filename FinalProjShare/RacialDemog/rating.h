#ifndef RATING_H
#define RATING_H

#include <string>
#include<iostream>

using namespace std;

class rating {
  public:
    //constructor that takes in a number
    rating(double inRating)  {
        //TODO fill in
        num_rating = inRating;
        str_rating = "num";
    }

    //constructor that takes in a number
    rating(string inRating) {
        //TODO fill in
        str_rating = inRating;
        if(str_rating == "Below"){
            num_rating = 0;
        }
        else if(str_rating == "Same"){
            num_rating = 1;
        }
        else if(str_rating == "Above"){
            num_rating = 2;
        }
        else{
            num_rating = -1;
        }
    }

    //default
    rating(){
        num_rating = 0;
        str_rating = "num";
    }
    //a method to return a string based on the current rating TODO complete
    string getRating() const;
    double getRatingNum() const{
        return num_rating;
    }

    friend std::ostream& operator<<(std::ostream &out, const rating &r);

    
    
    //TODO write operator overload
    
    rating operator+=(const rating &r){
        this->num_rating += r.num_rating;
        //used to check if rating is a string or int
        if(r.str_rating != "num"){
            this->str_rating = r.str_rating;
        }
        return *this;
    }
    
    rating operator/(double len){
        double rat = this->num_rating /double(len);
        rating r{rat};
        r.str_rating = this->str_rating;
        return r;
    }
    
    bool operator<(const rating &r){
        return this->num_rating < r.num_rating;
    }
    
    bool operator>(const rating &r){
        return this->num_rating > r.num_rating;
    }
    

private:
     //TODO decide what data to represent
    double num_rating = 0;
    string str_rating = "";
};
#endif
