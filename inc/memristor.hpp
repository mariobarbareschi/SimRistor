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