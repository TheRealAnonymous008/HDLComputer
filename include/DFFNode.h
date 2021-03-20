#ifndef DFFNODE_H
#define DFFNODE_H

#include <AbstractNode.h>


class DFFNode : public AbstractNode
{
    public:
        DFFNode();
        virtual ~DFFNode();
        DFFNode(const DFFNode& other);
        DFFNode& operator=(const DFFNode& other);

    protected:

    private:
};

#endif // DFFNODE_H
