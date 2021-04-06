#include "candidate.h"
#include <sstream>

/* print county demographic data */
std::ostream& operator<<(std::ostream& out, const candidate& D) {
    out  << D.name << "(" << D.party << ") " << D.votes;
    return out;
}