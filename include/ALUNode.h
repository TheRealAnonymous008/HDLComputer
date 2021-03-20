#ifndef ALUNODE_H
#define ALUNODE_H

#include <AbstractNode.h>


class ALUNode : public AbstractNode
{
    public:
        ALUNode(int n);
        virtual ~ALUNode();
        ALUNode(const ALUNode& other);
        ALUNode& operator=(const ALUNode& other);

    private:
        AbstractNode* zerox(int n);
        AbstractNode* negatex(int n, AbstractNode* zeroxNode);
        AbstractNode* zeroy(int n);
        AbstractNode* negatey(int n, AbstractNode* zeroyNode);
        AbstractNode* xplusy(int n, AbstractNode* px, AbstractNode* py);
        AbstractNode* xandy(int n, AbstractNode* px, AbstractNode* py);
        AbstractNode* choice(int n, AbstractNode* a, AbstractNode* c);
        AbstractNode* negateo(int n, AbstractNode* o);
        void checkIfZero(int n, AbstractNode* o);
};

#endif // ALUNODE_H
