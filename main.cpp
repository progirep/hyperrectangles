#include <random>
#include <iostream>
#include "interface.h"


void test1()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);

    for (unsigned int i=0;i<100;i++) {

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


void test2()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 0; i < 5; i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j = 0; j < g_nofDimensions; j++) {
            min.push_back(0.0);
            max.push_back(i+0.5);
        }
        ds.addRectangleIfNotCoveredAlready(HyperRectangle(min,max));
    }

    std::cout << "we have: " << ds.size()  << "in our Rtree" << std::endl;

}

void test3()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 10; i >= 0; i--) {

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

void test4()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 10; i >= 0; i--) {

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

void test5()
{
    DataStructureForHyperRectangles ds(g_nofDimensions);
    for (int i = 0; i < 5; i++) {

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



    test5();


    return 0;

}






/*std::vector<double> min{6,6,6,6};
    std::vector<double> max{8,8,8,8};

    std::vector<double> res = ds.getAUniformlyRandomPointNotCoveredByAnyRectangleAlready(min, max);

    std::cerr << "This point is not covered: ";
    for(auto& it : res)
    {
        std::cerr << it << ",";
    }
    std::cerr << "\n";*/



/*std::list<std::pair<std::vector<double>, std::vector<double>>> ds_list;
ds.getListOfAllRectangles(ds_list);
std::cerr << "We have : " << ds_list.size() << " hyperrectagngles in list.\n";*/
