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
    pool = new Memristor*[columns*rows];
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            if(0 != configuration[i*columns + j])
                pool[i*columns + j] = new Memristor(std::to_string(i)+" "+std::to_string(j));
        }
    }
}

void simristor::XBar::print(std::ostream& outstream){
    outstream << "\033[1m" << name << "\033[0m: " << rows << "x" << columns << std::endl;
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++)
            outstream << "  |  ";
        outstream << std::endl;
        for(j = 0; j < columns; j++){
            if(pool[i*columns + j] != NULL)
                if(pool[i*columns + j]->isHigh())
                    outstream << "_\033[0;31m/\033[0m|__";
                else
                    outstream << "_\033[0;32m/\033[0m|__";
            else
                outstream << "__|__";
        }
        outstream << std::endl;
    }
    for(j = 0; j < columns; j++)
            outstream << "  |  ";
        outstream << std::endl;
}

void simristor::XBar::printStat(std::ostream& outstream){
    outstream << "Switching activity for \033[1m" << name << "\033[0m crossbar: " << rows << "x" << columns << std::endl;
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++)
            outstream << "  |  ";
        outstream << std::endl;
        for(j = 0; j < columns; j++){
            if(pool[i*columns + j] != NULL)
                    outstream << std::setfill('_') << std::setw(2) << pool[i*columns + j]->getSwitchingActivity() << "|__";
            else
                outstream << "__|__";
        }
        outstream << std::endl;
    }
    for(j = 0; j < columns; j++)
            outstream << "  |  ";
        outstream << std::endl;
}

simristor::Memristor* simristor::XBar::getMemristor(int i, int j) const{
    return pool[i*columns+j];
}

simristor::XBar::~XBar(){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            if(pool[i*columns + j] != NULL)
                delete pool[i*columns + j];
        }
    }
    delete pool;
}
