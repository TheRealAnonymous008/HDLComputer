#include "ORNode.h"
#include "Nodes.h"

ORNode::ORNode() : AbstractNode{"OR" ,2, 1}
{
    this->internalNodes.push_back(new NOTNode());
    this->internalNodes.push_back(new NOTNode());
    this->internalNodes.push_back(new NANDNode());

    this->getInputPort(0)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[1]->getInputPort(0));
    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[2]->getInputPort(0));
    this->internalNodes[1]->getOutputPort(0)->connectTo(this->internalNodes[2]->getInputPort(1));
    this->internalNodes[2]->getOutputPort(0)->connectTo(this->getOutputPort(0));
}

ORNode::ORNode(int n) : AbstractNode {"MB_OR", 2 *n , n}{
    // Multibit OR
    for(int i = 0; i < n; i ++){
        this->internalNodes.push_back(new ORNode());
        this->getInputPort(i)->connectTo(this->internalNodes[i]->getInputPort(0));
        this->getInputPort(i + n)->connectTo(this->internalNodes[i]->getInputPort(1));
        this->internalNodes[i]->getOutputPort(0)->connectTo(this->getOutputPort(i));
    }
}

ORNode::~ORNode()
{
    //dtor
}

ORNode::ORNode(const ORNode& other)
{
    //copy ctor
}

ORNode& ORNode::operator=(const ORNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
