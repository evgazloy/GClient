#ifndef TCPCOMMANDS_H
#define TCPCOMMANDS_H

#include <QDataStream>

enum
{
    typeDevice,
    typeControl
};

enum
{
    cmdRegistration,
};

struct cmdRegistration_s
{
    quint8 type;
};

inline QDataStream &operator <<(QDataStream &out, const cmdRegistration_s &data)
{
    out<<quint8(cmdRegistration)<<data.type;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, cmdRegistration_s &data)
{
    in>>data.type;
    return in;
}

#endif // TCPCOMMANDS_H
