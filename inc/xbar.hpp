#ifndef XBAR_HPP
#define XBAR_HPP

#include <string>
#include <ostream>
#include "memristor.hpp" 

namespace simristor{

class XBar{
private:
    Memristor** pool;
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
    
    Memristor* getMemristor(int i, int j) const;
    
    void print(std::ostream&);
    void printStat(std::ostream&);

    
    XBar(std::string name, int rows, int columns, bool* configuration);
    XBar(int rows, int columns, bool* configuration) : XBar("", rows, columns, configuration) {}
    XBar();
    ~XBar();
};

    
}/*end namespace simristor*/

#endif /*XBAR_HPP*/