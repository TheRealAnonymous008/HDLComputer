#ifndef NORNODE_H
#define NORNODE_H

#include <AbstractNode.h>


class NORNode : public AbstractNode
{
    public:
        NORNode();
        NORNode(int n);
        virtual ~NORNode();
        NORNode(const NORNode& other);
        NORNode& operator=(const NORNode& other);

    protected:

    private:
};

#endif // NORNODE_H
