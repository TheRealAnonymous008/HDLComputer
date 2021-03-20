#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include <AbstractNode.h>


class OUTPUTNode : public AbstractNode
{
    public:
        OUTPUTNode(int number);
        virtual ~OUTPUTNode();
        OUTPUTNode(const OUTPUTNode& other);
        OUTPUTNode& operator=(const OUTPUTNode& other);

        Signal* getSignalAtPort(int number);
        void displaySignalAtPort(int number);

    private:
        void Process() override;
};

#endif // OUTPUTNODE_H
