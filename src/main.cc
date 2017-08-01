#include <simpledb.h>
#include <cstring>
using namespace std;

mutex    mtx;
typedef int (*FUNCP)(SimpleDB*, vector<string>& tokens, vector<string>& paths);
int select_and_display (SimpleDB* db, vector<string>& tokens, vector<string>& paths) {
    db->read_path(paths);
    return 0;
}

int create_path (SimpleDB* db, vector<string>& tokens, vector<string>& paths) {
    db->create_path(paths);
    return 0;
}

int read_path (SimpleDB* db, vector<string>& tokens, vector<string>& paths) {
    if (db->read_path(paths) == -1) {
        cout<<"unable to read path"<<endl;
    }
    return 0;
}

int update_path (SimpleDB* db, vector<string>& tokens, vector<string>& paths) {
    uint32_t pos = tokens[1].find("=");
    //cout<<tokens[1].substr(pos+1)<<endl;
    string value = tokens[1].substr(pos+1);
    cout<<"VALUE:"<<value<<endl;
    db->update_path(paths, value);
    return 0;
}

int delete_path (SimpleDB* db, vector<string>& tokens, vector<string>& paths) {
    db->delete_path(paths);
    return 0;
}

void show_version(SimpleDB* db) {
    db->show_version();
}

int client_exit() {
    exit(0);
}

int process (SimpleDB *db, string s) {
    map<string, FUNCP> map;
    istringstream ss(s);
    vector<string> tokens;
    copy(istream_iterator<string>(ss),
         istream_iterator<string>(),
         back_inserter(tokens));
    map["cd"] = select_and_display;
    map["ls"] = read_path;
    map["+"] = create_path;
    map["-"] = delete_path;
    map["!"] = update_path;
    if (map.find(tokens.front()) != map.end()) {
        vector<string> paths;
        size_t pos = 0, equal_pos = tokens[1].find("=");
        string tok;
        while ((pos = tokens[1].find("/")) != string::npos) {
            tok = tokens[1].substr(0, pos);
            cout<<"path:"<<tok<<endl;
            paths.push_back(tok);
            tokens[1].erase(0, pos + 1);
        }

        tok = tokens[1].substr(0, pos);
        if ((pos = tok.find("=")) != string::npos) {
            cout<<"path:"<<tok.substr(0, pos)<<endl;;
            paths.push_back(tok.substr(0, pos));
        } else {
            cout<<"path:"<<tok<<endl;
            paths.push_back(tok);
        }
        for (int idx=0;idx<paths.size();idx++) {
            cout<<paths[idx]<<endl;
        }
        map[tokens.front()](db, tokens, paths);
    } else {
        if (tokens.front() == "version") {
            show_version(db);
        }
    }
    cout<<endl;
    return 0;
}

void read_from_command(SimpleDB *db, uint32_t idx) {
    while (true) {
        string line;
        mtx.lock();
        getline(cin, line);
        if (line != "") { 
            //cout<<idx<<" "<<line<<endl;
            process(db, line);
        }
        mtx.unlock();
    }
}

#define DEFAULT_CLIENTS 5
int main(int argc, char* argv[]) {
    vector<thread*>  clients;
    SimpleDB        *db = new SimpleDB();
    
    if (strncmp(argv[0], "-d", 2) == 0) {
    }
    for (int idx=0;idx<DEFAULT_CLIENTS;idx++) {
        clients.push_back(new thread(read_from_command, db, idx));
    }
    for_each(clients.begin(), clients.end(), mem_fn(&thread::join));
    return 0;
}
