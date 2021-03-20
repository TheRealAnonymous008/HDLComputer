#include "MUXNode.h"
#include "Nodes.h"
#include <math.h>

MUXNode::MUXNode() : AbstractNode("MUX", 3, 1)
{
    this->internalNodes.push_back(new ANDNode);
    this->internalNodes.push_back(new NOTNode);
    this->internalNodes.push_back(new ANDNode);
    this->internalNodes.push_back(new ORNode);

    this->getInputPort(2)->connectTo(this->internalNodes[0]->getInputPort(0));
    this->getInputPort(1)->connectTo(this->internalNodes[0]->getInputPort(1));

    this->getInputPort(2)->connectTo(this->internalNodes[1]->getInputPort(0));
    this->internalNodes[1]->getOutputPort(0)->connectTo(this->internalNodes[2]->getInputPort(0));
    this->getInputPort(0)->connectTo(this->internalNodes[2]->getInputPort(1));

    this->internalNodes[0]->getOutputPort(0)->connectTo(this->internalNodes[3]->getInputPort(0));
    this->internalNodes[2]->getOutputPort(0)->connectTo(this->internalNodes[3]->getInputPort(1));

    this->internalNodes[3]->getOutputPort(0)->connectTo(this->getOutputPort(0));

}

MUXNode::MUXNode(int n) : AbstractNode("MB_MUX", 2 * n + 1, n){
    // This one performs bitwise MUX.
    for(int i = 0; i < n; i ++){
        this->internalNodes.push_back(new MUXNode());
        this->getInputPort(i)->connectTo(this->internalNodes[i]->getInputPort(0));
        this->getInputPort(i + n)->connectTo(this->internalNodes[i]->getInputPort(1));
        this->internalNodes[i]->getOutputPort(0)->connectTo(this->getOutputPort(i));
        this->getInputPort(2*n)->connectTo(this->internalNodes[i]->getInputPort(2));
    }
}

MUXNode::MUXNode(int n, int k) : AbstractNode("MW_MB_MUX", k * n + (int) ceil(log2(k)) , n){
    // Multi bit and multi way MUX. Let n be the number of bits, and k be the number of choices
    // TO-DO Wire up the k-way n-bit MUXNode
    int digits = (int) ceil(log2(k));
    AbstractNode* arr[k];

    for(int i = 0; i < k; i ++){
        arr[i] = new MUXNode(n);
    }


    for(int i = 0; i < k; i++){
        for(int j = 0; j < n; j ++){
            // Our start is at i * n + j.
            // Wire up all corresponding inputs to mux node
            this->getInputPort(n * i + j)->connectTo(arr[i]->getInputPort(n + j));
        }

        // Connect current mux to previous mux
        if(i != 0){
            for(int d = 0 ; d< n; d++){
                arr[i - 1]->getOutputPort(d)->connectTo(arr[i]->getInputPort(d));
            }
        }


        // Wire up digit checker programmaticaly. it STRICTLY consists of AND nodes applied in sequence
        AbstractNode* digitChecker = new EQNode(digits, i);

        // Configure digit Checker
        for(int d = 0; d < digits; d++){
            this->getInputPort(k * n + d)->connectTo(digitChecker->getInputPort(d));
        }
        this->internalNodes.push_back(digitChecker);

        digitChecker->getOutputPort(0)->connectTo(arr[i]->getInputPort(2 * n));

        this->internalNodes.push_back(arr[i]);

    }

    // The output of the last mux node is our answer
    for(int i = 0; i < n; i++){
        arr[k - 1]->getOutputPort(i)->connectTo(this->getOutputPort(i));
    }

}

MUXNode::~MUXNode()
{
    //dtor
}

MUXNode::MUXNode(const MUXNode& other)
{
    //copy ctor
}

MUXNode& MUXNode::operator=(const MUXNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
