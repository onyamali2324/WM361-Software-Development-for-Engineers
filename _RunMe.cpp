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
    std::map<std::string, std::string> entered_logs = Tasking.LoginPrompt();
    int login_check = Tasking.login_checker(entered_logs);
    if (login_check == -1){return 0;}
    std::map<std::string, std::function<void()>> commandMapGet = {
    {"getrobotspeed",[&Tasking, login_check]() {Tasking.TaskGetRobotSpeed(login_check);}},
    {"getrobotbattery", [&Tasking, login_check]() {Tasking.TaskGetRobotBattery(login_check);}},
    {"getrobotpower",[&Tasking, login_check]() { Tasking.TaskGetRobotPower(login_check);}},
    {"getadvanceddata",[&Tasking, login_check]() {Tasking.TaskGetRobotsAdvancedData(login_check);}},
    {"getbasicdata",[&Tasking, login_check]() {Tasking.TaskGetRobotsBasicData(login_check);}},
    {"getrobotstatus",[&Tasking, login_check]() {Tasking.TaskGetRobotStatus(login_check);}},
    {"w",[&Tasking, login_check]() {Tasking.TaskMoveForward(login_check);}},
    {"a",[&Tasking, login_check]() {Tasking.TaskMoveLeft(login_check);}},
    {"s",[&Tasking, login_check]() {Tasking.TaskMoveBackward(login_check);}},
    {"d",[&Tasking, login_check]() {Tasking.TaskMoveRight(login_check);}}
    };

    std::string command;
    while (true) {
        std::cout << "> ";  // Command prompt
        std::getline(std::cin, command);

        transform(command.begin(), command.end(), command.begin(), ::tolower);
        // Check for exit command
        if (command == "exit") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }

        std::istringstream iss(command);
        std::string part1;
        std::string part2;

        // Extract the command and argument
        iss >> part1 >> part2;

if (!iss.fail()) {
    // if there is 2 items, then it must be a set command
    if (part1 == "setrobotspeed") {
        Tasking.TaskSetRobotSpeed(login_check, stringToLevel(part2));
    } else if (part1 == "setrobotpower") {
        Tasking.TaskSetRobotPower(login_check,stringToLevel(part2));
    } else if (part1 == "setrobotschedule") {
        try {
            Tasking.TaskSetRobotSchedule(login_check,std::stoi(part2));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Argument has to be an integer" << std::endl;
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

    }
return 0;
}