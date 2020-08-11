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

bool HyperRectangle::isExternal(HyperRectangle &r) const {
    for(int i = 0; i != dimension; ++i)
    {
        if (r.max[i] <= min[i] || r.min[i] >= max[i])
            return true;
    }
    return false;
}

//******************************************Define addRectangleIfNotCoveredAlready()*****************************************************
void DataStructureForHyperRectangles::addRectangle(const HyperRectangle &rectangle){
    total.push_back(rectangle);
}

bool DataStructureForHyperRectangles::ifNotCoveredAlredy(const HyperRectangle &r) {
    for(auto& it : total)
    {
        if(r.coveredBy(it))
        {
            return false;
        }
        else if (r.isExternal(it)) //r is at the external of the it, and also r should be at external of every recs in the total set. Then we can say r is not covered by total.
        {
            continue;//跳过本次循环，进行下一次，如果每次都是在rec的外部的话。则说明这个r is not covered already by this total.
        }
        else//r不是完全在it的内部，r也不是完全在rec的外部，那么r就是与rec有部分是相交的。
        {
            ;//递归找出r是不是被其他的rec所覆盖
        }
    }
}

//******************************************Define addRectangleIfNotCoveredAlready()*****************************************************
bool DataStructureForHyperRectangles::addRectangleIfNotCoveredAlready(const HyperRectangle &r) {

    if (ifNotCoveredAlredy(r)){
        total.push_back(r);
        return true;
    }
    else{
        return false;
    }
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