#include "interface.h"
#include <random>
#include <iostream>

int main(int argv, const char **args) {


    DataStructureForHyperRectangles ds(g_nofDimensions);

    for (unsigned int i=0;i<100;i++) {

        std::vector<double> min;
        std::vector<double> max;
        for (unsigned int j=0;j<g_nofDimensions;j++) {
            min.push_back(rand());
            max.push_back(rand()+min.back());
        }
        ds.addRectangle(HyperRectangle(min,max,i));
    }

    ds.removeCoveredRectangles();

    std::cerr << "Computation finished.\n";
    std::cerr << "We have : " << ds.size() << " hyperrectagngles.\n";































/*    std::cout << ds.size() << std::endl;

    std::vector<double> rec4_min {999,999,999,999};
    std::vector<double> rec4_max {9999,9999,9999,9999};
    HyperRectangle search_rec(rec4_min, rec4_max, 333);*/







/*    std::vector<double> search_min{1, 1,1,1};
    std::vector<double> search_max{2000, 2000,2000,3000};
    HyperRectangle rectangle(search_min,search_max,99999);
    //std::cout << ds.ifNotCoveredAlredy(HyperRectangle(search_min,search_max,99999));
    //ds.removeCoveredRectangles();
    std::vector<HyperRectangle> overlap_recs;
    ds.overlap_search(rectangle,overlap_recs);

    std::cout << "we have :" <<

    std::cerr << "Computation finished.\n";
    std::cerr << "We have : " << ds.size() << " hyperrectagngles.\n";*/
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


/*RTree<int, int, nofDimensions, float>::Iterator it;
    ds.tree.GetFirst(it);
    while(!it.IsNull()){
        int value = *it;
        int min[nofDimensions] = {0,0,0,0};
        int max[nofDimensions] = {0,0,0,0};
        it.GetBounds(min, max);
        std::cout << "(";
        for(int i = 0; i < nofDimensions; i++){
            std::cout << min[i] << ",";
        }
        for(int i = 0; i < nofDimensions; i++){
            std::cout << max[i] << ",";
        }
        std::cout << ")" << std::endl;

        ds.tree.GetNext(it);
        std::cout << value << std::endl;
    }*/
