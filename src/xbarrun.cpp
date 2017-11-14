//===- xbarrun.cpp --------------------------------------------------*- C++ -*-===//
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
/// \file xbarrun.cpp
/// \author Mario Barbareschi
/// \brief This file implements the class for running a FBLS controller
//===----------------------------------------------------------------------===//


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
