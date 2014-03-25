#include <QCoreApplication>
#include <QCommandLineParser>
#include "mgrow.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("GClient");
    QCoreApplication::setApplicationVersion("0.1");
    MGrow m_grow;

    QCommandLineParser parser;
    parser.setApplicationDescription("Hardware client");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portName(QStringList()<<"p"<<"port-name", "Specify serial port name", "name", "ttyUSB0");
    parser.addOption(portName);

    QCommandLineOption printNames(QStringList()<<"a"<<"available-ports", "Print all ports names");
    parser.addOption(printNames);

    QCommandLineOption serverHostName(QStringList()<<"n"<<"host-name", "Specify server's host name", "hostName", "vo.grow");
    parser.addOption(serverHostName);

    QCommandLineOption serverPort(QStringList()<<"P"<<"server-port", "Specify server's port", "port", "32345");
    parser.addOption(serverPort);

    QCommandLineOption certificate(QStringList()<<"c"<<"certificate", "Specify local certificate", "file", "keys/client.pem");
    parser.addOption(certificate);

    parser.process(a);

    if(parser.isSet(printNames)) {
        m_grow.printPortNames();
        return 0;
    }

    m_grow.setPortName(parser.value(portName));
    m_grow.openPort();

    m_grow.setCertificate(parser.value(certificate));
    m_grow.setServer(parser.value(serverHostName), parser.value(serverPort).toInt());
    m_grow.createConnection();

    return a.exec();
}
