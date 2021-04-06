#ifndef VISITREP_H
#define VISITREP_H

#include "hospitalData.h"
#include "demogData.h"
#include "visitor.h"

class visitorReport : public Visitor{
	virtual void visit(shared_ptr<hospitalData> h){
		cout<<"\nHospital Info: "<<h->getState();
		cout<<"\nOverall rating (out of 5): "<<h->getOverallRate();
	}
	virtual void visit(shared_ptr<demogData> d){
		cout<<"\nDemographics Info (State): "<<d->getState();
		cout<<"\nEducation info:";
		cout<<"\n(% Bachelor degree or more): "<<d->getBAup();
		cout<<"\n(% high school or more): "<<d->getHSup();
		cout<<"\n% below poverty: "<<d->getBelowPoverty();
	}
};

#endif
