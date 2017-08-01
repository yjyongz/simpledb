#ifndef _SIMPLE_DB_H_
#define _SIMPLE_DB_H_

#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <algorithm>
#include <mutex>
#include <string>
#include <cstring>
#include <iterator>
#include <sstream>
#include <map>
using namespace std;

class SimpleDB {
typedef map<string, void*> MAPTYPE;
public:
    SimpleDB():m_SYNC(1),m_ASYNC(2), m_version("1.0"),m_debug(0) {
        m_mode = m_SYNC;
    }
    SimpleDB(int8_t num_clients, int8_t mode):m_SYNC(1), \
             m_ASYNC(2),m_mode(mode), m_version("1.0"),m_debug(0) {
    }
    int create_path(const vector<string>& tokens);
    int read_path(const vector<string>& tokens);
    int update_path(const vector<string>& tokens, const string& value);
    int delete_path(const vector<string>& tokens);
    void show_version() { cout<<m_version<<endl; } 
    void setDebug(int8_t mode) { m_debug = mode;}
private:
    uint8_t              m_mode;
    const uint8_t        m_SYNC;   
    const uint8_t        m_ASYNC;
    uint8_t              m_debug;
    const string         m_version;
    MAPTYPE              m_map;
    /*
     * private functions
     */
    int create_path(const vector<string>& tokens, int idx, int size, MAPTYPE* map);
    int read_path(const vector<string>& tokens, int idx, int size, MAPTYPE* map);
    int update_path(const vector<string>& tokens, int idx, int size,
                    const string& value, MAPTYPE* map);
    int delete_path(const vector<string>& tokens, int idx, int size, MAPTYPE *map);
};
#endif
