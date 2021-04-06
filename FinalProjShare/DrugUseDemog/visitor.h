#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"
#include <memory>
#include "drugData.h"


class Visitor {

    public:
        virtual void visit(std::shared_ptr<hospitalData> hosp) = 0;
        virtual void visit(drugData &drugstuff){};
        virtual void visit(demogData &demog) = 0;

        //virtual void visit(comboHospitalData &combohosp) = 0;
        //virtual void visit(comboDemogddata &combodemog) = 0;
};



#endif