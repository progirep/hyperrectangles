#include "interface.h"
#include <random>
#include <iostream>

int main(int argv, const char **args) {

    (void)argv;
    (void)args;

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


    ds.removeCoveredRectangles();


    std::cerr << "Computation finished.\n";
    std::cerr << "We have : " << ds.size() << " hyperrectagngles.\n";



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

    return 0;

}
