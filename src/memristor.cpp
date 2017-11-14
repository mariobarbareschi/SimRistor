//===- memristor.cpp --------------------------------------------------*- C++ -*-===//
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
/// \file memristor.cpp
/// \author Mario Barbareschi
/// \brief This file implements a switch-like memristor model
//===----------------------------------------------------------------------===//

#include "memristor.hpp"

long int simristor::Memristor::getSwitchingActivity() const{
    return this->switchingActivity;
}

const std::string simristor::Memristor::getTag() const{
    return this->tag;
}

simristor::Memristor* simristor::Memristor::setTag(const std::string tag){
    this->tag = tag;
    return this;
}
    
simristor::MemristorState simristor::Memristor::getState() const {
    return this->state;
}

bool simristor::Memristor::isHigh() const {
    return getState() == simristor::MemristorState::HIGH;
}


simristor::Memristor* simristor::Memristor::setState(simristor::MemristorState state){
    if(this->state != state){
        this->state = state;
        ++switchingActivity;
    }
    return this;
}


simristor::Memristor* simristor::Memristor::set(){
    return setState(simristor::MemristorState::HIGH);
}

simristor::Memristor* simristor::Memristor::reset(){
    return setState(simristor::MemristorState::LOW);
}

simristor::Memristor& simristor::Memristor::operator=(Memristor memristor) noexcept{
    setState(memristor.getState());
    return *this;
}