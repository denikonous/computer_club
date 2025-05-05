#ifndef FILE_READER_H
#define FILE_READER_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
class file_reader
{
public:
    file_reader();
    ~file_reader();
    std::vector<std::string> read(const std::string& input);
    bool validTime(const std::string& time);
    bool validClient(const std::string& client);
    bool validId(const std::string& ident);
    bool compareTimes(const std::string& time1, const std::string& time2);
};

#endif // FILE_READER_H
