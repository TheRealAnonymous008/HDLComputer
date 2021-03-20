#include "INPUTNode.h"

INPUTNode::INPUTNode(int n) : AbstractNode{"INPUT", 0, n}
{
    //ctor
}

INPUTNode::~INPUTNode()
{
    //dtor
}

INPUTNode::INPUTNode(const INPUTNode& other)
{
    //copy ctor
}

INPUTNode& INPUTNode::operator=(const INPUTNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void INPUTNode::setSignalAtPort(Signal *signal, int number){
    if(number >= this->outputPorts)
        throw "Output Port does not Exist for INPUT Node";
    else{
        this->outPorts[number]->setRegister(*signal);
        this->outPorts[number]->receiveData();
    }
}


void INPUTNode::Process(){
}
