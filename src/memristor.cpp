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