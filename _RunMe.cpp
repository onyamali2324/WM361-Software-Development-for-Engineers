//Includes
#include <iostream>
#include <string>
#include <functional>
#include <map>

#ifndef DEFINEH
#define DEFINEH
#include "Defines.h"
#include "Robot.cpp"
#include "CommunicationManager.cpp"
#endif



//Variables

CommunicationManager* CommunicationManager::instancePointer = NULL;

//using namespace std;

void WelcomeMessage (){
    
    std::cout << "\\                          / ________             ________  ________   ___      ___   ________   "   <<std:: endl;
    std::cout << " \\                        / |          |         |         |        | |   \\    /   | |          "    << std::endl;
    std::cout << "  \\          __          /  |          |         |         |        | |    \\  /    | |          "    << std::endl;
    std::cout << "   \\        /  \\        /   |_____     |         |         |        | |     \\/     | |_____     "   << std::endl;
    std::cout << "    \\      /    \\      /    |          |         |         |        | |            | |          "    << std::endl;
    std::cout << "     \\    /      \\    /     |          |         |         |        | |            | |          "    << std::endl;
    std::cout << "      \\__/        \\__/      |________  |________ |________ |________| |            | |________  "    << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------"       << std::endl;
}

int LoginPrompt(){
    std::cout << "Please enter your User ID:" <<std::endl;
    std::string User;
    std::getline(std::cin, User);

    std::cout << User << std::endl;

 

    return 0;
}

void Command(const std::string& command, Robot& robot, std::map<std::string, std::function<void(Robot&, const std::string&)>>& commandMap) {
    auto it = commandMap.find(command);
    if (it != commandMap.end()) {
        it->second(robot, "some_argument"); // You can pass additional arguments here
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

int main(){

    CommunicationManager::GetInstance()->ConnectRobot();

    bool IsConnected = CommunicationManager::GetInstance()->IsRobotConnected(2);
    Robot ConnectedRobot;
    std::cout << IsConnected << std::endl;

    WelcomeMessage();
    std::map<std::string, std::function<void(Robot&, const std::string&)>> commandMap = {
    {"GetBatteryStatus", &Robot::GetBatteryStatus},
    {"GetRecentCleaningTime", &Robot::GetRecentCleaningTime}
    // Populate with rest of commands

    };

    //LoginPrompt();
    std::string command;
    while (true) {
        std::cout << "> ";  // Command prompt
        std::getline(std::cin, command);

        // Check for exit command
        if (command == "exit") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }

        // Process the entered command
        Command(command,ConnectedRobot,commandMap);
    }



    return 0;
}