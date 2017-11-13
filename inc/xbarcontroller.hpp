#ifndef XBARCONTROLLER_HPP
#define XBARCONTROLLER_HPP

#include <ostream>

#include "xbar.hpp"

namespace simristor{
    
enum XBarBlock{
    NONE = 0,
    IN = 1,
    MINTERM = 2,
    AND = 3,
    OL = 4
};

class XBarController {
private:
    XBar *crossbar;
    XBarBlock *xbarStructure;
protected:
    int inputs;
    int minterms;
    int outputs;
    
    int* MInput, *MMinterm, *MOutput, *MOutputDirectRow, *MOutputDirectCol;
    
    int inputRow;
    
public:
    
    XBarController(XBar* crossbar, int inputRow, int inputs, int minterms, int outputs);
    ~XBarController();
    
    const XBar* getXBar() const;
    
    void print(std::ostream&);
    
    XBarController* ina();
    XBarController* ri(bool* inputValues);
    XBarController* cfm();
    XBarController* evm();
    XBarController* evr();
    XBarController* inr();
    XBarController* so(bool* outputValues);

    
}; /*end class Memristor*/

    
}/*end namespace simristor*/

#endif /*XBARCONTROLLER_HPP*/