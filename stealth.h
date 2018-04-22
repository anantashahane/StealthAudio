#ifndef STEALTH_H
#define STEALTH_H
#include "QString"

class Stealth
{
    QString inputfilename;
    QString outputfilename;
    QString Message;
public:
    Stealth();
    void Setinput(QString);
    void Setoutput(QString);
    void Setmessage(QString);
    int Encode();
    QString Decode();
};

#endif // STEALTH_H
