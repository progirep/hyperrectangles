//
// Created by lijialin on 2020/7/28.
//

#include "interface.h"

//******************************************Define MySearchCallback********************************************************
/**
     * @brief callback function to return the overlap hyper-rectangles
     * @param id the id of hyper-rectangle
     * @param arg the pointer of void* that return from the search function
     * */
std::vector<HyperRectangle> overlapset;

bool MySearchCallbackWriteToOverlapset(size_t id, void* arg)
{
    (void)id;
    std::vector<double> min;
    std::vector<double> max;
    for(int i = 0; i < g_nofDimensions; i++)
    {
        min.push_back(((Rect*)arg)->min[i]);
        max.push_back(((Rect*)arg)->max[i]);
    }

    HyperRectangle rec(min,max);
    overlapset.push_back(rec);
    return true; // keep going
}

bool MySearchCallback(size_t id, void* arg)
{
    (void)id;
    (void)arg;
    return true; // keep going
}


//*****************************************Define coveredBy(HyperRectangle)********************************************
// The min point of rec1 is not in rec2 OR the max point of rec1 should not be in rec2 OR the min and max point of rec
// are both not inside rec2. Then rec1 is not totally covered by rec2.
bool HyperRectangle::coveredBy(HyperRectangle &rec2) const {
    for(unsigned int i = 0; i < dimension; ++i)
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
    for(unsigned int i = 0; i < dimension; ++i)
    {
        if(point[i] > this->max[i] || point[i] < this->min[i])
            return false;
    }
    return true;
}

bool HyperRectangle::isExternal(HyperRectangle &r) const {
    for(unsigned int i = 0; i < dimension; ++i)
    {
        if (r.max[i] <= min[i] || r.min[i] >= max[i])
            return true;
    }
    return false;
}

//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//******************************************Define addRectangleIfNotCoveredAlready()*****************************************************
void DataStructureForHyperRectangles::addRectangle(const HyperRectangle &rectangle){
    int recMin[rectangle.dimension], recMax[rectangle.dimension];
    for (unsigned int i = 0; i < rectangle.dimension; i++)
    {
        recMin[i] = rectangle.min[i];
        recMax[i] = rectangle.max[i];
    }

    tree.Insert(recMin,recMax,rectangle.id);
}


int DataStructureForHyperRectangles::overlap_search(const HyperRectangle &rec) const{
    int search_min[g_nofDimensions];
    int search_max[g_nofDimensions];
    for(unsigned int i = 0; i < rec.dimension; i++){
        search_min[i] = rec.min[i];
        search_max[i] = rec.max[i];
    }
    return tree.Search(search_min, search_max, MySearchCallbackWriteToOverlapset, nullptr);
}


//******************************************Define ifNotCoveredAlready********************************************************
bool DataStructureForHyperRectangles::ifNotCoveredAlready(const HyperRectangle &r) {

    //search for overlap hyper rectangles
    overlapset.clear();
    overlap_search(r);

    std::cout << std::endl;
    std::cout << "Overlap hyper rectangles : " << overlapset.size() << std::endl;

    if(overlapset.empty()){return false;}

    //to check if the r is totally covered by overlap hyper rectangles
    //transfer overlap hyper rectangles to overlapset_trans, store all the values in every dimension. and values in each
    // dimension has been stored in one vector<double>.

    std::vector<std::vector<double>> overlapset_trans;

    for (unsigned int i = 0; i < r.dimension; i++){
        std::vector<double> overlapset_trans_temp;//temp vector<double>, to store all the values in one dimension.
        for (auto &it : overlapset){
            overlapset_trans_temp.push_back(it.min[i]);
            overlapset_trans_temp.push_back(it.max[i]);
        }
        overlapset_trans.push_back(overlapset_trans_temp);
        overlapset_trans[i].push_back(r.min[i]);
        overlapset_trans[i].push_back(r.max[i]);
    }

    //Remove duplicate points and sort the points
    for(auto & it : overlapset_trans){
        std::sort(it.begin(), it.end());
        it.erase(std::unique(it.begin(), it.end()), it.end());
    }

    //remove the value in different dimension that not inside of the r
    for(unsigned int i = 0; i < nofDimensions; i++){
        auto it_min = std::find(overlapset_trans[i].begin(),overlapset_trans[i].end(),r.min[i]);//find r.min[i] iterator
        auto it_max = std::find(overlapset_trans[i].begin(),overlapset_trans[i].end(),r.max[i]);//find r.max[i]
        overlapset_trans[i].erase(overlapset_trans[i].begin(), it_min);//delete value smaller than r.min[i]
        overlapset_trans[i].erase(it_max, overlapset_trans[i].end());//delete value larger than r.max[i]
    }

    //output overlapset_trans before going to Cartesian product calculation
    /*for(int i = 0; i < g_nofDimensions; i++){
        std::cout << "The number of elements in overlapset_trans " << i + 1<< " dimension: " << overlapset_trans[i].size() << std::endl;
    }*/

    //pre check the number of points will be generated in Cartesian product point set
    //if the number of Cartesian product points will be larger than the pre set value then check the new added hyper re-
    // ctangle has a uniform distribution point is not covered by any hyper rectangle in the data structure.
    //
    unsigned long long res_num_max = 1;
    for(int i = 0; i < g_nofDimensions; i++)
    {
        res_num_max = overlapset_trans[i].size() * res_num_max;

        if(res_num_max > g_max_num_of_points)//check the total of cartesian product is larger than pre set or not
        {
            std::vector<std::vector<double>> uniform_random_points;

            uniform_random_points = getUniformlyRandomPoints(r.min, r.max);

            for(auto& it : uniform_random_points)
            {
                if(!isPointContainedInAnyRectangle(it))
                {
                    return false;
                }
            }
            return true;
        }
    }


    //Cartesian product to calculate all the possible combination(points)
    std::vector<double> tmp;
    std::vector<std::vector<double>> res;//res to store the results
    int layer = 0;
    productImplement(overlapset_trans, res, layer, tmp);
    /*std::cout << "Result of Cartesian product (points) : " << res.size() << std::endl;*/


    //if there is one point in res is not contained by rtree, then r is not totally covered by this set of hyper recs.
    for(auto & it : res){
        if(isPointContainedInAnyRectangle(it)){}
        else{
            return false;
        }
    }
    return true;
}




//******************************************Define addRectangleIfNotCoveredAlready()*****************************************************
bool DataStructureForHyperRectangles::addRectangleIfNotCoveredAlready(const HyperRectangle &r) {

    if (ifNotCoveredAlready(r)){
        return false;
    }
    else{
        addRectangle(r);
        return true;
    }
}


// ****************************************Define isPointContainedInAnyRectangle()**************************************

bool DataStructureForHyperRectangles::isPointContainedInAnyRectangle(std::vector<double>& point)  const
{
    int search_min[nofDimensions];
    int search_max[nofDimensions];
    for(unsigned int i = 0; i < nofDimensions; i++){
        search_min[i] = point[i];
        search_max[i] = point[i];
    }

    int n = tree.Search(search_min, search_max, MySearchCallback, nullptr);
    if(n){
        return true;
    }
    else{//n is 0, represent this point is not contained by any hyper rectangles in the data structure
        return false;
    }
}

// ****************************************Define productImplement()**************************************

void DataStructureForHyperRectangles::productImplement(std::vector<std::vector<double>> dimvalue,
                                                       std::vector<std::vector<double>> &res, unsigned int layer,
                                                       std::vector<double> tmp) const{
    if (layer < dimvalue.size() - 1){
        for (unsigned int i = 0; i < dimvalue[layer].size(); i++){
            std::vector<double> sb;
            sb.clear();

            for (unsigned int i = 0; i < tmp.size(); i++){
                sb.push_back(tmp[i]);
            }
            sb.push_back(dimvalue[layer][i]);
            productImplement(dimvalue, res, layer+1,sb);
        }
    }
    else if (layer == dimvalue.size()-1){
        for (unsigned int j = 0; j < dimvalue[layer].size();j++){
            tmp.push_back(dimvalue[layer][j]);
            res.push_back(tmp);
            tmp.pop_back();
        }
    }

}


// ****************************************Define removeCoveredRectangle()*********************************************
void DataStructureForHyperRectangles::removeCoveredRectangles() {

    DataStructureForHyperRectangles newds(g_nofDimensions);

    RTree<size_t , int , g_nofDimensions, double >::Iterator it;

    for (tree.GetFirst(it); !tree.IsNull(it); tree.GetNext(it)){

        int arr_min[g_nofDimensions], arr_max[g_nofDimensions];
        it.GetBounds(arr_min,arr_max);
        int id = tree.GetAt(it);

        std::vector<double> vec_min, vec_max;
        for(int i = 0; i < g_nofDimensions; i++){
            vec_min.push_back(arr_min[i]);
            vec_max.push_back(arr_max[i]);
        }

        HyperRectangle rec(vec_min,vec_max, id);

        newds.addRectangleIfNotCoveredAlready(rec); //newds中都是不重叠的hyper rectengles
    }

    tree.RemoveAll();//把newds.tree通过迭代器赋值给ds.tree

    RTree<size_t , int , g_nofDimensions, double >::Iterator it_newds;

    for(newds.tree.GetFirst(it_newds); !it_newds.IsNull(); newds.tree.GetNext(it_newds)){
        int arr_min[g_nofDimensions], arr_max[g_nofDimensions];
        int id_newds = newds.tree.GetAt(it_newds);
        it_newds.GetBounds(arr_min, arr_max);
        tree.Insert(arr_min,arr_max,id_newds);
    }
    /*std::cout << size() << std::endl;
    std::cout << newds.size() << std::endl;*/
}

void DataStructureForHyperRectangles::getListOfAllRectangles(
        std::list<std::pair<std::vector<double>, std::vector<double>>> &listToStoreTo) const {

    RTree<size_t , int , g_nofDimensions, double >::Iterator it;
    std::pair<std::vector<double>, std::vector<double>> hyperrecranle;
    for (tree.GetFirst(it); !tree.IsNull(it); tree.GetNext(it)) {

        int arr_min[g_nofDimensions], arr_max[g_nofDimensions];
        it.GetBounds(arr_min, arr_max);

        std::vector<double> vec_min, vec_max;
        for (int i = 0; i < g_nofDimensions; i++) {
            vec_min.push_back(arr_min[i]);
            vec_max.push_back(arr_max[i]);
        }
        hyperrecranle = std::make_pair(vec_min, vec_max);
        listToStoreTo.push_back(hyperrecranle);
    }


}


std::vector<std::vector<double>> DataStructureForHyperRectangles::getUniformlyRandomPoints(std::vector<double>spaceMin,
                                                                                           std::vector<double>spaceMax)
                                                                                           const {
    for(int i = 0; i < g_nofDimensions; i++)
    {
        assert(spaceMin[i] <= spaceMax[i]);
    }

    std::vector<std::vector<double>> uniformRandomPoints;

    double root = 1.0 / (double) g_nofDimensions;
    double n = pow((double) g_max_num_of_points, root);

    for(int i = 0; i < g_nofDimensions; i++)
    {
        double longth = spaceMax[i] - spaceMin[i];

        std::vector<double> dimension_temp{spaceMin[i]};

        if(n > longth){n = longth;}

        double ceil = longth / n;

        for(int j = 0; j < n-1; j++)
        {
            dimension_temp.push_back(dimension_temp.back()+ceil);
        }

        dimension_temp.push_back(spaceMax[i]);

        uniformRandomPoints.push_back(dimension_temp);
    }

    //Cartesian product to calculate all the possible combination(points)
    std::vector<double> tmp;
    std::vector<std::vector<double>> res;//res to store the results
    int layer = 0;
    productImplement(uniformRandomPoints, res, layer, tmp);

    return res;
}

//*****************************************define getAUniformlyRandomPointNotCoveredByAnyRectangleAlready()*************
std::vector<double> DataStructureForHyperRectangles::getAUniformlyRandomPointNotCoveredByAnyRectangleAlready(
        std::vector<double> spaceMin, std::vector<double> spaceMax) const {

        HyperRectangle search_rec(spaceMin, spaceMax);
        overlapset.clear();
        overlap_search(search_rec);
        if(overlapset.empty()){return spaceMin;}

        std::vector<std::vector<double>> overlapset_trans;

        for (unsigned int i = 0; i < search_rec.dimension; i++) {
            std::vector<double> overlapset_trans_temp;//temp vector<double>, to store all the values in one dimension.
            for (auto &it : overlapset) {
                overlapset_trans_temp.push_back(it.min[i]);
                overlapset_trans_temp.push_back(it.max[i]);
            }
            overlapset_trans.push_back(overlapset_trans_temp);
            overlapset_trans[i].push_back(search_rec.min[i]);
            overlapset_trans[i].push_back(search_rec.max[i]);
        }

        for (auto &it : overlapset_trans) {
            std::sort(it.begin(), it.end());
            it.erase(std::unique(it.begin(), it.end()), it.end());
        }

        for (unsigned int i = 0; i < nofDimensions; i++) {
            auto it_min = std::find(overlapset_trans[i].begin(), overlapset_trans[i].end(),
                                    search_rec.min[i]);//find r.min[i] iterator
            auto it_max = std::find(overlapset_trans[i].begin(), overlapset_trans[i].end(),
                                    search_rec.max[i]);//find r.max[i]
            overlapset_trans[i].erase(overlapset_trans[i].begin(), it_min);//delete value smaller than r.min[i]
            overlapset_trans[i].erase(it_max, overlapset_trans[i].end());//delete value larger than r.max[i]
        }

        unsigned long long res_num_max = 1;
        for (int i = 0; i < g_nofDimensions; i++) {

            res_num_max = overlapset_trans[i].size() * res_num_max;

            if (res_num_max > g_max_num_of_points) {//generate 1000000 uniform random points in search hyper rectangle and check
                std::vector<std::vector<double>> uniform_random_points;

                uniform_random_points = getUniformlyRandomPoints(spaceMin, spaceMax);

                for(auto& it : uniform_random_points)
                {
                    if(!isPointContainedInAnyRectangle(it))
                    {
                        return it;
                    }
                }
            }
        }

        //Cartesian product to calculate all the possible combination(points)
        std::vector<double> tmp;
        std::vector<std::vector<double>> res;//res to store the results
        int layer = 0;
        productImplement(overlapset_trans, res, layer, tmp);
        /*std::cout << "Cartesian product results points: " << res.size() << std::endl;*/


        //if there is one point in res is not contained by rtree, then r is not totally covered by this set of hyper recs.
        for(auto & it : res){
            if(!isPointContainedInAnyRectangle(it))
            {
                return it;
            }
        }

        // What if this does not work?
        throw 123;
}
