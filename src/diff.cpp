#include "diff.hpp"

// Diff
Diff::Diff(const File & firstFile, const File &secondFile) : _first(firstFile.Clone()), _second(secondFile.Clone()) {
    _first->Load();
    _second->Load();
}

Diff::Diff(const Diff & src) {
    if(&src == this) return;

    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;

    _first = src._first->Clone();
    _second = src._second->Clone();
}

Diff::~Diff() {
    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;
}

bool Diff::Compare() {
    return true;
}

Diff & Diff::operator=(const Diff & src) {
    if(&src == this) return *this;

    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;

    _first = src._first->Clone();
    _second = src._second->Clone();

    return *this;
}

std::ostream & operator<<(std::ostream & os, const Diff & src) {
    os << "--General Diff--" << std::endl;
    os << "File 1: " << src._first << std::endl;
    os << "File 2: " << src._second;

    return os;
}

// Binary Diff
BinDiff::BinDiff(const File & firstFile, const File & secondFile) : Diff(firstFile, secondFile) {

}

BinDiff::BinDiff(const BinDiff & src) : Diff(src)  {
    if(&src == this);
}

BinDiff::~BinDiff() {

}

bool BinDiff::Compare() {
    std::vector<uint8_t> bytesX = _first->GetBinary();
    std::vector<uint8_t> bytesY = _second->GetBinary();

    if(bytesX.size() != bytesY.size()) return false;
    for(size_t i = 0; i < bytesX.size(); i++) {
        std::cout << "cmp: " << (int)bytesX[i] << " ?? " << (int)bytesY[i] << std::endl;
        if(bytesX[i] != bytesY[i]) return false;
    }

    return true;
}   

std::ostream & operator<<(std::ostream & os, const BinDiff & src) {
    os << "--Binary Diff--" << std::endl;
    os << "File 1: " << *src._first << std::endl;
    os << "File 2: " << *src._second;

    return os;
}

// Txt Diff
TxtDiff::TxtDiff(const File & firstFile, const File & secondFile) : Diff(firstFile, secondFile) {

}

TxtDiff::TxtDiff(const TxtDiff & src) :Diff(src)  {
    if(&src == this);
}

TxtDiff::~TxtDiff() {

}

bool TxtDiff::Compare() {
    std::vector<char> charsX = _first->GetText();
    std::vector<char> charsY = _second->GetText();

    if(charsX.size() != charsY.size()) return false;
    for(size_t i = 0; i < charsX.size(); i++) {
        std::cout << "cmp: " << charsX[i] << " ?? " << charsY[i] << std::endl;
        if(charsX[i] != charsY[i]) return false;
    }

    return true;
}   

std::ostream & operator<<(std::ostream & os, const TxtDiff & src) {
    os << "--Txt Diff--" << std::endl;
    os << "File 1: " << *src._first << std::endl;
    os << "File 2: " << *src._second;

    return os;
}

// Json Diff
JsnDiff::JsnDiff(const File & firstFile, const File & secondFile) : Diff(firstFile, secondFile)  {

}

JsnDiff::JsnDiff(const JsnDiff & src) : Diff(src) {
    if(&src == this) return;
}

JsnDiff::~JsnDiff() {

}

bool JsnDiff::Compare() {
    return true;
}   

std::ostream & operator<<(std::ostream & os, const JsnDiff & src) {
    os << "--JSON Diff--" << std::endl;
    os << "File 1: " << *src._first << std::endl;
    os << "File 2: " << *src._second;

    return os;
}