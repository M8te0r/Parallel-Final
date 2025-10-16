#include <iostream>
#include "mesh/mesh.h"

int main(){
    PF::Mesh m;

    int a=-2;
    int b=-1;
    int rslt=((-2)&(-1))|(0&0)|(0&0)|(0&0)|(0&(-1))|(0&(-1))|(0&0)|(1&0)|((-3)&1);
    std::cout<<rslt<<std::endl;
    return 0;
}