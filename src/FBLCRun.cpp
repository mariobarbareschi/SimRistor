//===- FBLCRun.cpp --------------------------------------------------*- C++ -*-===//
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
/// \file FBLCRun.cpp
/// \author Mario Barbareschi
/// \brief This file implements the class for running a FBLC controller
//===----------------------------------------------------------------------===//


#include "FBLCRun.hpp"

#include <thread>

simristor::FBLCRun* simristor::FBLCRun::run(bool* input, bool* output){
    XBarRun::run(input, output);
    controller->ina()->ri(input)->cfm()->evm()->evr()->inr()->so(output);
    return this;
}
