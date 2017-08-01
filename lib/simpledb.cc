#include <simpledb.h>
using namespace std;

int SimpleDB::create_path(const vector<string> &tokens) {
    return create_path(tokens, 0, tokens.size(), &m_map);
}

int SimpleDB::create_path(const vector<string>& tokens, int idx,
                          int size, MAPTYPE* map) {
    if (idx == size) {
        cout<<endl;
        return 0;
    }
    if (map->find(tokens[idx]) == map->end()) {
        cout<<"create:"<<tokens[idx]<<" ";
        (*map)[tokens[idx]] = new MAPTYPE();
    }
    return create_path(tokens, idx+1, size, (MAPTYPE*)((*map)[tokens[idx]]));
}

int SimpleDB::read_path(const vector<string> &tokens) {
    return read_path(tokens, 0, tokens.size(), &m_map);
}

int SimpleDB::read_path(const vector<string>& tokens, int idx, 
                        int size, MAPTYPE* map) {
    if (idx == size) {
        //MAPTYPE* m = (MAPTYPE*)((*map)[tokens[idx]]);
        if (map->find("value") != map->end()) {
            cout<<"="<<(char*)((*map)["value"])<<endl;
        }
        return 0;
    }

    if (map->find(tokens[idx]) != map->end()) {
        cout<<tokens[idx]<<"/";
    } else {
        return -1;
    }
    return read_path(tokens, idx+1, size, (MAPTYPE*)((*map)[tokens[idx]]));
}

int SimpleDB::update_path(const vector<string> &tokens, const string &value) {
    return update_path(tokens, 0, tokens.size(), value, &m_map);
}

int SimpleDB::update_path(const vector<string>& tokens, int idx, 
                          int size, const string &value, MAPTYPE* map) {
    if (idx == size) {
        char *c = new char[64];
        strncpy(c, value.c_str(), 64);
        (*map)["value"] = c;
        return 0;
    }

    if (map->find(tokens[idx]) != map->end()) {
        cout<<"update:"<<tokens[idx]<<" ";
        return update_path(tokens, idx+1, size, value, (MAPTYPE*)map->at(tokens[idx]));
    } else {
        return -1;
    }
}

int SimpleDB::delete_path(const vector<string> &tokens) {
    return delete_path(tokens, 0, tokens.size(), &m_map);
}

int SimpleDB::delete_path(const vector<string>& tokens, int idx,
                          int size, MAPTYPE* map) {
    if (idx == size) {
        if (map->find("value") != map->end()) {
            delete (char*)map->at("value");
            map->erase(map->find("value"));
        }
        return 0;
    }

    if (map->find(tokens[idx]) != map->end()) {
        delete_path(tokens, idx+1, size, (MAPTYPE*)map->at(tokens[idx]));
    }
    if (idx != size) {
        if (map->find(tokens[idx]) != map->end() && 
            ((MAPTYPE*)map->at(tokens[idx]))->size() == 0) {
            cout<<"delete:"<<tokens[idx]<<endl;
            map->erase(map->find(tokens[idx]));
        }
    }
    return 0;
}
#ifdef SIMPLEDB_STUB
int main(int argc, char *argv[]) {
    return 0;
}
#endif
