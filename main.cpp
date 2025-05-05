#include "file_reader.h"
#include "calc_club.h"

struct testCases{
    std::string input;
    int expected;
};
void startTests(const std::string& currentDir)
{
    std::string txt = ".txt";
    const int testSize = 10;
    int passed = 0;
    std::vector<testCases> tests;
    std::string fileTest;
    file_reader readTests;
    for(int iter = 1; iter <=testSize; iter++)
    {
        std::string testPath = "\\tests\\test" + std::to_string(iter) + txt;
        fileTest = currentDir + testPath;
        tests.push_back({fileTest,-1});
    }

    for (int i =0; i < tests.size(); i++)
    {
        if(std::stoi(readTests.read(tests.at(i).input)[0]) < 0)
            passed++;
        else
        {
            std::cout << "false results for " << i + 1 << " test" << std::endl;
        }
    }
    std::cout << "test passed " << passed << " of " << testSize << std::endl;
}
int main(int argc, char* argv[])
{
    if(argc >2 || argc < 2){
        std::cerr << "Incorrect quantity of input arguments! Please, check .txt file!" << std::endl;
        return 1;
    }
    int choise;
    std::cout << "Start tests: 1 - Yes, 0 - No" << std::endl;
    std::cin >> choise;
    std::string filepath = argv[1];
    std::string dir_path = __FILE__;
    size_t lastSlashPos = dir_path.find_last_of("\\");
    std::string currentDir = dir_path.substr(0, lastSlashPos);
    std::string file = currentDir +"\\" +filepath;
    file_reader reader;
    calc_club clients;
    std::vector<std::string> dataFromFile = reader.read(file);
    if(dataFromFile[0] != "-1")//error catcher
        clients.processing_of_clients(dataFromFile);
    if(choise ==1)
        startTests(currentDir);

    return 0;
}





