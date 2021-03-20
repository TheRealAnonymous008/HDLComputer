#ifndef REGNODE_H
#define REGNODE_H

#include <AbstractNode.h>


class REGNode : public AbstractNode
{
    public:
        REGNode();
        REGNode(int n);
        virtual ~REGNode();
        REGNode(const REGNode& other);
        REGNode& operator=(const REGNode& other);

    protected:

    private:
};

#endif // REGNODE_H
