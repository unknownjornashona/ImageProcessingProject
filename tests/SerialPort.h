#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <boost/asio.hpp>
#include <string>
#include <iostream>

class SerialPort {
public:
    SerialPort(const std::string& port, unsigned int baud_rate);
    void sendData(const std::string& data);
    ~SerialPort();

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};

#endif // SERIALPORT_H
