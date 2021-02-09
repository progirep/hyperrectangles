#include <random>
#include <iostream>
#include "interface.h"

//Input random hyper rectangles, mainly used for speed test
void test1()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);

    for (unsigned int i=0;i<10000;i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j=0;j<g_nofDimensions;j++) {
            min.push_back(rand());
            max.push_back(rand()+min.back());
        }
        ds.addRectangle(HyperRectangle(min,max));
    }


    std::cout << "before remove the covered rectangles, we have: " << ds.size() << std::endl;

    ds.removeCoveredRectangles();


    std::cout << "Computation finished.\n";
    std::cout << "We have : " << ds.size() << " hyperrectagngles.\n";
}

//the input hyper rectangle getting larger and larger(eg. the second one contains the first one, and it is contained by
//the third one. The third one is contained by the fourth one, the fourth one is contained by the fifth.)
//the remain hyper rectangles should be the same as inputs, because the input hyper rectangle is always has not covered area.
void test2()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 0; i < 50; i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j = 0; j < g_nofDimensions; j++) {
            min.push_back(0.0);
            max.push_back(i+0.5);
        }
        ds.addRectangleIfNotCoveredAlready(HyperRectangle(min,max));
    }

    std::cout << "we have: " << ds.size()  << " in the data structure." << std::endl;

}

//the remain hyper rectangles should be only one(the very first one). other hand of the test2.
void test3()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 1000; i >= 0; i--) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j = 0; j < g_nofDimensions; j++) {
            min.push_back(0.0);
            max.push_back(i+0.5);
        }
        ds.addRectangleIfNotCoveredAlready(HyperRectangle(min,max));
    }


    std::cout << "Computation finished.\n";
    std::cout << "We have : " << ds.size() << " hyperrectagngles.\n";
}

//the input logic is the same as test 2, but the remain hyper rectangles is rely on the sequence in rtree.
//in test2 and test3 we are calling addRectangleIfNotCoveredAlready(); so the already covered hyper rectangle can not be
//added into the data structure(rtree). But for test4, all the rectangles will be firstly added into the data structure(
// rtree), then the sequence of rectangles in the rtree are different as input.
//Thus the remain hyper rectangles may not be the same as the input hyper rectangles.
void test4()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 0; i < 20; i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j = 0; j < g_nofDimensions; j++) {
            min.push_back(0.0);
            max.push_back(i+0.5);
        }
        ds.addRectangle(HyperRectangle(min,max));
    }

    std::cout << "before remove the covered rectangles, we have: " << ds.size() << std::endl;
    /*for(auto i:ds.rtree)
    {
        std::cout << bg::dsv(i) << std::endl;
    }*/
    ds.removeCoveredRectangles();

    std::cout << "Computation finished.\n";
    std::cout << "We have : " << ds.size() << " hyperrectagngles.\n";
}

//the input logic is the same as test2, also firstly add all recs into data structure, then remove the covered ones.
void test5()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 20; i >= 0; i--) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j = 0; j < g_nofDimensions; j++) {
            min.push_back(0.0);
            max.push_back(i+0.5);
        }
        ds.addRectangle(HyperRectangle(min,max));
    }

    ds.removeCoveredRectangles();

    std::cout << "Computation finished.\n";
    std::cout << "We have : " << ds.size() << " hyperrectagngles.\n";
}


int main(int argv, const char **args) {

    test2();

    return 0;

}
