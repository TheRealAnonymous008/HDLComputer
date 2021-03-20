#ifndef NOTNODE_H
#define NOTNODE_H

#include <AbstractNode.h>


class NOTNode : public AbstractNode
{
    public:
        NOTNode();
        NOTNode(int n);
        virtual ~NOTNode();
        NOTNode(const NOTNode& other);
        NOTNode& operator=(const NOTNode& other);

    private:
        void Process() override;
};

#endif // NOTNODE_H
