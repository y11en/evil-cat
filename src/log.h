#ifndef EVIL_CAT_LOG_H
#define EVIL_CAT_LOG_H

#include <iostream>

class DummyLogStream : public std::ostream {
    class DummyLogBuffer : public std::streambuf {
    public:
        int overflow(int c) override {
            return c;
        }
    } dummyBuffer;
public:
    DummyLogStream() : std::ostream(&dummyBuffer) {}
};

#define DEBUG_ENABLE 0

#if (DEBUG_ENABLE)
#define LOG_DEBUG (std::cout<<"[debug]")
#else
#define LOG_DEBUG (DummyLogStream())
#endif

#endif //EVIL_CAT_LOG_H
