//
// Created by patryk on 15/07/2021.
//

#include <chrono>
#include <sstream>
#include <ratio>

std::string getTimeString(const std::chrono::system_clock::duration& duration)
{
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - minutes);
    auto centiseconds = std::chrono::duration_cast<std::chrono::duration<int, std::centi>>(duration - minutes - seconds);
    std::stringstream ss;
    ss << minutes.count() << 'm' << seconds.count() << 's' << centiseconds.count();
    return ss.str();
}