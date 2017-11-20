//===- xbar.cpp --------------------------------------------------*- C++ -*-===//
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
/// \file xbar.cpp
/// \author Mario Barbareschi
/// \brief This file implements the memristor crossbar
//===----------------------------------------------------------------------===//

#include <assert.h>     /* assert */
#include <iomanip>
#include "xbar.hpp"

const std::string simristor::XBar::getName() const{
    return this->name;
}

int simristor::XBar::getRows() const{
    return this->rows;
}

int simristor::XBar::getColumns() const{
    return this->columns;
}

simristor::XBar* simristor::XBar::setName(const std::string name){
    this->name = name;
    return this;
}

simristor::XBar* simristor::XBar::setRows(int rows){
    assert(rows > 3 && "XBar should have at least 3 rows");
    this->rows = rows;
    return this;
}

simristor::XBar* simristor::XBar::setColumns(int columns){
    assert(columns > 3 && "XBar should have at least 3 columns");
    this->columns = columns;
    return this;
}


simristor::XBar::XBar(std::string name, int rows, int columns, bool* configuration){
    int i, j;
    this->setName(name)->setRows(rows)->setColumns(columns);
    pool.reserve(columns*rows);
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            if(0 != configuration[i*columns + j])
                pool.push_back(std::shared_ptr<simristor::Memristor>(new simristor::Memristor(std::to_string(i)+" "+std::to_string(j))));
            else
                pool.push_back(nullptr);
        }
    }
}

void simristor::XBar::print(std::ostream& outstream){
    outstream << "\033[1m" << name << "\033[0m: " << rows << "x" << columns << std::endl;
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++)
            outstream << "    |";
        outstream << std::endl;
        for(j = 0; j < columns; j++){
            if(nullptr != pool[i*columns + j]){
                if(pool[i*columns + j]->isHigh())
                    outstream << "___\033[0;31m/\033[0m|";
                else
                    outstream << "___\033[0;32m/\033[0m|";
            }else{
                outstream << "____|";
            }
        }
        outstream << "__" << std::endl;
    }
    for(j = 0; j < columns; j++)
            outstream << "    |";
        outstream << std::endl;
}

void simristor::XBar::printStat(std::ostream& outstream){
    outstream << "Switching activity for \033[1m" << name << "\033[0m crossbar: " << rows << "x" << columns << std::endl;
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++)
            outstream << "    |";
        outstream << std::endl;
        for(j = 0; j < columns; j++){
            if(pool[i*columns + j])
                    outstream << std::setfill('_') << std::setw(4) << pool[i*columns + j]->getSwitchingActivity() << "|";
            else
                outstream << "____|";
        }
        outstream << "__" << std::endl;
    }
    for(j = 0; j < columns; j++)
            outstream << "    |";
        outstream << std::endl;
}

std::shared_ptr<simristor::Memristor> simristor::XBar::getMemristor(int i, int j) const{
    return pool[i*columns+j];
}

simristor::XBar::~XBar(){
   pool.clear();
}
