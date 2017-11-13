#include "xbarrun.hpp"

#include <thread>

simristor::XBarRun* simristor::XBarRun::run(bool* input, bool* output){
    controller->ina()->ri(input)->cfm()->evm()->evr()->inr()->so(output);
    cycles++;
    return this;
}

int simristor::XBarRun::getCycles() const{
    return cycles;
}
