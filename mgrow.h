#ifndef MGROW_H
#define MGROW_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QDebug>
#include <QTime>
#include <QTimerEvent>
#include "mgsocket.h"
#include "mprotocol.h"

#define PORT_TIMEOUT 1000
#define SOCKET_TIMEOUT 2000

class MGrow : public QObject
{
    Q_OBJECT
public:
    explicit MGrow(QObject *parent = 0);
    ~MGrow();

    void openPort();
    void printPortNames();
    QString portName() const;
    void setPortName(const QString &portName);

private:
    QString m_portName;
    QSerialPort m_port;
    QByteArray m_buffer;
    quint8 m_dataCount;
    quint8 m_cmd = 0;
    int m_portTimerId = 0;

    MTime m_time;
    float m_temp = 0;
    quint8 m_state;
    MOptions m_options;
    MMVent m_vent;

    void inData();
    bool readCmd(void *buf, quint8 size);
    void sendQuery(quint8 query, void *buf = 0, quint8 size = 0);

    void timerEvent(QTimerEvent *ev);

signals:

private slots:
    void portError(QSerialPort::SerialPortError err);

//-----------------------------------------------------------------------

public:
    void setCertificate(const QString &file);
    void setServer(const QString &host, const quint16 &port);
    void createConnection();

private:
    MGSocket *m_socket = 0;
    int m_socketTimerId = 0;
    int m_socketState = QAbstractSocket::UnconnectedState;
    QString m_host;
    quint16 m_serverPort;

    void initSocket();

signals:

private slots:
    void socketReady();
    void socketError(QAbstractSocket::SocketError err);
};

#endif // MGROW_H
