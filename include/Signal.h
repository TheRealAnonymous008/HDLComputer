#ifndef SIGNAL_H
#define SIGNAL_H


class Signal
{
    public:
        Signal(int _value);
        Signal();
        virtual ~Signal();
        Signal(const Signal& other);
        Signal& operator=(const Signal& other);
        Signal(Signal &&other);

        bool operator ==(Signal& other){
            if(this->getValue() == other.getValue())
                return true;
            return false;
        }

        int getValue();

    private:
        int value;
};

#endif // SIGNAL_H
