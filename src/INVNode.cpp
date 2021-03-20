#include "INVNode.h"
#include "Nodes.h"

INVNode::INVNode(int n) : AbstractNode {"MB_INVERTER", n, n}
{
    //An inverter to output the negative of a number following twos complements
    this->internalNodes.push_back(new NOTNode(n));
    this->internalNodes.push_back(new ADDERNode(n));

    for(int i = 0; i < n; i ++){
        this->getInputPort(i)->connectTo(this->internalNodes[0]->getInputPort(i)) ;      // connect everything to NOTNode
        this->internalNodes[0]->getOutputPort(i)->connectTo(this->internalNodes[i]->getInputPort(i));   // connect NOT to ADDER
        this->internalNodes[1]->getOutputPort(i)->connectTo(this->getOutputPort(i));        // connect to Output Port
    }

    // Set the other ADDEND as 1
    this->internalNodes[1]->getInputPort(n)->setRegister(*(new Signal(1)));
    this->internalNodes[1]->getInputPort(n)->receiveData();
}

INVNode::~INVNode()
{
    //dtor
}

INVNode::INVNode(const INVNode& other)
{
    //copy ctor
}

INVNode& INVNode::operator=(const INVNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
