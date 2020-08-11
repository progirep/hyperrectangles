//
// Created by lijialin on 2020/7/28.
//

#ifndef HYPERRECTANGLESRTREE_INTERFACE_H
#define HYPERRECTANGLESRTREE_INTERFACE_H

#include <vector>
#include <cassert>
#include <list>
#include <iostream>

//******************************************HyperRectangle Class*******************************************************
// @brief Data Structure for rectangle.
class HyperRectangle {

public:
    // @Member variable dimension: the number of dimension of Hyper-rectangle object.
    // @Member variable min: The corner of the hyper-rectangle in which the values along all dimensions are minimal.
    // This is a vector with d-dimension, the number of elements in this vector should be the same as the number of
    // dimension.
    // @Member variable max: The corner of the hyper-rectangle in which the values along all dimensions are maximal.
    // This is a vector with d-dimension, the number of elements in this vector should be the same as the number of
    // dimension.
    unsigned int dimension = 1;
    std::vector<double> min;
    std::vector<double> max;


public:
    //*************************************constructor*****************************************************************
    // @brief Constructor: generate a new hyper-rectangle object.
    // @param ds: The number of dimensions of the hyper-rectangle.
    // @param mini: The minimum point defining the lower bound of the hyper-rectangle.
    // @param maxi: The maximum point defining the upper bound of the hyper-rectangle.
    HyperRectangle(std::vector<double> &mini, std::vector<double> &maxi) : dimension(mini.size()), min(mini), max(maxi) {
        assert(mini.size()==maxi.size());
    }

    //**************************************if covered by***************************************************************
    // @brief Check this rectangle is totally covered by the other rectangle or not.
    // @return True if the rectangle has been totally covered by rec2; False if it was not totally covered.

    bool coveredBy(HyperRectangle &rec2) const;


    //*************************************contain*********************************************************************
    // @brief If the specified point is contained within this rectangle.
    // @param point Should has the same dimension as rectangle.
    bool contain(std::vector<double> &point) const;

    // @brief If the rec1 is at external of the rec2，These two recs has no intersection.
    // @param hyperrectangle that has the same dimension as the rec1
    bool isExternal(HyperRectangle& r) const;

    // ===================================== Flex Goals ====================================================
    std::vector<double> getAUniformlyRandomPointNotCoveredByAnyRectangleAlready(std::vector<double> spaceMin, std::vector<double> spaceMax) const;

};

class DataStructureForHyperRectangles {
private:
    // .... internal components
    std::vector<HyperRectangle> total;
    unsigned int nofDimensions;

public:
    /**
     * @brief Constructor -- Generates a new data structure instance for storing hyper-rectangles
     * @param nofDimensions The number of dimensions of each hyper-rectangle later stored in this data structure. Must be at least 1
     */
    DataStructureForHyperRectangles(unsigned int _nofDimensions) : nofDimensions(_nofDimensions) {};
    ~DataStructureForHyperRectangles() {};

    /**
     * @brief Adds a new rectangle
     * @param rectangle The new hyperrectangle
     */
    void addRectangle(const HyperRectangle &rectangle);

    /**
    * @brief Returns the number of hyper-rectangles contained in this data structure
    * @return the number of hyper-rectangles.
    */
    unsigned int size() {
        return total.size();
    }

    /**
     * @brief check if the hyper-rectangles is covered already. Return true if rectangle is covered, return false if the rectangle is not totally covered.
     * @param r The rectangle that need to be check.
     * */
     bool ifNotCoveredAlredy(const HyperRectangle& r);

    /**
     * @brief Adds a new rectangle if it is not already covered by the other rectangles already in the data structure
     * @return True if the rectangle has been added, False if it was totally covered by total
     * @param rectangle The new hyperrectangle
     */
    bool addRectangleIfNotCoveredAlready(const HyperRectangle &rectangle);

    /**
     * @brief Removes redundant rectangles, i.e., consisting only of points already covered in other rectangles.
     *        Note that the result is not unique.
     */
    void removeCoveredRectangles();


    /**
     * @brief getNofRectangles
     * @return How many rectangles are in the data structure
     */
    unsigned int getNofRectangles() const;

    /**
     * @brief isPointContainedInAnyRectangle
     * @return True if the set of hyper-rectangle is contain this point
     * @return False if the set of hyper-rectangle is not contain this point
     */
    bool isPointContainedInAnyRectangle(std::vector<double>& point) const;

    /**
     * @brief Stores a copy of all rectangles into the list provided.
     * @param listToStoreTo A reference to a list for putting the rectangles into.
     */
    void getListOfAllRectangles(std::list<std::pair<std::vector<double>, std::vector<double> > > &listToStoreTo) const;


    // ===================================== Flex Goals ====================================================
    std::vector<double> getAUniformlyRandomPointNotCoveredByAnyRectangleAlready(std::vector<double> spaceMin, std::vector<double> spaceMax) const;

};


#endif //HYPERRECTANGLESRTREE_INTERFACE_H
