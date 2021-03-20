#include "Signal.h"

Signal::Signal(int _value)
{
    this->value = _value;
}

Signal::Signal(){

}

Signal::~Signal()
{
    //dtor
}

Signal::Signal(const Signal& other)
{
    //copy ctor
}

Signal& Signal::operator=(const Signal& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    this->value = rhs.value;
    return *this;
}

Signal::Signal(Signal&& other){
    this->value = other.value;
    other.value = 0;
}


int Signal::getValue(){
    return this->value;
}

