#ifndef CALC_CLUB_H
#define CALC_CLUB_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
class calc_club
{
public:
    calc_club();
    ~calc_club();
    void processing_of_clients(const std::vector<std::string>& inputData);
    std::vector<std::pair<int,int>> normalize_results(std::vector<std::pair<int,int>>& tablesData,
                                                      const int& normSize);
    void print_day_results(const std::vector<std::pair<int,int>>& resultReward,
                           const std::vector<std::pair<int,int>>& resultTime) const;
    void countMoney(const int& totalMinutes,
                    int& table_tup,
                    const int& payment,
                    std::vector<std::pair<int,int>>& tablesReward,
                    std::vector<std::pair<int,int>>& timeOfWork);
};

#endif // CALC_CLUB_H
