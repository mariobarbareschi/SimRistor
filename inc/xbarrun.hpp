//===- xbarrun.hpp --------------------------------------------------*- C++ -*-===//
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
/// \file xbarrun.hpp
/// \author Mario Barbareschi
/// \brief This file describes a virtual class for running a controller
//===----------------------------------------------------------------------===//

#ifndef XBARRUN_HPP
#define XBARRUN_HPP

#include "FBLCController.hpp"

namespace simristor{
    
class XBarRun {
protected:
    int cycles;
public:
    
    XBarRun(): cycles(0) {}
    //~XBarRun() = 0;
    XBarRun* run(bool* input, bool* output) {cycles++; return this;}
    
    int getCycles() const{return cycles;}
    
}; /*end class XBarRun*/
    
}/*end namespace simristor*/

#endif /*XBARRUN_HPP*/ 