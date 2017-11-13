#ifndef XBARRUN_HPP
#define XBARRUN_HPP

#include "xbarcontroller.hpp"


namespace simristor{
    
class XBarRun {
private:
    XBarController *controller;
protected:
    int cycles;
public:
    
    XBarRun(XBarController *controller): controller(controller), cycles(0) {}
    XBarRun* run(bool* input, bool* output);
    //~XBarRun();
    
    int getCycles() const;
    
}; /*end class Memristor*/
    
}/*end namespace simristor*/

#endif /*XBARRUN_HPP*/ 