//Includes
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <algorithm>

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
        std::cout << command << std::endl;

        // Check for exit command
        if (command == "exit") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }

        // Process the entered command
    }



    return 0;
}