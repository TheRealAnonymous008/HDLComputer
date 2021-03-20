#ifndef RAMNODE_H
#define RAMNODE_H

#include <AbstractNode.h>


class RAMNode : public AbstractNode
{
    public:
        RAMNode(int n, int w);
        virtual ~RAMNode();
        RAMNode(const RAMNode& other);
        RAMNode& operator=(const RAMNode& other);

    protected:

    private:
};

#endif // RAMNODE_H
