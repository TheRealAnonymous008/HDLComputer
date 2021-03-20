#ifndef INPUTNODE_H
#define INPUTNODE_H

#include <AbstractNode.h>


class INPUTNode : public AbstractNode
{
    public:
        INPUTNode(int n);
        virtual ~INPUTNode();
        INPUTNode& operator=(const INPUTNode& other);
        INPUTNode(const INPUTNode& other);

        void setSignalAtPort(Signal *signal, int number);

    private:
        void Process() override;

};

#endif // INPUTNODE_H
