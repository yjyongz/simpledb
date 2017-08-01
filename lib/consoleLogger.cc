#include <logger.h>
#include <iostream>
using namespace std;

class ConsoleLogger: public Logger {
public:
    ConsoleLogger() {};
    ~ConsoleLogger() {};
    void info(string msg) { cout<<"INFO:"<<msg<<endl; }
    void error(string msg) { cout<<"ERROR:"<<msg<<endl; }
};
