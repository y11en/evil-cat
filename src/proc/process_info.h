#ifndef EVIL_CAT_PROC_PROCESS_INFO_H
#define EVIL_CAT_PROC_PROCESS_INFO_H

#include <unordered_map>
#include <string>

class ProcessInfo {

public:

    static ProcessInfo &getInstance();

    virtual bool attach(const std::string &processName) = 0;

    virtual bool detach() = 0;

    virtual bool getModuleAddress(const std::string &moduleName, void *&address) = 0;

    virtual bool refresh() = 0;
};

#endif //EVIL_CAT_PROC_PROCESS_INFO_H
