//Includes
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <sstream>

#ifndef DEFINEH
#define DEFINEH
#include "Defines.h"
//#include "Robot.cpp"
//#include "CommunicationManager.cpp"
#include "TaskManager.cpp"
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
LevelValue stringToLevel(const std::string& LevelStr) {
    if (LevelStr == "low") {
        return Low;
    } else if (LevelStr == "medium") {
        return Medium;
    } else if (LevelStr == "high") {
        return High;
    } else {
        // Handle the case when the string is not recognized
        std::cerr << "Unknown LevelValue: " << LevelStr << std::endl;
    return Medium;
    }
}

int main(){

    CommunicationManager::GetInstance()->ConnectRobot();

    bool IsConnected = CommunicationManager::GetInstance()->IsRobotConnected(2);
    Robot ConnectedRobot;
    std::cout << IsConnected << std::endl;
    TaskManager Tasking;
    WelcomeMessage();
    std::map<std::string, std::function<void()>> commandMapGet = {
    {"getrobotspeed",[&Tasking]() {Tasking.TaskGetRobotSpeed();}},
    {"getrobotbattery", [&Tasking]() {Tasking.TaskGetRobotBattery();}},
    {"getrobotpower",[&Tasking]() { Tasking.TaskGetRobotPower();}},
    {"getadvanceddata",[&Tasking]() {Tasking.TaskGetRobotsAdvancedData();}},
    {"getbasicdata",[&Tasking]() {Tasking.TaskGetRobotsBasicData();}},
    {"getrobotstatus",[&Tasking]() {Tasking.TaskGetRobotStatus();}},
    {"w",[&Tasking]() {Tasking.TaskMoveForward();}},
    {"a",[&Tasking]() {Tasking.TaskMoveLeft();}},
    {"s",[&Tasking]() {Tasking.TaskMoveBackward();}},
    {"d",[&Tasking]() {Tasking.TaskMoveRight();}}
    };

    //LoginPrompt();
    std::string command;
    while (true) {
        std::cout << "> ";  // Command prompt
        std::getline(std::cin, command);

        transform(command.begin(), command.end(), command.begin(), ::tolower); 

        std::istringstream iss(command);
        std::string part1;
        std::string part2;

        // Extract the command and argument
        iss >> part1 >> part2;

if (!iss.fail()) {
    // if there is 2 items, then it must be a set command
    if (part1 == "setrobotspeed") {
        Tasking.TaskSetRobotSpeed(stringToLevel(part2));
    } else if (part1 == "setrobotpower") {
        Tasking.TaskSetRobotPower(stringToLevel(part2));
    } else if (part1 == "setrobotschedule") {
        try {
            Tasking.TaskSetRobotSchedule(std::stoi(part2));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Argument is not an int" << std::endl;
        }
    }
} else {
    // There was no argument, has to be a get function
    auto it = commandMapGet.find(command);
    if (it != commandMapGet.end()) {
        // If the method is found, invoke it
        it->second();
    } else {
        std::cout << "Method not found: " << command << std::endl;
    }
}
        // Check for exit command
        if (command == "exit") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }
    }
return 0;
}