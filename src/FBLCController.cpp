//===- FBLCController.cpp --------------------------------------------------*- C++ -*-===//
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
/// \file FBLCController.cpp
/// \author Mario Barbareschi
/// \brief This file implements the class of a the controller of a FBLC
//===----------------------------------------------------------------------===//

#include <assert.h>     /* assert */
#include <algorithm>
#include "FBLCController.hpp"
#include "utils.h"

std::string codeColor(simristor::XBarBlock blk){
    std::string ret;
    switch(blk){
        case simristor::XBarBlock::IN:
            ret = "\033[0;43;30m";
            break;
        case simristor::XBarBlock::MINTERM:
            ret = "\033[0;44;30m";
            break;
        case simristor::XBarBlock::AND:
            ret = "\033[0;45;30m";
            break;
        case simristor::XBarBlock::OL:
            ret = "\033[0;46;30m";
            break;
        case simristor::XBarBlock::NONE:
        default:
            ret = "\033[0;47;30m";
            break;
    }
    return ret;
}


simristor::FBLCController::FBLCController(XBar* crossbar, int inputRow, int inputs, int minterms, int outputs){
    this->crossbar = crossbar;
    this->inputs = inputs;
    this->minterms = minterms;
    this->outputs = outputs;
    this->inputRow = inputRow;
    
    /*We need to popolate a vector which addresses input memristor columns*/
    MInput = new int[2*inputs];
    int j, literals = 0;
    /*Here we are looking for input memristor which resides into the inputRow row*/
    for(j = 0; j < crossbar->getColumns(); j++){
            Memristor* memptr = crossbar->getMemristor(inputRow,j);
            if(memptr != NULL){
                MInput[literals++] = j;
                DEBUG_PRINT("Found an input memristor at <"+std::to_string(inputRow)+", "+std::to_string(j)+">" << std::endl);
            }
    }
    assert(literals == 2*inputs && "Number of input memristor does not match the literals!");
    
    /*We need to popolate a vector which addresses minterms memristor rows*/
    MMinterm = new int[minterms];
    int i, mint = 0;
    /*Here we need to identify the memristor which represents minterms, hence they have at least one memristor in the corresponding row which is an input memristor*/
    for(i = 0; i < crossbar->getRows(); i++){
        if(i != inputRow){
                j = 0;
                while( j < 2*inputs && crossbar->getMemristor(i, MInput[j]) == NULL) j++;
                if(j < 2*inputs){
                    MMinterm[mint++] = i;
                    DEBUG_PRINT("Found a minterm memristor at "+std::to_string(i)+" row" << std::endl);
                }
        }
    }
    assert(minterms == mint && "Number of minterms does not match xbar structure!");
    
    /*We need to populate a vector which addresses output memristor column*/
    MOutput = new int[outputs];
    int outp = 0;
    for(j = 0; j < crossbar->getColumns(); j++){
        //If the columns is not an input one
        if(std::find(MInput, MInput+2*inputs, j) == MInput+2*inputs){
            i = 0;
            while(i < minterms && crossbar->getMemristor(MMinterm[i], j) == NULL) i++;
            //If we meet a memristor along the j-th column in correspondance to the minterms row, we got an output memristor
            if(i != minterms){
                MOutput[outp++] = j;
                DEBUG_PRINT("Found an output memristor at "+std::to_string(j)+" column" << std::endl);
            }
        }
            
    }
    assert(outp == outputs && "Number of output does not match xbar structure!");
    
    /*We need to populate a vector which addresses output memristor (direct form) row*/
    /*We can exploit the fact that output direct memristor are alone along a single column*/
    MOutputDirectRow = new int[outputs];
    MOutputDirectCol = new int[outputs];
    outp = 0;
    for(j = 0; j < crossbar->getColumns(); j++){
        int countMemristor = 0;
        i = 0;
        int rowPosition;
        while(countMemristor <= 1 && i < crossbar->getRows() ){
            if(crossbar->getMemristor(i, j) != NULL){
                countMemristor++;
                rowPosition = i;
            }
            i++;
        }
        if(1 == countMemristor){
            MOutputDirectRow[outp] = rowPosition;
            MOutputDirectCol[outp] = j;
            DEBUG_PRINT("Found a direct output memristor at <"+std::to_string(rowPosition)+", "+std::to_string(j)+">" << std::endl);
            outp++;
        }
    }
    assert(outp == outputs && "Number of output does not match xbar structure!");

    xbarStructure = new simristor::XBarBlock[crossbar->getRows()*crossbar->getColumns()];
    for(i = 0; i < crossbar->getRows(); i++)
        for(j = 0; j < crossbar->getColumns(); j++)
            xbarStructure[i*crossbar->getColumns()+j] = simristor::XBarBlock::NONE;
    
    for(j = 0; j < 2*inputs; j++)
        xbarStructure[inputRow*crossbar->getColumns() + MInput[j]] = simristor::XBarBlock::IN;
    
    for(i = 0; i < minterms; i++){
            for(j = 0; j < 2*inputs; j++){
                xbarStructure[MMinterm[i]*crossbar->getColumns()+MInput[j]] = simristor::XBarBlock::MINTERM;
            }
        
    }
    
    for(i = 0; i < minterms; i++){
            for(j = 0; j < outputs; j++){
                xbarStructure[MMinterm[i]*crossbar->getColumns()+MOutput[j]] = simristor::XBarBlock::AND;
            }
    }
    
    for(i = 0; i < outputs; i++){
            for(j = 0; j < outputs; j++){
                xbarStructure[MOutputDirectRow[i]*crossbar->getColumns()+MOutput[j]] = simristor::XBarBlock::OL;
                xbarStructure[MOutputDirectRow[i]*crossbar->getColumns()+MOutputDirectCol[i]] = simristor::XBarBlock::OL;
            }
    }
    //TODO completare xbarStructure per INV block
}


simristor::FBLCController* simristor::FBLCController::ina(){
    DEBUG(clock_t begin = clock());
    int i, j;
    for(i = 0; i < crossbar->getRows(); i++){
        for(j = 0; j < crossbar->getColumns(); j++){
            Memristor* memptr = crossbar->getMemristor(i,j);
            if(memptr != NULL)
                memptr->set();
        }
    }
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("INA successfully completed in "<< elapsed_secs << " ms" <<std::endl);

    return this;
}

simristor::FBLCController* simristor::FBLCController::ri(bool* inputValues){
    DEBUG(clock_t begin = clock());
    int j;
    for(j = 0; j < 2*inputs; j++)
                *inputValues++ ? crossbar->getMemristor(inputRow, MInput[j])->set() : crossbar->getMemristor(inputRow, MInput[j])->reset();
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("RI successfully completed in "<< elapsed_secs << " ms" <<std::endl);
    
    return this;
}

simristor::FBLCController* simristor::FBLCController::cfm(){
    DEBUG(clock_t begin = clock());
    int j, i;
    for(j = 0; j < 2*inputs; j++){ /*Looking for memristors belonging to the same column of a input memristor*/
        for(i = 0; i < crossbar->getRows(); i++){
            if(i != inputRow){
                Memristor* memptr = crossbar->getMemristor(i,j);
                if(memptr != NULL){
                    *memptr = *crossbar->getMemristor(inputRow, MInput[j]);
                }
            }
        }
    }
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("CFM successfully completed in "<< elapsed_secs << " ms" <<std::endl);
    return this;
}

simristor::FBLCController* simristor::FBLCController::evm(){
    DEBUG(clock_t begin = clock());
    int j, i;
    for(i = 0; i < minterms; i++){
        int colIndex = 0;
        /*We evaluate the value of each minterm
        To to this, we retrieve values of minterm's memristors (memristors that are under a input memristor) and if we got at least one that is low its value is high (NAND)*/

        while(colIndex < 2*inputs &&
              (crossbar->getMemristor(MMinterm[i], MInput[colIndex]) == NULL || (
                crossbar->getMemristor(MMinterm[i], MInput[colIndex]) != NULL && crossbar->getMemristor(MMinterm[i], MInput[colIndex])->isHigh()))
             ) colIndex++;
        /*If the while terminates without find a low value, the corresponding minterm must set to 0
        Lets now find the corresponding minterms onto output columns*/
        if(colIndex == 2*inputs){
            for(j = 0; j < crossbar->getColumns(); j++){
            /*If there is a memristor at <i,j> and j is not an input column*/
            if(crossbar->getMemristor(MMinterm[i], j) != NULL && std::find(MInput, MInput+2*inputs, j) == MInput+2*inputs){
                crossbar->getMemristor(MMinterm[i], j)->reset();
            }
        }
        }
    }/*For all outputs*/
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("EVM successfully completed in "<< elapsed_secs << " ms" <<std::endl);
    return this;
}

simristor::FBLCController* simristor::FBLCController::evr(){
    DEBUG(clock_t begin = clock());
    int j, i;
    for(i = 0; i < outputs; i++){
        j = 0;
        while(j < minterms && (crossbar->getMemristor(MMinterm[j], MOutput[i]) == NULL || (crossbar->getMemristor(MMinterm[j], MOutput[i]) != NULL && crossbar->getMemristor(MMinterm[j], MOutput[i])->isHigh()))) j++;
        if(j != minterms){
            //We need to find the row of the output memristor
            int rowIndex;
            for(rowIndex = 0; rowIndex < crossbar->getRows(); rowIndex++){
                if((std::find(MMinterm, MMinterm+minterms, rowIndex) == MMinterm+minterms) && 
                    crossbar->getMemristor(rowIndex, MOutput[i]) != NULL )
                    crossbar->getMemristor(rowIndex, MOutput[i])->reset();
            }
        }
              
    }/*For all minterms*/
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("EVR successfully completed in "<< elapsed_secs << " ms" <<std::endl);
    return this;
}

simristor::FBLCController* simristor::FBLCController::inr(){
    DEBUG(clock_t begin = clock());
    int j, i;
    for(i = 0; i < outputs; i++){
        //Lets iterate along columns
        j = 0;
        while(j < crossbar->getColumns() && (j == MOutputDirectCol[i] || crossbar->getMemristor(MOutputDirectRow[i], j) == NULL)) j++;
        if(j < crossbar->getColumns())
            crossbar->getMemristor(MOutputDirectRow[i], j)->isHigh() ? crossbar->getMemristor(MOutputDirectRow[i], MOutputDirectCol[i])->reset() : crossbar->getMemristor(MOutputDirectRow[i], MOutputDirectCol[i])->set();
    }
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("INR successfully completed in "<< elapsed_secs << " ms" <<std::endl);
    return this;
}

simristor::FBLCController* simristor::FBLCController::so(bool* outputValues){
    DEBUG(clock_t begin = clock());
    int i;
    for(i = 0; i < outputs; i++)
                outputValues[i] = crossbar->getMemristor(MOutputDirectRow[i], MOutputDirectCol[i])->isHigh();
    DEBUG(double elapsed_secs = double(clock() - begin) / (CLOCKS_PER_SEC/1000));
    DEBUG_PRINT("SO successfully completed in "<< elapsed_secs << " ms" <<std::endl);
    return this;
}

const simristor::XBar* simristor::FBLCController::getXBar() const{
    return crossbar;
}


void simristor::FBLCController::print(std::ostream& outstream){
   outstream << "\033[1m" << crossbar->getName() << "\033[0m: " << crossbar->getRows() << "x" << crossbar->getColumns() << std::endl;
    int i, j;
    for(i = 0; i < crossbar->getRows(); i++){
        for(j = 0; j < crossbar->getColumns(); j++)
            outstream << codeColor(xbarStructure[i*crossbar->getColumns()+j] ) << "  |  ";
        outstream << "\033[0m" <<std::endl;
        for(j = 0; j < crossbar->getColumns(); j++){
            if(crossbar->getMemristor(i,j) != NULL)
                if(crossbar->getMemristor(i,j)->isHigh())
                    outstream << codeColor(xbarStructure[i*crossbar->getColumns()+j] ) << "_\033[0;31m/" << codeColor(xbarStructure[i*crossbar->getColumns()+j] ) <<"|__";
                else
                    outstream << codeColor(xbarStructure[i*crossbar->getColumns()+j] )  << "_\033[0;32m/" << codeColor(xbarStructure[i*crossbar->getColumns()+j] ) <<"|__";
            else
                outstream << codeColor(xbarStructure[i*crossbar->getColumns()+j] ) << "__|__";
        }
        outstream << "\033[0m" << std::endl <<  "\033[0m" ;
    }
    for(j = 0; j < crossbar->getColumns(); j++)
            outstream << codeColor(simristor::XBarBlock::NONE) << "  |  ";
        outstream << "\033[0m" << std::endl;
}

simristor::FBLCController::~FBLCController(){
    delete MInput;
    delete MMinterm;
    delete MOutput;
    delete MOutputDirectRow;
    delete MOutputDirectCol;
    delete xbarStructure;
}
