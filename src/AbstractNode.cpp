#include "AbstractNode.h"
#include<iostream>
#include<random>

AbstractNode::AbstractNode()
{
    //ctor
}

AbstractNode::AbstractNode(int inputs, int outputs){
    this->inputPorts = inputs;
    this->outputPorts = outputs;

    for(int i = 0; i < inputs; i++){
        this->inPorts.push_back(new Port());
    }

    for(int i = 0; i < outputs; i++){
        this->outPorts.push_back(new Port());
    }
}

AbstractNode::AbstractNode(std::string nodeName, int inputs, int outputs){
    this->inputPorts = inputs;
    this->outputPorts = outputs;

    for(int i = 0; i < inputs; i++){
        this->inPorts.push_back(new Port());
    }

    for(int i = 0; i < outputs; i++){
        this->outPorts.push_back(new Port());
    }

    this->id = nodeName + (std::string)"-" + this->generateId();
}

AbstractNode::~AbstractNode()
{
    //dtor
}

AbstractNode::AbstractNode(const AbstractNode& other)
{
    //copy ctor
}

AbstractNode& AbstractNode::operator=(const AbstractNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

std::string AbstractNode::getId(){
    return this->id;
}

Port* AbstractNode::getInputPort(int number){
    if(number >= this->inputPorts){
        std::cout<<"Input Port "<<number<<" Not Found for "<<this->id<<"\n";
        throw "Error";
    }
    return this->inPorts[number];
}

Port* AbstractNode::getOutputPort(int number){
    if(number >= this->outputPorts){
        std::cout<<"Output Port "<<number<<" Not Found for "<<this->id<<"\n";
        throw "Error";
    }
    return this->outPorts[number];
}

void AbstractNode::performOperation(){
    for(auto it = this->inPorts.begin(); it!=this->inPorts.end(); it++){
        (*it)->receiveData();
    }

    this->Process();

    for(auto it = this->outPorts.begin(); it!=this->outPorts.end(); it++){
        (*it)->sendData();
    }
}


std::string AbstractNode::generateId(){
    const std::string charList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int chars = charList.size();
    int idSize = 8;
    char id[idSize + 1];

    for(int i = 0; i < idSize; i ++){
        id[i] = charList[rand() %chars];
    }
    id[idSize] = '\0';

    return id;
}
