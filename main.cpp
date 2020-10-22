#include "interface.h"
#include <random>
#include <iostream>
#include "RTree.h"

int main(int argv, const char **args) {

    const int nofDimensions = 4;

    DataStructureForHyperRectangles ds(nofDimensions);

    for (unsigned int i=0;i<30;i++) {

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
    std::cerr << "We have : " << ds.size() << " hyperrectagngles.\n";

}
/*    int nofDimensions = 2;
    DataStructureForHyperRectangles ds(nofDimensions);
    std::vector<double> min1{1, 1};
    std::vector<double> max1{2, 2};
    ds.addRectangle(HyperRectangle(min1,max1));
    std::vector<double> min2{1, 1};
    std::vector<double> max2{3, 3};
    ds.addRectangle(HyperRectangle(min2,max2));
    std::vector<double> min3{1, 1};
    std::vector<double> max3{2, 2};

    std::cout << ds.ifNotCoveredAlredy(HyperRectangle(min3,max3));
    return 0;
}*/

