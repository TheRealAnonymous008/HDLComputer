#include "NANDNode.h"
#include "AbstractNode.h"

NANDNode::NANDNode() : AbstractNode {"NAND", 2, 1}
{
    //ctor
}

NANDNode::NANDNode(int n) : AbstractNode {"MB_NAND", 2 * n, n}{
    // Multibit NAND
    for(int i = 0; i < n; i ++){
        this->internalNodes.push_back(new NANDNode());
        this->getInputPort(i)->connectTo(this->internalNodes[i]->getInputPort(0));
        this->getInputPort(i + n)->connectTo(this->internalNodes[i]->getInputPort(1));
        this->internalNodes[i]->getOutputPort(0)->connectTo(this->getOutputPort(i));
    }

}

NANDNode::~NANDNode()
{
    //dtor
}

NANDNode::NANDNode(const NANDNode& other)
{
    //copy ctor
}

NANDNode& NANDNode::operator=(const NANDNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void NANDNode::Process(){

    // We cannot use the default Process function from AbstractNode if NAND is 1-bit so we do a check first
    if(this->inputPorts > 2){
        AbstractNode::Process();
    }
    else{
        Port *p1 = this->getInputPort(0);
        Port *p2 = this->getInputPort(1);

        Signal output;
        if(p1->getActualValue().getValue() != 0 && p2->getActualValue().getValue() != 0)
            output = Signal(0);
        else
            output = Signal(1);

        Port* o1 = this->getOutputPort(0);
        o1->setRegister(output);
        o1->receiveData();
    }
}
