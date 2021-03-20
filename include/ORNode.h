#ifndef ORNODE_H
#define ORNODE_H

#include <AbstractNode.h>


class ORNode : public AbstractNode
{
    public:
        ORNode();
        ORNode(int n);
        virtual ~ORNode();
        ORNode(const ORNode& other);
        ORNode& operator=(const ORNode& other);

    private:

};

#endif // ORNODE_H
