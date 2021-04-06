#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

/* very general data type for any kind of place data - very simple for lab04 */
class placeData {
public:

	placeData(string n) : name(n) {}
	placeData() : name("") {}
	
	string getName() const {
		return name;
	}

	//void toString(ostream& os) {}
    
	friend std::ostream& operator<<(std::ostream& out, const placeData& DD);
	
	virtual void accept(class Visitor& v) = 0;
	
private:
	string name;
};
#endif
