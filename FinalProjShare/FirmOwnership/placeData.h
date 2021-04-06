#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>
#include <memory>

class Visitor;

using namespace std;

/* very general data type for any kind of place data - very simple for lab04 */
class placeData : public std::enable_shared_from_this<placeData>{
	//TODO define
public:
	placeData(string s):
		region(s){}

	std::shared_ptr<placeData> getptr() {
        return shared_from_this();
    }

	string getState() const { return region; }

	friend std::ostream& operator<<(std::ostream &out, const placeData& DD){
		return DD.print(out);
	}
	virtual ~placeData(){}

	virtual void accept(class Visitor &v) = 0;

protected:
	virtual std::ostream& print(std::ostream &out) const = 0;

protected:
	string region;
};
#endif
