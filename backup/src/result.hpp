#pragma once

#include <sstream>
#include <vector>

template<class T = uint8_t>
class Result {
    public:
        Result(const std::string & fileNameX, const std::string & fileNameY, const std::vector<T> & bx, const std::vector<T> & by, bool comparationResult = false);
        Result(const Result & src);
        ~Result();

        Result * Clone() const;
        void Set(const Result & src);

        bool GetResult() const;

        void AddToXBytes(T byte);
        void AddToYBytes(T byte);

        size_t GetXBytesSize() const;
        size_t GetYBytesSize() const;

        std::ostream & Print(std::ostream & os);

    private:
        std::string _fileNameX;
        std::string _fileNameY;

        bool _comparationResult;

        std::vector<T> _fileXBytes;
        std::vector<T> _fileYBytes;

        std::ostream & PrintDiffer(std::ostream & os, const std::string & first, const std::string & second, const std::vector<T> & differs);
};

template<class T>
Result<T>::Result(const std::string & fileNameX, const std::string & fileNameY, const std::vector<T> & bx, const std::vector<T> & by, bool comparationResult)
                : _fileNameX(fileNameX), _fileNameY(fileNameY),
                  _comparationResult(comparationResult), _fileXBytes(bx), _fileYBytes(by) {
    
}

template<class T>
Result<T>::Result(const Result<T> & src)
                : _fileNameX(src._fileNameX), _fileNameY(src._fileNameY),
                  _comparationResult(src._comparationResult), _fileXBytes(src._fileXBytes), _fileYBytes(src._fileYBytes) {
    
}

template<class T>
Result<T>::~Result() {

}

template<class T>
Result<T> * Result<T>::Clone() const {
    return new Result(*this);
}

template<class T>
void Result<T>::Set(const Result<T> & src) {
    if(&src == this) return;

    _comparationResult = src._comparationResult;
    _fileXBytes = src._fileXBytes;
    _fileYBytes = src._fileYBytes;
}

template<class T>
bool Result<T>::GetResult() const {
    return _comparationResult;
}

template<class T>
void Result<T>::AddToXBytes(T byte) {
    _fileXBytes.push_back(byte);
}

template<class T>
void Result<T>::AddToYBytes(T byte) {
    _fileYBytes.push_back(byte);
}

template<class T>
size_t Result<T>::GetXBytesSize() const {
    return _fileXBytes.size();
}

template<class T>
size_t Result<T>::GetYBytesSize() const {
    return _fileYBytes.size();
}

template<class T>
std::ostream & Result<T>::Print(std::ostream & os) {
    os << "--Diff Result--" << "\n";
    
    os << "Files " << _fileNameX << " and " << _fileNameY << " are" << (_comparationResult ? "" : " not") << " equal." << std::endl;
    if(_comparationResult) return os;

    PrintDiffer(os, _fileNameX, _fileNameY, _fileXBytes);
    PrintDiffer(os, _fileNameY, _fileNameX, _fileYBytes);

    return os;
}

template<class T>
std::ostream & Result<T>::PrintDiffer(std::ostream & os, const std::string & first, const std::string & second, const std::vector<T> & differs) {
    if(differs.size() == 0) return os;

    os << "Bytes in " << first << " but not in " << second << ": ";
    for(size_t i = 0; i < differs.size(); i++) os << differs[i];

    return os << std::endl;
}