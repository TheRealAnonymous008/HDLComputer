#ifndef INVNODE_H
#define INVNODE_H

#include <AbstractNode.h>


class INVNode : public AbstractNode
{
    public:
        INVNode(int n);
        virtual ~INVNode();
        INVNode(const INVNode& other);
        INVNode& operator=(const INVNode& other);

    protected:

    private:
};

#endif // INVNODE_H
