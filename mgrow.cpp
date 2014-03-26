#include "mgrow.h"

MGrow::MGrow(QObject *parent) :
    QObject(parent), m_dataCount(0)
{
    this->initSocket();
}

MGrow::~MGrow()
{
    delete m_socket;
}

void MGrow::openPort()
{
    m_port.setPortName(m_portName);
    if(m_port.open(QSerialPort::ReadWrite))
    {
        m_port.setBaudRate(9600);
        m_port.setDataBits(QSerialPort::Data8);
        m_port.setFlowControl(QSerialPort::NoFlowControl);
        m_port.setParity(QSerialPort::NoParity);
        m_port.setStopBits(QSerialPort::OneStop);
        connect(&m_port, &QSerialPort::readyRead, this, &MGrow::inData);
        connect(&m_port, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(portError(QSerialPort::SerialPortError)));

        qDebug()<<"Port"<<m_portName<<"opened";
    }
    else
    {
        qCritical()<<"Error opening port:"<<m_port.errorString();
        m_portTimerId = this->startTimer(PORT_TIMEOUT);
    }
}

void MGrow::printPortNames()
{
    qDebug()<<"Available ports:";
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, ports)
        qDebug()<<info.portName();
}

void MGrow::sendQuery(quint8 query, void *buf, quint8 size)
{
    QByteArray data;
    data.append(query);
    if(buf)
        data.append((char *)buf, size);
    if(m_port.isOpen())
        m_port.write(data);
}

void MGrow::inData()
{
    if(!m_port.isOpen())
        return;

    m_buffer.append(m_port.readAll());

    while(m_buffer.size())
    {
        quint8 cmd = m_buffer.at(0);

        quint8 size = 0;

        void *ptr = 0;
        switch(cmd)
        {
        case USB_TEMP_R:
            size = sizeof(float);
            ptr = &m_temp;
            break;

        case USB_TIME_R:
            size = sizeof(MTime);
            ptr = &m_time;
            break;

        case USB_STATE_R:
            size = 1;
            ptr = &m_state;
            break;

        case USB_VENT_R:
            size = sizeof(MMVent);
            ptr = &m_vent;
            break;

        case USB_OPT_R:
            size = sizeof(MOptions);
            ptr = &m_options;
            break;

        case USB_START_R:
            qDebug()<<"Device started";
            m_buffer.remove(0,1);
            break;

        default:
            m_buffer.remove(0,1);
        }
        if(size)
        {
            if(!this->readCmd(ptr, size))
                return;
        }
    }
}

bool MGrow::readCmd(void *buf, quint8 size)
{
    if(m_buffer.size()<size+1)
        return false;

    memcpy(buf, m_buffer.data()+1, size);
    m_buffer.remove(0 ,size+1);
    return true;
}

void MGrow::portError(QSerialPort::SerialPortError err)
{
    qDebug()<<err;
    m_port.disconnect();
    m_port.close();
    m_portTimerId = this->startTimer(PORT_TIMEOUT);
    qDebug()<<"Port closed";
}

QString MGrow::portName() const
{
    return m_portName;
}

void MGrow::setPortName(const QString &portName)
{
    m_portName = portName;
}

void MGrow::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == m_portTimerId)
    {
        if(!m_port.isOpen())
            this->openPort();
        else
            this->killTimer(m_portTimerId);
    }
    if(ev->timerId() == m_socketTimerId)
    {
        Q_CHECK_PTR(m_socket);
        if(m_socketState == QAbstractSocket::UnconnectedState)
        {
            m_socketState = QAbstractSocket::ConnectingState;
            this->createConnection();
        }
    }
}

void MGrow::initSocket()
{
    m_socket = new MGSocket(typeDevice);
    Q_CHECK_PTR(m_socket);
    connect(m_socket, SIGNAL(sig_ready()), SLOT(socketReady()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(sig_socketError(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
    m_socket->initSocket();
}

void MGrow::socketReady()
{
    qDebug()<<"Socket ready";
    m_socketState = QAbstractSocket::ConnectedState;
    this->killTimer(m_socketTimerId);
    Q_CHECK_PTR(m_socket);

    m_socket->send("adsfasd");
}

void MGrow::socketError(QAbstractSocket::SocketError err)
{
    m_socketState = QAbstractSocket::UnconnectedState;
    m_socketTimerId = this->startTimer(SOCKET_TIMEOUT);
}

void MGrow::setCertificate(const QString &file)
{
    Q_CHECK_PTR(m_socket);
    m_socket->setCertificate(file);
}

void MGrow::setServer(const QString &host, const quint16 &port)
{
    m_host = host;
    m_serverPort = port;
}

void MGrow::createConnection()
{
    Q_CHECK_PTR(m_socket);
    m_socket->createConnection(m_host, m_serverPort);
}

