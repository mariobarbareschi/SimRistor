#include <iostream>
#include <fstream>

#include "memristor.hpp"
#include "xbar.hpp"
#include "FBLCController.hpp"
#include "FBLCRun.hpp"

int main(int argc, char* argv[]){
    /*bool config[7][10] = {{1,1,1,1,1,1,0,0,0,0},
                         {0,1,1,0,0,1,0,0,1,0},
                         {1,0,0,1,0,1,0,0,0,1},
                         {0,1,0,0,1,0,0,0,0,1},
                         {0,0,1,0,1,0,0,0,1,0},
                         {0,0,0,0,0,0,1,0,1,0},
                         {0,0,0,0,0,0,0,1,0,1}};
    std::cout << "Creating XBar" << std::endl;
    simristor::XBar xbar = simristor::XBar("Test", 7, 10, (bool*)config);
    xbar.print(std::cout);
    std::cout << "Creating XBarController" << std::endl;
    simristor::FBLCController xbarController = simristor::FBLCController(&xbar, 0, 3, 4, 2);
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
    
    simristor::FBLCRun fblcrun(&xbarController);
    
    bool xbarInput2[] = {1,0,1,0,0,1};
    fblcrun.run(xbarInput2, xbarOutput);
    std::cout << "Output: " << xbarOutput[0] << std::endl;
    xbarController.print(std::cout);
    
    xbar.printStat(std::cout);
    */
    
    std::ofstream outfile;
    outfile.open("dump_xor.txt", std::ios::out | std::ios::trunc );
    
    bool config[25][48] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
					{0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
					{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
					{0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
					{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1}};
    
    std::cout << "Creating XBar" << std::endl;
    simristor::XBar xbar("Test", 25, 48, (bool*)config);
    std::cout << "Creating XBarController" << std::endl;
    simristor::FBLCController xbarController = simristor::FBLCController(&xbar, 0);
    //std::cout << "Creating XBarRun" << std::endl;
    //simristor::FBLCRun fblcrun(&xbarController);
    
    bool xbarInput[32];
    bool xbarOutput[8];
    
    bool secretKey[8] = {1, 0, 0, 1, 0, 1, 1, 0};
    
    for(int k = 0; k < 256; k++){
        std::bitset<8> bits(k);
        for(int b = 0; b < 8; b++){
            xbarInput[4*b] = 1== secretKey[b];
            xbarInput[4*b+1] = 0 == secretKey[b];
            xbarInput[4*b+2] = bits[b];
            xbarInput[4*b+3] = ~bits[b];
        }
        std::cout << "Input: ";
        for(int i = 0; i < 32; i++)
            std::cout << xbarInput[i] << ", ";
        std::cout << std::endl;
        //fblcrun.run(xbarInput, xbarOutput);
            
        xbarController.ina();
        outfile << k << ", " << xbar.getTotalSwitches() << ", ";
        xbarController.ri(xbarInput);
        outfile << xbar.getTotalSwitches() << ", ";
        xbarController.cfm();
        outfile << xbar.getTotalSwitches() << ", ";
        xbarController.evm();
        outfile << xbar.getTotalSwitches() << ", ";
        xbarController.evr();
        outfile << xbar.getTotalSwitches() << ", ";
        xbarController.inr();
        outfile << xbar.getTotalSwitches() << ", ";
        xbarController.so(xbarOutput);
        outfile << xbar.getTotalSwitches() << std::endl;

        std::cout << "Output: ";
        for(int i = 0; i < 8; i++)
            std::cout << xbarOutput[i] << ", ";
        std::cout << std::endl;
    }
    
    
    
    return 0;
}