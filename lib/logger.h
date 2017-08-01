#ifndef __LOGGER__
#define __LOGGER__
#include <string>
using namespace std;

class Logger {
public:
    virtual void info(string msg)=0;
    virtual void error(string msg)=0;
};
#endif
