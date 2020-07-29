//
// Created by lijialin on 2020/7/28.
//

#include "interface.h"

//*****************************************Define coveredBy(HyperRectangle)********************************************
// The min point of rec1 is not in rec2 OR the max point of rec1 should not be in rec2 OR the min and max point of rec
// are both not inside rec2. Then rec1 is not totally covered by rec2.
bool HyperRectangle::coveredBy(HyperRectangle &rec2) const {
    for(int i = 0; i != dimension; ++i)
    {
        //min point of rec1 is not covered by rec2
        if(min[i] > rec2.max[i] || min[i] < rec2.min[i])
            return false;
        //max point of rec2 is not covered by rec2
        if(max[i] > rec2.max[i] || max[i] < rec2.min[i])
            return false;
    }
    return true;
}

//***************************************Define contain(std::vector<double>)*************************************
bool HyperRectangle::contain(std::vector<double> &point) const {
    //Use for loop to check every dimension
    for(int i = 0; i != dimension; ++i)
    {
        if(point[i] > this->max[i] || point[i] < this->min[i])
            return false;
    }
    return true;
}

//******************************************Define addRectangleIfNotCoveredAlready()*****************************************************
void DataStructureForHyperRectangles::addRectangle(const HyperRectangle &rectangle){
    total.push_back(rectangle);
}

//******************************************Define addRectangleIfNotCoveredAlready()*****************************************************
bool DataStructureForHyperRectangles::addRectangleIfNotCoveredAlready(const HyperRectangle &r) {
    for(auto& it : total)
    {
        if(r.coveredBy(it))
        {
            //std::cout << "Redundant rectangle!";
            return false;
        }
    }
    total.push_back(r);
    return true;
}

// ****************************************Define removeCoveredRectangle()*********************************************
void DataStructureForHyperRectangles::removeCoveredRectangles() {
    DataStructureForHyperRectangles newds(nofDimensions);
    for (const auto& it : total)
    {
        newds.addRectangleIfNotCoveredAlready(it);
    }
    total = newds.total;
}

unsigned int DataStructureForHyperRectangles::getNofRectangles() const{
    return total.size();
}

bool DataStructureForHyperRectangles::isPointContainedInAnyRectangle(std::vector<double>& point) const
{
    for(const auto& it : total)
    {
        // If point is contained by any rectangle in 'total', then this point is contained by 'total'.
        if(it.contain(point))
            return true;
    }
    return false;
}