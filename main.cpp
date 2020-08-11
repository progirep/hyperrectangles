#include "interface.h"
#include <random>
#include <iostream>

int main(int argv, const char **args) {

    const int nofDimensions = 4;

    DataStructureForHyperRectangles ds(nofDimensions);

    for (unsigned int i=0;i<5000000;i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j=0;j<nofDimensions;j++) {
            min.push_back(rand());
            max.push_back(rand()+min.back());
        }
        std::cout << i << std::endl;
        ds.addRectangle(HyperRectangle(min,max));
    }

    ds.removeCoveredRectangles();

    std::cerr << "Computation finished.\n";

}

