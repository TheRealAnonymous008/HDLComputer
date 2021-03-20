#include "PCNode.h"
#include "Nodes.h"

PCNode::PCNode(int w) : AbstractNode {"PC", w + 4, w}
{
    // Contains w + 4 input ports, the first w are the input nodes, the last three are the
    // w'th : increment bit
    // w + 1: store bit
    // w + 2: reset bit
    // w + 3: clock bit

    AbstractNode* storedData = new MUXNode(w);
    AbstractNode* incrementor = new ADDERNode(w);
    AbstractNode* resetter = new MUXNode(w);
    AbstractNode* internalRegister = new REGNode(w);

    // Configure stored data node. It is used when the store bit is off.
    for(int i = 0; i < w; i ++){
        internalRegister->getOutputPort(i)->connectTo(storedData->getInputPort(i));
        this->getInputPort(i)->connectTo(storedData->getInputPort(w + i));
    }
    this->getInputPort(w + 1)->connectTo(storedData->getInputPort(2 * w));

    // Next hook up the value of the storedData to the incrementor
    for(int i = 0; i < w; i ++){
        storedData->getOutputPort(i)->connectTo(incrementor->getInputPort(i));
    }
    this->getInputPort(w)->connectTo(incrementor->getInputPort(w));

    // Next configure reset. If it's on, the output should be 0
    for(int i = 0; i < w; i ++){
        incrementor->getOutputPort(i)->connectTo(resetter->getInputPort(i));
    }
    this->getInputPort(w + 2)->connectTo(resetter->getInputPort(2 * w));

    // Connect resetter to register and output
    for(int i = 0; i < w; i ++){
        resetter->getOutputPort(i)->connectTo(internalRegister->getInputPort(i));
        internalRegister->getOutputPort(i)->connectTo(this->getOutputPort(i));
    }
    //Connect the clock and store bit
    this->getInputPort(w + 1)->connectTo(internalRegister->getInputPort(w));
    this->getInputPort(w + 3)->connectTo(internalRegister->getInputPort(w + 1));

    this->internalNodes.push_back(storedData);
    this->internalNodes.push_back(incrementor);
    this->internalNodes.push_back(resetter);
    this->internalNodes.push_back(internalRegister);

}

PCNode::~PCNode()
{
    //dtor
}

PCNode::PCNode(const PCNode& other)
{
    //copy ctor
}

PCNode& PCNode::operator=(const PCNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
