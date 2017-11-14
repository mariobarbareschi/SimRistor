//===- FBLCRun.hpp --------------------------------------------------*- C++ -*-===//
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
/// \file FBLCRun.hpp
/// \author Mario Barbareschi
/// \brief This file describes the class for running a FBLC controller
//===----------------------------------------------------------------------===//

#ifndef FBLCRUN_HPP
#define FBLCRUN_HPP

#include "xbarrun.hpp"
#include "FBLCController.hpp"


namespace simristor{
    
class FBLCRun : public XBarRun {
private:
    FBLCController *controller;
public:
    
    FBLCRun(FBLCController *controller): controller(controller), XBarRun() {}
    FBLCRun* run(bool* input, bool* output);
    //~XBarRun();
    
}; /*end class FBLCRun*/
    
}/*end namespace simristor*/

#endif /*FBLCRUN_HPP*/ 