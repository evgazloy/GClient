#ifndef TCPCOMMANDS_H
#define TCPCOMMANDS_H

#include <QDataStream>

inline void calcSize(QDataStream &out)
{
    if(out.device())
    {
        out.device()->seek(0);
        out<<quint32(out.device()->size()-sizeof(quint32));
    }
}

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
    out<<quint32(0)<<quint8(cmdRegistration)<<data.type;
    calcSize(out);
    return out;
}

inline QDataStream &operator >>(QDataStream &in, cmdRegistration_s &data)
{
    in>>data.type;
    return in;
}

#endif // TCPCOMMANDS_H
