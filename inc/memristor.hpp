//===- memristor.hpp --------------------------------------------------*- C++ -*-===//
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
/// \file memristor.hpp
/// \author Mario Barbareschi
/// \brief This file describes the class of a switch-like memristor model
//===----------------------------------------------------------------------===//

#ifndef MEMRISTOR_HPP
#define MEMRISTOR_HPP

#include <string> 

namespace simristor{

enum MemristorState {
    HIGH = 1,
    LOW = 0
};

class Memristor {
private:
    long int switchingActivity;
    std::string tag;
protected:
    MemristorState state;
public:
    long int getSwitchingActivity() const;
    const std::string getTag() const;
    Memristor* setTag(std::string);
    
    MemristorState getState() const;
    bool isHigh() const;
    Memristor* setState(MemristorState state);
    
    Memristor* set();
    Memristor* reset();
    
    Memristor(std::string tag) : switchingActivity(0), tag(tag), state(HIGH){}
    Memristor() : Memristor("") {}
    
    Memristor& operator=(Memristor memristor) noexcept;

    
}; /*end class Memristor*/

    
}/*end namespace simristor*/

#endif /*MEMRISTOR_HPP*/