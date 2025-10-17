#include "mesh/mesh.h"
#include <iostream>

int main()
{
    PF::Mesh m;
    if (!m.LoadFromFile("../models/test.obj"))
    {
        std::cerr << "[ERROR] load file faild\n";
        return 0;
    }


    for (const auto &adj : m.GetVV(1))
    {
        std::cout << adj << std::endl;
    }
    std::cout << "\n";

    // int a=-2;
    // int b=-1;
    // int rslt=((-2)&(-1))|(0&0)|(0&0)|(0&0)|(0&(-1))|(0&(-1))|(0&0)|(1&0)|((-3)&1);
    // std::cout<<rslt<<std::endl;
    return 0;
}