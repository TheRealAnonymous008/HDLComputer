#include "DFFNode.h"
#include "Nodes.h"

DFFNode::DFFNode() : AbstractNode {"DFF", 2, 1}
{
    this->internalNodes.push_back(new NOTNode());
    this->internalNodes.push_back(new DLATCHNode());
    this->internalNodes.push_back(new DLATCHNode());

    // The first input is for the data, the second is for clock
    this->getInputPort(1)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->getInputPort(0)->connectTo(this->internalNodes[1]->getInputPort(0));
    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[1]->getInputPort(1));

    this->internalNodes[1]->getOutputPort(0)->connectTo(this->internalNodes[2]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[2]->getInputPort(1));

    this->internalNodes[2]->getOutputPort(0)->connectTo(this->getOutputPort(0));

}

DFFNode::~DFFNode()
{
    //dtor
}

DFFNode::DFFNode(const DFFNode& other)
{
    //copy ctor
}

DFFNode& DFFNode::operator=(const DFFNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
