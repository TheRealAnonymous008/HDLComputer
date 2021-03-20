#ifndef XORNODE_H
#define XORNODE_H

#include <AbstractNode.h>


class XORNode : public AbstractNode
{
    public:
        XORNode();
        XORNode(int n);
        virtual ~XORNode();
        XORNode(const XORNode& other);
        XORNode& operator=(const XORNode& other);

    private:
};

#endif // XORNODE_H
