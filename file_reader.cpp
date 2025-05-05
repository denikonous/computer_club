#include "file_reader.h"

file_reader::file_reader()
{
    //
}
file_reader::~file_reader()
{
    //
}

bool file_reader::validTime(const std::string& time)
{
    std::regex timePattern("([01][0-9]|2[0-3]):[0-5][0-9]");
    return  std::regex_match(time, timePattern);
}
bool file_reader::validClient(const std::string& client)
{
    std::regex clientPattern("[a-z0-9-_]+");
    return std::regex_match(client, clientPattern);

}
bool file_reader::validId(const std::string& ident)
{
    int id;
    std::istringstream stream(ident);
    return (stream >> id) && (id > 0);
}
 bool file_reader::compareTimes(const std::string& time1, const std::string& time2)
{
    int hours1, hours2, minutes1, minutes2;
    char colon;

    std::istringstream stream1(time1);
    stream1 >> hours1 >> colon >> minutes1;
    std::istringstream stream2(time2);
    stream2 >> hours2 >> colon >> minutes2;
    if(hours1 != hours2)
        return hours1 < hours2;
    return  minutes1 < minutes2;

}

std::vector<std::string> file_reader::read(const std::string& input)
{

    std::ifstream inputdata(input);
    std::string line;
    int tables,payment;
    std::vector<std::string> error{"-1"};
    std::vector<std::string> lines;
    if(inputdata.is_open())
    {

        while (std::getline(inputdata, line))
        {
            lines.push_back(line);
        }
        inputdata.close();
    }
        else
        {
            std::cerr << "Fatal error! Please, try again!" << std::endl;
            return error;
        }

        // checkig for neccessary strings
        if(lines.size() < 3)
        {
            std::cerr << "The file does not contain neccessary information" << std::endl;
            return error;
        }
        std::istringstream stream(lines[1]);
        std::string startTime, endTime;
        // checking for format first string
        if(!(std::istringstream(lines[0]) >> tables) || tables <= 0)
        {
            std::cerr << "Error in quantity of tables (1): " << lines[0] << std::endl;
            return error;
        }
        else if(!(stream >> startTime >> endTime) || !validTime(startTime) || !validTime(endTime))
        {
            std::cerr << "Error in time format (2): " << lines[1] << std::endl;
            return error;
        }
        else if(!(std::istringstream(lines[2]) >> payment) || payment <= 0)
        {
            std::cerr << "Error in quantity of payment (3): " << lines[2] << std::endl;
            return error;
        }
        std::string prevTime = "00:00";
        //checking remaining strings
        for (int i = 3; i < lines.size(); i++)
        {
            stream.clear();
            stream.str(lines[i]);
            std::string time, ident, client, nTime, extra;
            int numtable;
            if(!(stream >> time >> ident >> client ) || !validTime(time) || !validId(ident)
                                                    || !validClient(client))
            {
                std::cerr << "Error in event string " << (i + 1) << ": " << lines[i] << std::endl;
                return error;
            }
            if(ident != "2" && (stream >> extra))
            {
                std::cerr << "Error in event string " << (i + 1) << ": " << lines[i] << std::endl;
                return error;
            }
            else if((ident == "2" && stream >>numtable >> extra))
            {
                std::cerr << "Error in event string " << (i + 1) << ": " << lines[i] << std::endl;
                return error;

            }
             else if(ident == "2" && !validId(std::to_string(numtable)))
            {
                std::cerr << "Error in event string " << (i + 1) << ": " << lines[i] << std::endl;
                return error;
            }
            else if(ident == "2" && numtable > tables)
            {
                std::cerr << "Error in event string " << (i + 1) << ": " << lines[i] << std::endl;
                return error;
            }
            if(!compareTimes(prevTime, time))
            {
                std::cerr << "Error in string (sequence of time)" << i+1 << ": " << lines[i];
                return error;

            }
            prevTime = time;
        }
        return lines;

}
