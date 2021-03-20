#include "RAMNode.h"
#include "Nodes.h"
#include<math.h>

RAMNode::RAMNode(int n, int w) : AbstractNode {"RAM", w + (int) ceil(log2(n)) + 2, w}
{
    // w is the width, n is number of registers.

    // Configure registers
    int selectorBits = (int) ceil(log2(n));

    AbstractNode* registers[n];
    AbstractNode* regSelector = new MUXNode(w, n);
    AbstractNode* loadSelector = new MUXNode(w);

    for(int i = 0; i < n; i ++){
        registers[i] = new REGNode(w);
    }

    // Connect registers to regSelector. Also connect all input nodes to registers
    for(int i = 0; i < n; i ++){
        for(int j = 0 ; j <w; j++){
            this->getInputPort(j)->connectTo(registers[i]->getInputPort(j));
            registers[i]->getOutputPort(j)->connectTo(regSelector->getInputPort(i * n + j));
        }
        // Connect all registers to clock signal.
        this->getInputPort(w + selectorBits + 1)->connectTo(registers[i]->getInputPort(w + 1));
    }

    for(int i = 0; i < selectorBits ;i ++){
        this->getInputPort(w + i)->connectTo(regSelector->getInputPort(n * w + i));
    }

    // Connect regSelector to loadSelector
    for(int i = 0; i < w; i ++){
        regSelector->getOutputPort(i)->connectTo(loadSelector->getInputPort(i));
        this->getInputPort(i)->connectTo(loadSelector->getInputPort(w + i));
    }
    // Connect load bit to load Selector
    this->getInputPort(w + selectorBits)->connectTo(loadSelector->getInputPort(2 * w));

    // Connect load Selector to output
    for(int i = 0; i < w; i++){
        loadSelector->getOutputPort(i)->connectTo(this->getOutputPort(i));
    }

    // Configure load signal for each register
    for(int i = 0; i < n; i++){
        AbstractNode* eqChecker = new EQNode(selectorBits, i);
        for(int j = 0; j < selectorBits; j ++){
            // Wire up selector bits
            this->getInputPort(w + j)->connectTo(eqChecker->getInputPort(j));
        }
        // Wire the eq node to an and signal. The other operand should be whether load bit is on
        AbstractNode* loadModifier = new ANDNode();
        eqChecker->getOutputPort(0)->connectTo(loadModifier->getInputPort(0));
        this->getInputPort(w + selectorBits)->connectTo(loadModifier->getInputPort(1));
        loadModifier->getOutputPort(0)->connectTo(registers[i]->getInputPort(w));

        this->internalNodes.push_back(eqChecker);
        this->internalNodes.push_back(loadModifier);
        this->internalNodes.push_back(registers[i]);
    }

    // Add nodes in order
    this->internalNodes.push_back(regSelector);
    this->internalNodes.push_back(loadSelector);


}

RAMNode::~RAMNode()
{
    //dtor
}

RAMNode::RAMNode(const RAMNode& other)
{
    //copy ctor
}

RAMNode& RAMNode::operator=(const RAMNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
