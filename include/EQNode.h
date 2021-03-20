#ifndef EQNODE_H
#define EQNODE_H

#include <AbstractNode.h>


class EQNode : public AbstractNode
{
    public:
        EQNode(int n, int number);
        virtual ~EQNode();
        EQNode(const EQNode& other);
        EQNode& operator=(const EQNode& other);

    protected:

    private:
};

#endif // EQNODE_H
