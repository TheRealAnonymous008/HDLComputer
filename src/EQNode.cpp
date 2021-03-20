#include "EQNode.h"
#include "Nodes.h"
#include <math.h>

EQNode::EQNode(int n, int number): AbstractNode {"EQ", n, 1}
{
    //The following is a node that checks if the value in the first n nodes is equal to the specified i value.

    // It takes in n inputs. The bits of x we are checking against number. It returns 1 output, 0 if unequal and 1 if equal
    AbstractNode* nodes[n];

    for(int i = 0; i < n; i++){
        nodes[i] = new ANDNode();
    }

    for(int i = 0; i < n; i ++){
        if(i != 0){
            nodes[i-1]->getOutputPort(0)->connectTo(nodes[i]->getInputPort(0));
        }
        else{
            nodes[i]->getInputPort(0)->setRegister(*(new Signal(1)));
            nodes[i]->getInputPort(0)->receiveData();
        }

        if(number & (1 << i)){
            this->getInputPort(i)->connectTo(nodes[i]->getInputPort(1));
        }
        else{
            AbstractNode* notNode = new NOTNode();
            this->internalNodes.push_back(notNode);
            this->getInputPort(i)->connectTo(notNode->getInputPort(0));
            notNode->getOutputPort(0)->connectTo(nodes[i]->getInputPort(1));
        }

        this->internalNodes.push_back(nodes[i]);
    }
    nodes[n - 1]->getOutputPort(0)->connectTo(this->getOutputPort(0));
}

EQNode::~EQNode()
{
    //dtor
}

EQNode::EQNode(const EQNode& other)
{
    //copy ctor
}

EQNode& EQNode::operator=(const EQNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
