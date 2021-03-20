#ifndef PCNODE_H
#define PCNODE_H

#include <AbstractNode.h>


class PCNode : public AbstractNode
{
    public:
        PCNode(int w);
        virtual ~PCNode();
        PCNode(const PCNode& other);
        PCNode& operator=(const PCNode& other);

    protected:

    private:
};

#endif // PCNODE_H
