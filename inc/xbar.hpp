//===- xbar.hpp --------------------------------------------------*- C++ -*-===//
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
/// \file xbar.hpp
/// \author Mario Barbareschi
/// \brief This file describes a class which handles a memristor crossbar
//===----------------------------------------------------------------------===//

#ifndef XBAR_HPP
#define XBAR_HPP

#include <string>
#include <ostream>
#include <vector>
#include <memory>
#include "memristor.hpp" 

namespace simristor{

class XBar{
private:
    std::vector<std::shared_ptr<Memristor>> pool;
    std::string name;
protected:
    int rows;
    int columns;
    XBar* setRows(int);
    XBar* setColumns(int);
public:
    const std::string getName() const;
    int getRows() const;
    int getColumns() const;
    
    XBar* setName(const std::string);
    
    std::shared_ptr<Memristor> getMemristor(int i, int j) const;
    
    void print(std::ostream&);
    void printStat(std::ostream&);

    int getTotalSwitches() const;
    
    XBar(std::string name, int rows, int columns, bool* configuration);
    XBar(int rows, int columns, bool* configuration) : XBar("", rows, columns, configuration) {}
    XBar();
    ~XBar();
}; /*end class XBar*/

    
}/*end namespace simristor*/

#endif /*XBAR_HPP*/