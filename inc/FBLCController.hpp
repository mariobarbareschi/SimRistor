//===- FBLCcontroller.hpp --------------------------------------------------*- C++ -*-===//
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
/// \file FBLCcontroller.hpp
/// \author Mario Barbareschi
/// \brief This file describes the class of a the controller of a FBLC
//===----------------------------------------------------------------------===//

#ifndef FBLCCONTROLLER_HPP
#define FBLCCONTROLLER_HPP

#include <ostream>
#include <memory>
#include <unordered_map>

#include "xbar.hpp"

namespace simristor{
    
enum XBarBlock{
    NONE = 0,
    IN = 1,
    MINTERM = 2,
    AND = 3,
    OL = 4
};

class FBLCController {
private:
    XBar *crossbar;
    std::vector<XBarBlock> xbarStructure;
protected:
    int inputs;
    int minterms;
    int outputs;
    
    std::unordered_map<int, std::shared_ptr<Memristor>> inputMemristor;
    std::unordered_map<std::shared_ptr<Memristor>,std::vector<std::shared_ptr<Memristor>>> inputColumns;
    std::unordered_map<int,std::vector<std::shared_ptr<Memristor>>> mintermRows;
    std::unordered_map<int,std::vector<std::shared_ptr<Memristor>>> mintermOutputRows;
    std::unordered_map<int,std::vector<std::shared_ptr<Memristor>>> outputColumns;
    std::unordered_map<int,std::shared_ptr<Memristor>> outputNegMemristorColumn;
    std::unordered_map<int,std::shared_ptr<Memristor>> outputNegMemristorRow;
    std::unordered_map<int,std::shared_ptr<Memristor>> outputMemristorRow;

    int inputRow;
    
public:
    
    FBLCController(XBar* crossbar, int inputRow, int inputs, int minterms, int outputs);
    FBLCController(XBar* crossbar, int inputRow) : FBLCController(crossbar, inputRow, 0, 0, 0) {}
    ~FBLCController();
    
    const XBar* getXBar() const;
    
    void print(std::ostream&);
    
    FBLCController* ina();
    FBLCController* ri(bool* inputValues);
    FBLCController* cfm();
    FBLCController* evm();
    FBLCController* evr();
    FBLCController* inr();
    FBLCController* so(bool* outputValues);

    
}; /*end class FBLCController*/

    
}/*end namespace simristor*/

#endif /*FBLCCONTROLLER_HPP*/