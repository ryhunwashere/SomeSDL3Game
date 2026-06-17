#pragma once
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

namespace rgp::util::logging {
    constexpr auto FILE_NAME = "error_log.txt";

    static void logMessage(const std::string_view message) {
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
}