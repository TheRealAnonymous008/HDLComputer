#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include "Signal.h"
#include "Port.h"

#include<vector>
#include<string>

class AbstractNode
{
    public:
        AbstractNode();
        AbstractNode(int inputs, int outputs);
        AbstractNode(std::string nodeName, int inputs, int outputs);
        virtual ~AbstractNode();
        AbstractNode(const AbstractNode& other);
        AbstractNode& operator=(const AbstractNode& other);

        std::string getId();
        Port* getInputPort(int number);
        Port* getOutputPort(int number);

        void performOperation();


    protected:
        virtual void Process() {
            // Default implementation
            for(int i = 0; i < inputPorts ; i ++){
                this->getInputPort(i)->sendData();
            }

            for(int i = 0; i < (int) this->internalNodes.size(); i ++){
                this->internalNodes[i]->performOperation();
            }

            for(int i = 0; i < outputPorts; i ++){
                this->getOutputPort(i)->receiveData();
            }
        };

        std::string id = "";
        int inputPorts = 0;
        int outputPorts = 0;

        std::vector<Port*> inPorts;
        std::vector<Port*> outPorts;
        std::vector<AbstractNode*> internalNodes;

    private:
        std::string generateId();

};

#endif // ABSTRACTNODE_H
