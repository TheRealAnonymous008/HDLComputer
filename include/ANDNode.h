#ifndef ANDNODE_H
#define ANDNODE_H

#include <AbstractNode.h>


class ANDNode : public AbstractNode
{
    public:
        ANDNode();
        ANDNode(int n);
        virtual ~ANDNode();
        ANDNode(const ANDNode& other);
        ANDNode& operator=(const ANDNode& other);

    private:

};

#endif // ANDNODE_H
