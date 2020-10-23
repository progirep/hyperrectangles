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
//to check if the r is totally covered by total?
    //transfer total to total_trans, store all the values in every dimension. and values in each dimension has been
    // stored in one vector<double>.
    std::vector<std::vector<double>> total_trans;
    for (int i = 0; i < r.dimension; i++){
        std::vector<double> total_trans_temp;//temp vector<double>, to store all the values in one dimension.
        for (auto &it : total){
                total_trans_temp.push_back(it.min[i]);
                total_trans_temp.push_back(it.max[i]);
        }
        total_trans.push_back(total_trans_temp);
        total_trans[i].push_back(r.min[i]);
        total_trans[i].push_back(r.max[i]);
    }

    //Remove duplicate points
    for(auto & it : total_trans){
        std::sort(it.begin(), it.end());
        it.erase(std::unique(it.begin(), it.end()), it.end());
    }

    //Cartesian product to calculate all the possible combination(points)
    std::vector<double> tmp;
    std::vector<std::vector<double>> res;//res to store the results
    int layer = 0;
    productImplement(total_trans, res, layer, tmp);

    //输出total_trans
    for(auto & it : total_trans){
        for(auto & itt : it){
            std::cout << itt << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "*************************************************************";
    std::cout << std::endl;

/*    //输出res
    for(int i = 0; i < res.size(); i++){
        for(auto & j : res[i])
            std::cout << j << ",";
        std::cout << std::endl;
    }
    std::cout << "*************************************************************";
    std::cout << std::endl;*/


    //delete the points that not inside of the new rectangle r
    for(auto it = res.begin(); it != res.end();){
        if(r.contain(*(it))){
            it++;
        }
        else{
            it = res.erase(it);
        }
    }

/*    //输出在r中的res
    for(int i = 0; i < res.size(); i++){
        for(auto & j : res[i])
            std::cout << j;
        std::cout << std::endl;
    }
    std::cout << "*************************************************************";
    std::cout << std::endl;*/

    //if there is one point in res is not contained by total, then r is not totally covered by total.
    for(auto & it : res){
        if(!isPointContainedInAnyRectangle(it)){ //如果这个rec的set不是contain这个点。则说明rec中的点有没有被totalcontain。所以rec没有完全被覆盖。
            return true;
        }
    }
    return false;
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

void DataStructureForHyperRectangles::productImplement(std::vector<std::vector<double>> dimvalue,
                                                       std::vector<std::vector<double>> &res, int layer,
                                                       std::vector<double> tmp) {
    if (layer < dimvalue.size() - 1){
        for (int i = 0; i < dimvalue[layer].size(); i++){
            std::vector<double> sb;
            sb.clear();

            for (int i = 0; i < tmp.size(); i++){
                sb.push_back(tmp[i]);
            }
            sb.push_back(dimvalue[layer][i]);
            productImplement(dimvalue, res, layer+1,sb);
        }
    }
    else if (layer == dimvalue.size()-1){
        for (int j = 0; j < dimvalue[layer].size();j++){
            tmp.push_back(dimvalue[layer][j]);
            res.push_back(tmp);
            tmp.pop_back();
        }
    }

}




