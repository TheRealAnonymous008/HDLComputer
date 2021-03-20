#include <iostream>
#include "Nodes.h"
#include "Signal.h"
#include "Port.h"
#include "Clock.h"
#include <math.h>

int main()
{
    // Demonstration of using a k-bit RAM with n registers
    // Let's say we have 2-bit RAM with 2 registers. n = 2, w = k = 2
    int n = 2;
    int k = 2;

    int inputs  = k + 4;
    int outputs = k;

    INPUTNode* inNode = new INPUTNode(inputs);
    OUTPUTNode* outNode = new OUTPUTNode(outputs);
    AbstractNode* node = new PCNode(k);
    Clock* clock = new Clock();



    for(int i = 0; i < inputs; i ++){
        inNode->getOutputPort(i)->connectTo(node->getInputPort(i));
    }

    for(int i = 0; i < outputs; i ++){
        node->getOutputPort(i)->connectTo(outNode->getInputPort(i));
    }


    // Program Logic goes here
    while(true){
        for(int i = 0; i < inputs; i ++){
            if(i == k){
                std::cout<<"Enter inc / store / reset / clock: ";
            }
            int x;
            std::cin>>x;
            inNode->setSignalAtPort(new Signal(x), i);
        }


        inNode->performOperation();
        node->performOperation();
        outNode->performOperation();


        for(int i = 0; i < inputs; i++){
            node->getInputPort(i)->displayVal();
        }
        std::cout<<"\n";

        for(int i = 0; i < outputs; i++){
            outNode->displaySignalAtPort(i);
        }
    }

    return 0;
}
