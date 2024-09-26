#include "TargetTracker.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <model_path> <serial_port> <baud_rate>" << std::endl;
        return 1;
    }

    const char* model_path = argv[1];
    const char* serial_port = argv[2];
    unsigned int baud_rate = 0;

    try {
        baud_rate = std::stoi(argv[3]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid baud rate: " << argv[3] << std::endl;
        return 1;
    }

    TargetTracker tracker(model_path, serial_port, baud_rate);
    
    tracker.run();
    return 0;
}
