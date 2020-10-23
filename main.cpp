#include "interface.h"
#include <random>
#include <iostream>
#include "RTree.h"

int main(int argv, const char **args) {

    const int nofDimensions = 4;

    DataStructureForHyperRectangles ds(nofDimensions);

    for (unsigned int i=0;i<5;i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j=0;j<nofDimensions;j++) {
            min.push_back(rand());
            max.push_back(rand()+min.back());
        }
        ds.addRectangle(HyperRectangle(min,max));
    }

    std::vector<double> min{1, 1,1,1};
    std::vector<double> max{2, 2,2,3};
    std::cout << ds.ifNotCoveredAlredy(HyperRectangle(min,max));
    //ds.removeCoveredRectangles();

    std::cerr << "Computation finished.\n";
    std::cerr << "We have : " << ds.size() << " hyperrectagngles.\n";
    return 0;

}




/*int main(){
    const int nofDimensions = 2;
    DataStructureForHyperRectangles ds(nofDimensions);
    std::vector<double> min1{1, 1};
    std::vector<double> max1{2, 2};
    ds.addRectangle(HyperRectangle(min1,max1));
    std::vector<double> min2{5, 5};
    std::vector<double> max2{3, 3};
    ds.addRectangle(HyperRectangle(min2,max2));
    std::vector<double> min3{3, 3};
    std::vector<double> max3{3, 3};
    ds.addRectangle(HyperRectangle(min3,max3));
    std::vector<double> min{1, 1};
    std::vector<double> max{2, 2};

    std::cout << ds.ifNotCoveredAlredy(HyperRectangle(min,max));
    return 0;
}*/

