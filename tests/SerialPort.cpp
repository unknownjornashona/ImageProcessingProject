#include "SerialPort.h"

SerialPort::SerialPort(const std::string& port, unsigned int baud_rate)
    : serial(io, port) {
    serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
}

void SerialPort::sendData(const std::string& data) {
    boost::asio::write(serial, boost::asio::buffer(data));
}

SerialPort::~SerialPort() {
    serial.close();
}
