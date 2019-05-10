#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"
#include "folder.hpp"
#include "io.hpp"

using namespace std;

bool lineCmpIncase(const string & ll, const string & lr) {
    if(ll.size() != lr.size()) return false;
    for(size_t i = 0; i < ll.size(); i++) {
        if(toupper(ll[i]) != toupper(lr[i])) {
            return false;
        }
    }
    return true;
}

bool compareIgnored(const string & ll, const string & lr) {

    const char * l = ll.c_str();
    const char * r = lr.c_str();

    while (true) {
        while (*l != '\0' && isspace((unsigned char)*l)) l++;
        while (*r != '\0' && isspace((unsigned char)*r)) r++;
        if (*l == '\0' || *r == '\0') {
          return (*r == '\0') - (*l == '\0') == 0;
        }
        if (*l != *r) {
          return (unsigned char)*r - (unsigned char)*l == 0;
        }
        l++;
        r++;
    }

    return 0;
}

bool compareIgnCaseIns(const string & ll, const string & lr) {
    const char * l = ll.c_str();
    const char * r = lr.c_str();

    while (true) {
        while (*l != '\0' && isspace((unsigned char)*l)) l++;
        while (*r != '\0' && isspace((unsigned char)*r)) r++;
        if (*l == '\0' || *r == '\0') {
          return (*r == '\0') - (*l == '\0') == 0;
        }
        if (toupper(*l) != toupper(*r)) {
          return (unsigned char)*r - (unsigned char)*l == 0;
        }
        l++;
        r++;
    }
}

bool lineCmpWthIgnCaseIns(const string & ll, const string & lr) {
    int r = compareIgnCaseIns(ll, lr);
    if(r == 0) return true;
    return false;
}

bool lineCmpWhtIgn(const string & ll, const string & lr) {
    int r = compareIgnored(ll, lr);
    if(r == 0) return true;
    return false;
}

bool charCmp(char x, char y) {
    return toupper(x) == toupper(y); 
}

int CompareType = -1;
bool DifferentTypes = false;

bool caseInsensitive = false;
bool ignoreWhitespace = false;

int main(int argc, char * argv[]) {       
        if(argc <= 2) {
        cout << "Invalid number of arguments!" << endl;
        return 1;
    }

    vector<File *> files;
    vector<Folder *> folders;
    
    size_t i = 0;
    for(i = 1; i < (size_t)argc && i < 3; i++) {
        string current(argv[i]);
        
        File * file = CreateFile(current);
        if(file != NULL) {
            files.push_back(file);
            continue;
        }

        Folder * folder = CreateFolder(current);
        if(file != NULL) {
            folders.push_back(folder);
            continue;
        }

        cout << "Error: Can't load " << argv[i] << ". Are you sure, it's a corrent path?" << endl;

        for(auto f : files) delete f;
        for(auto f : folders) delete f;

        return 1;   
    }

    for(i = i; i < (size_t)argc; i++) {
        if(string(argv[i]) == "-i") {
            //cout << "switched to case insenstivite comparison" << endl;
            ignoreWhitespace = true;
        }
        else if(string(argv[i]) == "-c") {
            //cout << "switched to case insenstivite comparison" << endl;
            caseInsensitive = true;
        }
        else {
            cout << "Invalid argument: " << argv[i] << ", possible arguments: -c: case insensitive, -i: ignore whitespace" << endl;

            for(auto f : files) delete f;
            for(auto f : folders) delete f;

            return 1;
        }
    }

    //cout << "CompareType: " << CompareType << " // 0:bin, 1:txt, 2:jsn" << endl;
    //cout << "DifferentTypes: " << boolalpha << DifferentTypes << endl;

    Diff * diff = NULL;
    if(files.size() == 2)
    {
        /*
        switch(CompareType)
        {
            case 0:
                diff = new BinDiff(*files[0], *files[1]);
                break;
            case 1:
                diff = new TxtDiff(*files[0], *files[1]);
                break;
            case 2:
                diff = new JsnDiff(*files[0], *files[1]);
                break;
        }*/

        diff = CreateDiff(files[0], files[1]);
        if(diff == NULL) return 1;

        bool (*func)(const string &, const string &) = NULL;
        if(caseInsensitive && ignoreWhitespace) {
            func = compareIgnCaseIns;
        }
        else if(caseInsensitive) {
            func = lineCmpIncase;
        }
        else if(ignoreWhitespace) {
            func = compareIgnored;
        }

        auto result = diff->Compare(func); 
        result->Print(cout, true);
        delete result;
    }

    for(size_t i = 0; i < files.size(); i++) {
        delete files[i];
    }
    for(size_t i = 0; i < folders.size(); i++) {
        delete folders[i];
    }
    if(diff != NULL) delete diff;

    return 0;

    return 0;
}
