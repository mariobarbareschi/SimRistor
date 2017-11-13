#include <iostream>

#include "memristor.hpp"
#include "xbar.hpp"
#include "xbarcontroller.hpp"
#include "xbarrun.hpp"

int main(int argc, char* argv[]){
    bool config[6][8] = {{1,1,1,1,1,1,0,0},
                         {0,1,1,0,0,1,0,1},
                         {1,0,0,1,0,1,0,1},
                         {0,1,0,0,1,0,0,1},
                         {0,0,1,0,1,0,0,1},
                         {0,0,0,0,0,0,1,1}};
    std::cout << "Creating XBar" << std::endl;
    simristor::XBar xbar = simristor::XBar("Test", 6, 8, (bool*)config);
    xbar.print(std::cout);
    std::cout << "Creating XBarController" << std::endl;
    simristor::XBarController xbarController = simristor::XBarController(&xbar, 0, 3, 4, 1);
    std::cout << "Calling initialization" << std::endl;
    xbarController.ina();
    bool xbarInput[] = {0,1,1,0,0,1};
    bool xbarOutput[1];
    std::cout << "Calling receive input" << std::endl;
    xbarController.ri(xbarInput);
    xbar.print(std::cout);
    std::cout << "Calling receive cfm" << std::endl;
    xbarController.cfm();
    xbar.print(std::cout);
    std::cout << "Calling receive evm" << std::endl;
    xbarController.evm();
    xbar.print(std::cout);
    std::cout << "Calling receive evr" << std::endl;
    xbarController.evr();
    xbar.print(std::cout);
    std::cout << "Calling receive inr" << std::endl;
    xbarController.inr();
    xbar.print(std::cout);
    std::cout << "Calling receive so" << std::endl;
    xbarController.so(xbarOutput);
    xbar.print(std::cout);
    std::cout << "Output: " << xbarOutput[0] << std::endl;
    xbarController.print(std::cout);
    xbar.printStat(std::cout);
    
    simristor::XBarRun xbarrun(&xbarController);
    
    bool xbarInput2[] = {1,0,1,0,0,1};
    xbarrun.run(xbarInput2, xbarOutput);
    std::cout << "Output: " << xbarOutput[0] << std::endl;
    xbarController.print(std::cout);
    
    xbar.printStat(std::cout);
    
    return 0;
}