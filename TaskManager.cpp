#include <iostream>
#include <string>
#include <functional>
#include <map>

#include "Defines.h"
#include "Robot.cpp"
#include "CommunicationManager.cpp"

using namespace std;
class TaskManager{
    public:
        void Command(const std::string& command, Robot& robot, std::map<std::string, std::function<void(Robot&)>>& commandMap){
            auto it = commandMap.find(command);
            if (it == commandMap.end()) {
            std::cout << "Unknown command: " << command << std::endl;
        }  
    }
};