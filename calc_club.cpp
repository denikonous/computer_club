#include "calc_club.h"

calc_club::calc_club()
{
    //
}
calc_club::~calc_club()
{
    //
}
const int ID1 = 1;
const int ID2 = 2;
const int ID3 = 3;
const int ID4 = 4;
const int ID11 = 11;
const int ID12 = 12;
const int ID13 = 13;

void calc_club::processing_of_clients(const std::vector<std::string>& clientsInfo)
{
    std::deque<std::string> waitingQueue;
    int startHours, startMinutes, endHours, endMinutes, tables, payment;
    int numtable = -1;//standard value for client wthout table
    int newMinutes = -1;//if client change table
    std::string timeOpen, timeClose;
    std::set<std::string> clientsInClub;
    std::vector<std::pair<int,int>> tableInfo;//table-minutes
    std::vector<std::pair<std::string,int>> occupiedtables;//name-table
    std::vector<std::pair<int,int>> tablesReward;//record table's reward on the one client (table-reward)
    std::vector<std::pair<int,int>> timeOfWork;//recod tables's timeOfWork in the one client (table- timeOfWork in minutes)
    std::string clientFromQueue;


    for (int i = 0; i < clientsInfo.size(); i++)
    {
       char colon;

       if(i == 0)//quantity of tables
       {
           tables = std::stoi(clientsInfo[i]);
           for(int i = 0; i < tables;i++){occupiedtables.emplace_back("Name",numtable);}
       }
       else if(i == 1)// time of open and close
       {
           std::istringstream time(clientsInfo[i]);
           time >> timeOpen >> timeClose;
           std::istringstream timeStreamS(timeOpen);
           std::istringstream timeStreamE(timeClose);
           timeStreamS >> startHours >> colon >> startMinutes;
           timeStreamE >> endHours >> colon >> endMinutes;
       }
       else if(i == 2)//payment
       {
           payment = std::stoi(clientsInfo[i]);
       }
       else if(i>2)//events
       {
           if(i == 3)
           {
             std::cout <<  timeOpen << std::endl;
           }
           std::istringstream clientStream(clientsInfo[i]);
           std::string time,name;
           int hours, minutes, identif;
           clientStream >> time >> identif >> name;
           if(clientStream >> numtable)//if we have number of table in string
           {
//                std::cout << numtable << std::endl;
           }else{numtable = -1;}
           std::istringstream timeStream(time);
           timeStream >> hours >> colon >> minutes;

           //checking open time
           if((startHours > hours || ((startHours == hours) && startMinutes > minutes))&& identif == 1)
           {
              std::cout << time << " " << identif << " " << name << std::endl;
              std::cout << time << " " << ID13 << " " << " NotOpenYet"<< std::endl;
           }
           else if(((endHours < hours) || ( endHours == hours && minutes > endMinutes)) && identif == 1)
           {
              std::cout << time << " " << identif << " " << name << std::endl;
              std::cout << time << " " << ID13 << " " << " NotOpenYet"<< std::endl;
           }
           else
           {
              if((clientsInClub.find(name)  != clientsInClub.end()) && identif == 1)
              {
                  std::cout << time << " " << identif << " " << name << std::endl;
                  std::cout << time << " " << identif << " " << "YouShallNotPass"<< std::endl;
              }
              else if((clientsInClub.find(name)  == clientsInClub.end()))
              {
                  clientsInClub.insert(name);
              }

              auto it = std::find(waitingQueue.begin(), waitingQueue.end(), name);
              if(it == waitingQueue.end() && identif == ID1)//add new client in end of deque
              {
                  waitingQueue.push_back(name);
              }
               //clients sit down on his workplaces or gameplaces
              if(identif == ID2)
              {
                  if(clientsInClub.find(name) == clientsInClub.end())//unknown client
                  {
                      std::cout << time << " " << identif << " " << name << std::endl;
                      std::cout << time << " "<<ID13 << " " << "ClientUnknown" << std::endl;
                  }
                  else if(numtable>=0 && numtable <= tables)//checking on table
                  {
                      for (int i = 0; i < occupiedtables.size(); i++)
                      {
                               //table occuppied
                              if (occupiedtables.at(i).second != -1 && occupiedtables.at(i).second == numtable)
                              {
                                  std::cout << time << " " << identif << " " << name  << " " << numtable<< std::endl;
                                  std::cout << time << " " << ID13<< " PlaceIsBusy "  << std::endl;
                                  break;
                              }
                              else
                              {     //if client doesnot sit on the table -- delete from queue and write his data
                                  if(numtable != -1 && occupiedtables.at(i).second == -1){
                                      waitingQueue.erase(waitingQueue.begin() + i);
                                      occupiedtables.at(i).first = name;
                                      occupiedtables.at(i).second = numtable;
                                      tableInfo.emplace_back(numtable, hours*60 + minutes);
                                      std::cout << time << " " << identif << " " << name << " " << numtable  << std::endl;
                                      break;
                                  }
                              }
                      }
                  }

              }


              if(identif == ID3 )//client waiting for free place
              {// if we have free places
                  for(int i = 0; i < occupiedtables.size(); i++)
                  {
                      if(occupiedtables.at(i).second == -1)
                      {
                       std::cout << time << " " << identif << " " << name << std::endl;
                        std::cout <<time << " " <<ID13 << " ICanWaitNoLonger" << std::endl;
                      }
                      break;
                  }// if queue longer that amount of tables
                  if(waitingQueue.size() > tables)
                  {
                      waitingQueue.pop_back();
                      std::cout << time << " " << ID11 << " " << name << std::endl;
                  }
                  else{std::cout << time << " " << identif << " " << name << std::endl;}

              }
              //client go out from club
              if(identif == ID4 || (clientsInfo.size() -1 -i)==0)
              {
                  if(clientsInClub.find(name) != clientsInClub.end())
                  {
                      int tmp_place = 0;
                      int deleteClientQueue = 0;
                      int table_tup =0;
                      int minutes_tup = 0;
                      int totalMinutes = 0;
                      std::string tableName;
                      clientsInClub.erase(name);
                      std::cout << time << " " << identif << " " << name << std::endl;


                      for(int j = 0; j < tableInfo.size();j++)
                      {
                          table_tup = tableInfo.at(j).first;
                          minutes_tup = tableInfo.at(j).second;

                          if(occupiedtables.at(j).first == name)//set table free
                          {
                              tableName = occupiedtables.at(j).first;//table that we set free
                              tmp_place = occupiedtables.at(j).second;
                              occupiedtables.at(j).second = -1;
                              totalMinutes = hours*60 + minutes;

                              if(occupiedtables.at(j).first != clientFromQueue)
                              {
                                totalMinutes = totalMinutes -  minutes_tup;
                              }
                              else
                              {
                                  totalMinutes = totalMinutes -  newMinutes;
                                  newMinutes = -1;
                              }
                              countMoney(totalMinutes,table_tup,payment,tablesReward,timeOfWork);


                          }
                          if(occupiedtables.at(j).first == tableName)//add client from queue
                          {
                              if(!waitingQueue.empty() && deleteClientQueue == 0)
                              {
                                  deleteClientQueue++;
                                  for(const auto& newClient : waitingQueue)
                                  {
                                    occupiedtables.at(j).first = newClient;
                                    tableInfo.at(j).second = 60*hours + minutes;
                                    clientFromQueue = newClient;
                                    waitingQueue.pop_front();
                                    break;
                                  }
                                  newMinutes = hours*60 + minutes;
                                  occupiedtables.at(j).second = tmp_place;
                                  std::cout << time << " " << ID12 <<" " << occupiedtables.at(j).first << " " << occupiedtables.at(j).second << std::endl;

                              }
                          }
                      }
                          //checking, wthere vector clientsInClub is empty, or indeed after closing in clubs remains clients
                          if(!clientsInClub.empty() && tmp_place != -1 && (clientsInfo.size() -1 -i)==0 )
                          {
                              int lastPlaces, lastMinutes;
                              for(auto& client : clientsInClub)
                              {
                                  for(int m=0; m< occupiedtables.size(); m++)
                                  {
                                      if(occupiedtables.at(m).first == client)
                                      {
                                          lastPlaces = occupiedtables.at(m).second;//update place
                                          lastMinutes = tableInfo.at(m).second;//update minutes
                                      }
                                  }
                                  clientsInClub.erase(client);
                                  totalMinutes = endHours*60 + endMinutes;
                                  totalMinutes -=lastMinutes;
                                  countMoney(totalMinutes,lastPlaces,payment,tablesReward,timeOfWork);
                                  std::cout << timeClose << " " <<ID11 << " " << client << std::endl;
                              }
                          }
                  }
                  else if(clientsInClub.find(name) == clientsInClub.end())
                  {
                      std::cout << time << " "<<ID13 << " " << "ClientUnknown" << std::endl;
                  }

              }
              else//ordinary event
              {
                  if(identif != ID2 && identif != ID3)
                      std::cout << time << " " << identif << " " << name << " "  << std::endl;
             }
           }
       }
   }


    std::cout << timeClose  << std::endl;//time of close (output)
    std::vector<std::pair<int,int>> resultReward;//recorded normalized tables' reward: numTable-totalePayment
    std::vector<std::pair<int,int>> resultTime;//recorded normalized tables' time of work: table-totalMinutes
    resultReward = normalize_results(tablesReward, occupiedtables.size());//connection toatlPayment from client1 and client2 for one table, for example
    resultTime   = normalize_results(timeOfWork, occupiedtables.size());
    print_day_results(resultReward, resultTime);
}
void calc_club::countMoney(const int& totalMinutes,int& table_tup, const int& payment, std::vector<std::pair<int,int>>& tablesReward, std::vector<std::pair<int,int>>& timeOfWork)
{
    int totalTime = (totalMinutes/60 + (totalMinutes % 60 > 0 ? 1 : 0));//round to integer
    tablesReward.emplace_back(table_tup, totalTime*payment);
    timeOfWork.emplace_back(table_tup,totalMinutes);

}
std::vector<std::pair<int,int>> calc_club::normalize_results(std::vector<std::pair<int,int>>& tablesData,
                                                             const int& normSize)
{
    std::vector<std::pair<int,int>> resultData;
    std::map<int, int> sumData;
    for(int j = 0; j < normSize; j++){
        if(normSize > tablesData.size()){
            tablesData.emplace_back(-1,-1);
        }
    }
    for(const auto&  p:tablesData)
    {
        int table = p.first;
        int data = p.second;
        if(p.first < 0)
        {
            continue;
        }

        sumData[table] += data;
//        std::cout << table << "," << data << std::endl;

    }
    for(int j =1; j<=tablesData.size(); j++)
    {

        resultData.emplace_back(j, sumData[j]);
        if(j >= normSize)
            break;
    }
    return resultData;
}
void calc_club::print_day_results(const std::vector<std::pair<int,int>>& resultReward,
                                  const std::vector<std::pair<int,int>>& resultTime) const
{
    for(int i =0; i < resultTime.size(); i++)// conlusion of the day (output)
    {
        std::cout << resultReward.at(i).first << " " << resultReward.at(i).second << " ";
        int payHours = resultTime.at(i).second / 60;
        int payMinutes = resultTime.at(i).second % 60;
        if((payMinutes <10 && payMinutes >= 0) && (payHours <10 && payHours >= 0))
        {
            std::cout <<  "0"<<payHours << ":" <<"0" << payMinutes  << std::endl;
        }
        else if((payHours <10 && payHours >= 0))
        {
            std::cout << "0" << payHours << ":" << payMinutes << std::endl;
        }
        else if(payMinutes <10 && payMinutes >= 0)
        {
            std::cout << payHours << ":" <<"0" << payMinutes  << std::endl;
        }

        else
        {
            std::cout <<  payHours << ":" << payMinutes  << std::endl;
        }

    }
}
