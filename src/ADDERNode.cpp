#include "ADDERNode.h"
#include "Nodes.h"

ADDERNode::ADDERNode() : AbstractNode {"ADDER", 3, 2}
{
    // Adopt the convention that the 0th digit is the right most digit and the n+1th digit is the carry bit.

    // Specification:
    // The first n input ports correspond to the bits of the first addend, the next n input ports correspond to that of the second. The last port is for
    // the carry bit.
    // The node outputs the n-bit signal once the operation is completed.

    // Add the first two bits
    this->internalNodes.push_back(new XORNode());
    this->internalNodes.push_back(new ANDNode());

    this->getInputPort(0)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[0]->getInputPort(1));
    this->getInputPort(0)->connectTo(this->internalNodes[1]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[1]->getInputPort(1));


    // Add the carry bits
    this->internalNodes.push_back(new XORNode());
    this->internalNodes.push_back(new ANDNode());

    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[2]->getInputPort(0));
    this->getInputPort(2)->connectTo(this->internalNodes[2]->getInputPort(1));

    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[3]->getInputPort(0));
    this->getInputPort(2)->connectTo(this->internalNodes[3]->getInputPort(1));


    // Resolve carry bit
    this->internalNodes.push_back(new ORNode());
    this->internalNodes[1]->getOutputPort(0)->connectTo(this->internalNodes[4]->getInputPort(0));
    this->internalNodes[3]->getOutputPort(0)->connectTo(this->internalNodes[4]->getInputPort(1));

    this->internalNodes[2]->getOutputPort(0)->connectTo(this->getOutputPort(0));
    this->internalNodes[4]->getOutputPort(0)->connectTo(this->getOutputPort(1));
}

ADDERNode::ADDERNode(int n) : AbstractNode {"MB_ADDER", 2 * n + 1, n + 1}{
    for(int i = 0; i < n; i ++){
        this->internalNodes.push_back(new ADDERNode());
    }

    // Connect carry bit to first adder
    this->getInputPort(2 * n)->connectTo(this->internalNodes[0]->getInputPort(2));

    for(int i = 0; i < n; i ++){
        this->getInputPort(i)->connectTo(this->internalNodes[i]->getInputPort(0));
        this->getInputPort(i + n)->connectTo(this->internalNodes[i]->getInputPort(1));

        // connect the carry to the next bit's adder
        if(i != n -1 )
            this->internalNodes[i]->getOutputPort(1)->connectTo(this->internalNodes[i + 1]->getInputPort(2));
        this->internalNodes[i]->getOutputPort(0)->connectTo(this->getOutputPort(i));
    }

    // Connect last adder to output carry bit
    this->internalNodes[n - 1]->getOutputPort(1)->connectTo(this->getOutputPort(n));
}


ADDERNode::~ADDERNode()
{
    //dtor
}

ADDERNode::ADDERNode(const ADDERNode& other)
{
    //copy ctor
}

ADDERNode& ADDERNode::operator=(const ADDERNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

