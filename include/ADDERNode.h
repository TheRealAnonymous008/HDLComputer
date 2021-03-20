#ifndef ADDERNODE_H
#define ADDERNODE_H

#include <AbstractNode.h>


class ADDERNode : public AbstractNode
{
    public:
        ADDERNode();
        ADDERNode(int n);               // n-bit adder
        virtual ~ADDERNode();
        ADDERNode(const ADDERNode& other);
        ADDERNode& operator=(const ADDERNode& other);

    private:

};

#endif // ADDERNODE_H
