#include "XORNode.h"
#include "Nodes.h"

XORNode::XORNode() : AbstractNode("XOR" , 2, 1)
{
    this->internalNodes.push_back(new NOTNode);
    this->internalNodes.push_back(new ANDNode);
    this->internalNodes.push_back(new NOTNode);
    this->internalNodes.push_back(new ANDNode);
    this->internalNodes.push_back(new ORNode);

    this->getInputPort(0)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[2]->getInputPort(0));

    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[1]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[1]->getInputPort(1));

    this->internalNodes[2]->getOutputPort(0)->connectTo(this->internalNodes[3]->getInputPort(0));
    this->getInputPort(0)->connectTo(this->internalNodes[3]->getInputPort(1));

    this->internalNodes[1]->getOutputPort(0)->connectTo(this->internalNodes[4]->getInputPort(0));
    this->internalNodes[3]->getOutputPort(0)->connectTo(this->internalNodes[4]->getInputPort(1));

    this->internalNodes[4]->getOutputPort(0)->connectTo(this->getOutputPort(0));

}

XORNode::XORNode(int n) : AbstractNode{"MB_XOR", 2 *n , n}{
    // Multibit XOR
    for(int i = 0; i < n; i ++){
        this->internalNodes.push_back(new XORNode());
        this->getInputPort(i)->connectTo(this->internalNodes[i]->getInputPort(0));
        this->getInputPort(i + n)->connectTo(this->internalNodes[i]->getInputPort(1));
        this->internalNodes[i]->getOutputPort(0)->connectTo(this->getOutputPort(i));
    }
}

XORNode::~XORNode()
{
    //dtor
}

XORNode::XORNode(const XORNode& other)
{
    //copy ctor
}

XORNode& XORNode::operator=(const XORNode& rhs)
{

    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
