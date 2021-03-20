#include "ANDNode.h"
#include "Nodes.h"

ANDNode::ANDNode() : AbstractNode {"AND", 2, 1}
{
    this->internalNodes.push_back(new NANDNode());
    this->internalNodes.push_back(new NOTNode());

    this->getInputPort(0)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[0]->getInputPort(1));
    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[1]->getInputPort(0));
    this->internalNodes[1]->getOutputPort(0)->connectTo(this->getOutputPort(0));
}

ANDNode::ANDNode(int n) : AbstractNode {"MB_AND", 2 * n, n}{
    // Multibit AND
    for(int i = 0; i < n; i ++){
        this->internalNodes.push_back(new ANDNode());
        this->getInputPort(i)->connectTo(this->internalNodes[i]->getInputPort(0));
        this->getInputPort(i + n)->connectTo(this->internalNodes[i]->getInputPort(1));
        this->internalNodes[i]->getOutputPort(0)->connectTo(this->getOutputPort(i));
    }
}

ANDNode::~ANDNode()
{
    //dtor
}

ANDNode::ANDNode(const ANDNode& other)
{
    //copy ctor
}

ANDNode& ANDNode::operator=(const ANDNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
