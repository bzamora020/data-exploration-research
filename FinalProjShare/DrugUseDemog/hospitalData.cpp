#include "hospitalData.h"
#include <memory>
#include <sstream>

#include "visitor.h"

/* print hospital data partial - you must fill in*/
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
			out << "Hospital Info: "  << HD.region << ", " << HD.state;
			out << "\nType: " << HD.type;
			out << "\nOverall rating (out of 5): " << HD.overallRating;
			out << "\nmortality rating: " << HD.mortalityRating;
			out << "\nreadmission rating:" << HD.readmitRating;
			return out;
}


void hospitalData::accept(class Visitor &v) {
	v.visit(shared_from_this());
}