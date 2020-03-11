#ifndef LOG_MSG_H
#define LOG_MSG_H

#include <iostream>
#include <string>


#ifdef FDEBUG

template<typename T>
void log_msg(const std::string& fileName, T msg)
{
    std::cout << fileName << ": " << msg << std::endl;
}

#else // FDEBUG

template<typename T>
void log_msg(const std::string& fileName, T msg)
{
}

#endif // FDEBUG

#endif // LOG_MSG_H