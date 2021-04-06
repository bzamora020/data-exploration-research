#ifndef RATING_H
#define RATING_H

#include <string>
#include<iostream>
#include <cmath>

using namespace std;

class rating {
public:
	//constructor that takes in a number
	rating(double inRating)  {
		setNumRating(inRating);
	}
	rating(string inRating) {
		setRating(inRating);
	}
	void setNumRating(double inRating){
		if(isnan(inRating))
			numRating = -1;
		else
			numRating = inRating;
		wordRating = to_string(inRating);
	}
	void setRating(string inRating){
		string wordRating=inRating;
		if(inRating == "Below"){
			numRating = 1;
		}
		else if(inRating == "Same"){
			numRating = 2;
		}
		else if(inRating == "Above"){
			numRating = 3;
		}
		else{
			numRating = -1;
		}
	}
	//a method to return a string based on the current rating TODO complete
	bool isEmpty(){ return (numRating == -1); }
	const string getRating() const{ return wordRating; }
	double getRatingNum() const{ return numRating; }

	friend std::ostream& operator<<(std::ostream &out, const rating &r) {
		//if mortality <= 1.5 return Below
		if(r.numRating<=1.5){
			out << "Below";
		}
		//if 1.5 < mortality <= 2.5 return Same
		else if(r.numRating<=2.5){
			out << "Same";
		}
		// if 2.5 < mortality return Above
		else{
			out << "Above";
		}
		return out;
	}

	rating& operator/=(const double Sc) {
		this->numRating /= Sc;
		return *this;
	}

	/* implement other operators for example, maybe... */
	rating& operator/(const int Sc) {
		this->numRating = this->numRating/Sc;
		return *this;
	}

	rating& operator+=(const rating r) {
		this->numRating += r.getRatingNum();
		return *this;
	}

	bool operator < (const rating& r) {
		return this->numRating<r.getRatingNum();
	}
	bool operator > (const rating& r) {
		return this->numRating>r.getRatingNum();
	}
	bool operator == (const rating& r) {
		return this->numRating==r.getRatingNum();
	}


	//TODO write operator overload


private:
	string wordRating;
	double numRating;
};
#endif
