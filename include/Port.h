#ifndef PORT_H
#define PORT_H
#include<vector>

#include "Signal.h"

class Port
{
    public:
        Port();
        void connectTo(Port* port);
        void sendData();
        void receiveData();
        void setRegister(Signal &s);

        void displayVal();
        Signal getActualValue();
        void displayReg();

        void connectFrom(Port* port);


    private:
        std::vector<Port* > outNeighbor;
        std::vector<Port* > inNeighbor;

        Signal internalRegister;
        Signal actualValue;
        int id;

};

#endif // PORT_H
