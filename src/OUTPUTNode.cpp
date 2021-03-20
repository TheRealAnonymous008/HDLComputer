#include "OUTPUTNode.h"
#include<iostream>

OUTPUTNode::OUTPUTNode(int n) : AbstractNode{"OUTPUT", n, 0}
{

}

OUTPUTNode::~OUTPUTNode()
{
    //dtor
}

OUTPUTNode::OUTPUTNode(const OUTPUTNode& other)
{
    //copy ctor
}

OUTPUTNode& OUTPUTNode::operator=(const OUTPUTNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

Signal* OUTPUTNode::getSignalAtPort(int number){
    if(number >= this->inputPorts)
        throw "Input Port does not exist for OUTPUT node";
    else{
        int val = this->inPorts[number]->getActualValue().getValue();
        return new Signal(val);
    }
}

void OUTPUTNode::displaySignalAtPort(int number){
    if(number >= this->inputPorts)
        throw "Input Port does not exist for OUTPUT node";
    else{
        this->inPorts[number]->displayVal();
    }

}


void OUTPUTNode::Process(){
    for(int i = 0; i < this->inputPorts; i++){
        this->inPorts[i]->receiveData();
    }
}

