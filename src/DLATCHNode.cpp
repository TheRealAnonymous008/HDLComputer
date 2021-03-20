#include "DLATCHNode.h"
#include "Nodes.h"

DLATCHNode::DLATCHNode() : AbstractNode {"DLATCH", 2, 1}
{
    // First bit is data, second is store
    this->internalNodes.push_back(new NOTNode());
    this->internalNodes.push_back(new ANDNode());
    this->internalNodes.push_back(new ANDNode());

    // Connect data bit
    this->getInputPort(0)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[2]->getInputPort(0));
    this->getInputPort(0)->connectTo(this->internalNodes[1]->getInputPort(0));

    // Connect store bit
    this->getInputPort(1)->connectTo(this->internalNodes[1]->getInputPort(1));
    this->getInputPort(1)->connectTo(this->internalNodes[2]->getInputPort(1));

    // Connect NOR gates together
    this->internalNodes.push_back(new NORNode());
    this->internalNodes.push_back(new NORNode());

    this->internalNodes[1]->getOutputPort(0)->connectTo(this->internalNodes[3]->getInputPort(0));
    this->internalNodes[2]->getOutputPort(0)->connectTo(this->internalNodes[4]->getInputPort(0));
    this->internalNodes[3]->getOutputPort(0)->connectTo(this->internalNodes[4]->getInputPort(1));
    this->internalNodes[4]->getOutputPort(0)->connectTo(this->internalNodes[3]->getInputPort(1));

    this->internalNodes[4]->getOutputPort(0)->connectTo(this->getOutputPort(0));

}

DLATCHNode::~DLATCHNode()
{
    //dtor
}

DLATCHNode::DLATCHNode(const DLATCHNode& other)
{
    //copy ctor
}

DLATCHNode& DLATCHNode::operator=(const DLATCHNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
