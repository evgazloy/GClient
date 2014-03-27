#ifndef TCPCOMMANDS_H
#define TCPCOMMANDS_H

#include <QDataStream>
#include "mprotocol.h"

enum
{
    typeDevice,
    typeControl
};

enum
{
    cmdRegistration,
    cmdTemp,
    cmdTime
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

struct cmdTemp_s
{
    quint8 set;
    float temp;
};

inline QDataStream &operator <<(QDataStream &out, const cmdTemp_s &data)
{
    out<<quint8(cmdTemp)<<data.set<<data.temp;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, cmdTemp_s &data)
{
    in>>data.set>>data.temp;
    return in;
}

struct cmdTime_s
{
    quint8 set;
    MTime time;
};

inline QDataStream &operator <<(QDataStream &out, const cmdTime_s &data)
{
    out<<quint8(cmdTime)<<data.set<<data.time.day<<data.time.hour<<data.time.minute<<
         data.time.second;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, cmdTime_s &data)
{
    in>>data.set>>data.time.day>>data.time.hour>>data.time.minute>>data.time.second;
    return in;
}

#endif // TCPCOMMANDS_H
