//===- xbarcontroller.hpp --------------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2017  Mario Barbareschi (mario.barbareschi@unina.it)
// 
//  This file is part of simristor.
//
//  simristor is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  simristor is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with Clang-Chimera. If not, see <http://www.gnu.org/licenses/>.
//
//===----------------------------------------------------------------------===//
/// \file xbarcontroller.hpp
/// \author Mario Barbareschi
/// \brief This file describes the class of a the controller of a FBLC
//===----------------------------------------------------------------------===//

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