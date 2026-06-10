#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <array>
#include <SDL3/SDL.h>
#include "util_logger.h"

const auto FILE_NAME = std::string("error_log.txt");

void rgp::Util::logMessage(const std::string& message) {
    std::ofstream logFile(FILE_NAME, std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open or create the log file!" << std::endl;
        return;
    }

    const std::time_t now = std::time(nullptr);

    std::tm timeInfo;

    localtime_s(&timeInfo, &now);

    std::array<char, 20> timestamp{};
    std::strftime(timestamp.data(), timestamp.size(), "%Y-%m-%d %H:%M:%S", &timeInfo);

    logFile << "[" << timestamp.data() << "] " << message << std::endl;
}
