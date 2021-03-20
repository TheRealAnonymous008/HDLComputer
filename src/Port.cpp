#include "Port.h"
    #include<iostream>


Port::Port(){
    this->internalRegister = Signal(0);
    this->actualValue = Signal(0);
}

void Port::connectTo(Port* port){

    this->outNeighbor.push_back(port);
    port->connectFrom(this);

}

void Port::connectFrom(Port* port){
    this->inNeighbor.push_back(port);
}

void Port::setRegister(Signal &s){
    this->internalRegister = s;
}

void Port::sendData()
{
    for(int i = 0; i < (int) outNeighbor.size(); i++){
        outNeighbor[i]->setRegister(this->actualValue);
    }
}

void Port::receiveData(){
    this->actualValue = this->internalRegister;
}


void Port::displayVal(){
    std::cout<<this->actualValue.getValue();
}

Signal Port::getActualValue(){
    return Signal(this->actualValue.getValue());
}

void Port::displayReg(){
    std::cout<<"REG: "<<this->internalRegister.getValue();
}
