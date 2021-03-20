#include "ALUNode.h"
#include "Nodes.h"
#include<iostream>

ALUNode::ALUNode(int n) : AbstractNode {2 * n + 6, n + 2}
{
    // Specifications:
    // The first n inputs are the n-bits of the first input, the next n bits are for the second input.
    // The last 6 n inputs are function specifiers which modify input and output based on if they are true or false. In order they are:

    // 0: zx = zero the x input
    // 1: nx = negate the x input (bitwise. Always perform zx first if needed)
    // 2: zy = zero the y input
    // 3: ny = negate the y input (bitwise)
    // 4: f = a function code, if it's 1 perform an addition, 0 for bitwise and
    // 5: no = negate the output.


    // There are n + 2 outputs. The first n is the output of the function f. The last 2 in order are
    // zr = true iff out = 0
    // ng = true iff out < 0

    // Configure corresponding nodes.
    AbstractNode* zeroxNode = zerox(n);
    AbstractNode* zeroyNode = zeroy(n);
    AbstractNode* negxNode = negatex(n, zeroxNode);
    AbstractNode* negyNode= negatey(n, zeroyNode);

    // For performing the function we feed the nodes corresponding to nx and ny to f.
    AbstractNode* addition = xplusy(n, negxNode, negyNode);
    AbstractNode* conjunction = xandy(n, negxNode, negyNode);

    // Now just choose whichever is needed using a MUXNode. Note that 1 chooses the first option
    AbstractNode* chooser = choice(n, addition, conjunction);

    // Finally perform negation if necessary
    AbstractNode* outputNegation = negateo(n, chooser);

    // Wire up the output of Negation
    for(int i = 0; i < n; i ++){
        outputNegation->getOutputPort(i)->connectTo(this->getOutputPort(i));
    }
    // Perform the check to see if the answer is zero.
    checkIfZero(n, outputNegation);

    // to determine ng, just check the MSB
    outputNegation->getOutputPort(n - 1)->connectTo(this->getOutputPort(n + 1));

}

AbstractNode* ALUNode::zerox(int n){
    AbstractNode* notNode = new NOTNode();
    AbstractNode* andNode = new ANDNode(n);
    this->internalNodes.push_back(notNode);
    this->internalNodes.push_back(andNode);

    this->getInputPort(2 * n)->connectTo(notNode->getInputPort(0));

    for(int i = 0; i < n; i++){
        this->getInputPort(i)->connectTo(andNode->getInputPort(i));
        notNode->getOutputPort(0)->connectTo(andNode->getInputPort(n + i));
    }

    // This is to make things easier to connect
    return andNode;
}

AbstractNode* ALUNode::zeroy(int n){
    AbstractNode* notNode = new NOTNode();
    AbstractNode* andNode = new ANDNode(n);
    this->internalNodes.push_back(notNode);
    this->internalNodes.push_back(andNode);

    this->getInputPort(2 * n + 2)->connectTo(notNode->getInputPort(0));

    for(int i = 0; i < n; i++){
        this->getInputPort(n + i)->connectTo(andNode->getInputPort(i));
        notNode->getOutputPort(0)->connectTo(andNode->getInputPort(n + i));
    }

    return andNode;
}

AbstractNode* ALUNode::negatex(int n, AbstractNode* zeroxNode){
    // Connect zerox node
    AbstractNode* negxNode = new XORNode(n);
    this->internalNodes.push_back(negxNode);

    for(int i = 0; i < n; i ++){
        zeroxNode->getOutputPort(i)->connectTo(negxNode->getInputPort(i));
        this->getInputPort(2 * n + 1)->connectTo(negxNode->getInputPort(n + i));
    }

    return negxNode;
}

AbstractNode* ALUNode::negatey(int n, AbstractNode* zeroyNode){
    // Connect zerox node
    AbstractNode* negxNode = new XORNode(n);
    this->internalNodes.push_back(negxNode);

    for(int i = 0; i < n; i ++){
        zeroyNode->getOutputPort(i)->connectTo(negxNode->getInputPort(i));
        this->getInputPort(2 * n + 3)->connectTo(negxNode->getInputPort(n + i));
    }

    return negxNode;
}

AbstractNode* ALUNode::xplusy(int n, AbstractNode* px, AbstractNode *py){
    AbstractNode* adderNode = new ADDERNode(n);
    this->internalNodes.push_back(adderNode);

    for(int i = 0; i < n; i ++){
        px->getOutputPort(i)->connectTo(adderNode->getInputPort(i));
        py->getOutputPort(i)->connectTo(adderNode->getInputPort(n + i));
    }

    return adderNode;
}

AbstractNode* ALUNode::xandy(int n, AbstractNode* px, AbstractNode *py){
    AbstractNode* andNode = new ANDNode(n);
    this->internalNodes.push_back(andNode);

    for(int i = 0; i < n; i ++){
        px->getOutputPort(i)->connectTo(andNode->getInputPort(i));
        py->getOutputPort(i)->connectTo(andNode->getInputPort(n + i));
    }

    return andNode;
}

AbstractNode* ALUNode::choice(int n, AbstractNode* a, AbstractNode* c){
    AbstractNode* node = new MUXNode(n);
    this->internalNodes.push_back(node);
    for(int i = 0; i < n; i ++){
        c->getOutputPort(i)->connectTo(node->getInputPort(i));
        a->getOutputPort(i)->connectTo(node->getInputPort(n + i));
    }
    this->getInputPort(2 * n + 4)->connectTo(node->getInputPort(2 *n));
    return node;
}

AbstractNode* ALUNode::negateo(int n, AbstractNode* o){
    // Connect zerox node
    AbstractNode* negoNode = new XORNode(n);
    this->internalNodes.push_back(negoNode);

    for(int i = 0; i < n; i ++){
        o->getOutputPort(i)->connectTo(negoNode->getInputPort(i));
        this->getInputPort(2 * n + 5)->connectTo(negoNode->getInputPort(n + i));
    }

    return negoNode;
}

void ALUNode::checkIfZero(int n, AbstractNode* o){
    int currNodes = this->internalNodes.size();

    for(int i = 0; i < n; i ++){
        AbstractNode* node = new ORNode();
        this->internalNodes.push_back(node);

        o->getOutputPort(i)->connectTo(node->getInputPort(0));
        if(i == 0){
            this->internalNodes[currNodes]->getInputPort(1)->setRegister(*(new Signal(0)));
            this->internalNodes[currNodes]->getInputPort(1)->receiveData();
        }
        else{
            this->internalNodes[currNodes + i - 1]->getOutputPort(0)->connectTo(node->getInputPort(1));
        }
    }

    currNodes = this->internalNodes.size();
    AbstractNode* nd = new NOTNode();
    this->internalNodes.push_back(nd);;
    this->internalNodes[currNodes - 1]->getOutputPort(0)->connectTo(nd->getInputPort(0));
    nd->getOutputPort(0)->connectTo(this->getOutputPort(n));

}
ALUNode::~ALUNode()
{
    //dtor
}

ALUNode::ALUNode(const ALUNode& other)
{
    //copy ctor
}

ALUNode& ALUNode::operator=(const ALUNode& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


