#ifndef DLATCHNODE_H
#define DLATCHNODE_H

#include <AbstractNode.h>


class DLATCHNode : public AbstractNode
{
    public:
        DLATCHNode();
        virtual ~DLATCHNode();
        DLATCHNode(const DLATCHNode& other);
        DLATCHNode& operator=(const DLATCHNode& other);

    private:
};

#endif // DLATCHNODE_H
