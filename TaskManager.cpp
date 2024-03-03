#include <iostream>
#include<ostream>
#include <string>
#include <functional>
#include <map>
#include <fstream>
#include <sstream>

#include "CommunicationManager.cpp"

using namespace std;
class TaskManager{
    public:
        std::map<std::string, std::string> LoginPrompt(){
        std::cout << "Please enter your User ID:" <<std::endl;
        std::string User;
        std::getline(std::cin, User);
        std::cout << "Please enter your password:" <<std::endl;
        std::string Pwd;
        std::getline(std::cin, Pwd);
        std::map<std::string, std::string> entered_logins = {
            {User,Pwd}
        };
        return entered_logins;
}
        int login_checker(std::map<std::string, std::string> entered_logins){
                std::map<std::string, std::string> userPasswordMap;

    // Open the file
    std::ifstream inputFile("logins.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1; // Return an error code
    }

    // Read each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string username, password;

        // Split the line into username and password
        if (std::getline(iss, username, ',') && std::getline(iss, password, ',')) {
            // Store the pair in the map
        password.erase(std::remove_if(password.begin(), password.end(), [](char c) { return !std::isalpha(c); }),password.end());
            userPasswordMap[username] = password;
        } else {
            std::cerr << "Invalid format in line: " << line << std::endl;
        }
    }

    // Close the file
    inputFile.close();
            auto it = userPasswordMap.find(entered_logins.begin()->first);
            if (it != userPasswordMap.end()) {
            // Username found, now check if the password matches
            if (it->second == entered_logins.begin()->second) {
            std::cout << "Login successful!" << std::endl;
            if (entered_logins.begin()->first=="user"){
                return 0;
            } else if (entered_logins.begin()->first=="owner"){
                return 1;
            } else if (entered_logins.begin()->first=="admin"){
                return 2;
            }
            }else {
            std::cout << "Incorrect password." << std::endl;

            }
        } else {
        std::cout << "Username not found." << std::endl;
        }
        return -1;
}
        void TaskGetRobotSpeed(int login_check){
            if ((login_check == 1) || (login_check == 2)){
            int temp_val = CommunicationManager::GetInstance()->GetRobotSpeed();
            cout << "The current Robot Speed is" << temp_val << endl;
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        };
        void TaskGetRobotPower(int login_check){
            if ((login_check == 1) || (login_check == 2)){
            int temp_val = CommunicationManager::GetInstance()->GetRobotPower();
            cout << "The current Robot Power is" << temp_val << endl;
            } else{
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskGetRobotStatus(int login_check){
            if ((login_check == 1) || (login_check == 2)){
            Statuses temp_val = CommunicationManager::GetInstance()->GetRobotStatus();
            cout << "The current Robot Status is" << temp_val << endl;
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskGetRobotBattery(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                int temp_val = CommunicationManager::GetInstance()->GetRobotBattery();
                cout << "The current Robot Battery is" << temp_val << endl;
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskGetRobotSchedule(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                std::time_t temp_val = CommunicationManager::GetInstance()->GetRobotScheduledTime();
                cout << "The Scheduled Cleaning Time is :" << temp_val << endl;
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskGetRobotsAdvancedData(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                AdvancedDataStruct temp_val = CommunicationManager::GetInstance()->GetRobotsAdvancedData();
                cout << "The robot advanced data is :" << temp_val << endl;
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskGetRobotsBasicData(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                BasicDataStruct temp_val = CommunicationManager::GetInstance()->GetRobotsBasicData();
                cout << "The robot basic data is :" << temp_val << endl;
            }else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskMoveForward(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotForward();
                }
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskMoveBackward(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotBackward();
                }
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskMoveRight(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotRight();
                }
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskMoveLeft(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotLeft();
                }
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskSetRobotSpeed(int login_check, LevelValue speed){
            if ((login_check == 1) || (login_check == 2)){
                CommunicationManager::GetInstance()->SetRobotSpeed(speed);
                cout << "The new Speed is:" << speed << endl;
            }else {
                 cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskSetRobotPower(int login_check, LevelValue power){
            if ((login_check == 1) || (login_check == 2)){
                CommunicationManager::GetInstance()->SetRobotPower(power);
                cout << "The new Power is:" << power << endl;
            }else {
                 cout << "You do not have the right to do this action" << endl;
            }
        }
        void TaskSetRobotSchedule(int login_check, int hour){
            if ((login_check == 1) || (login_check == 2)){
                CommunicationManager::GetInstance()->SetRobotSchedule(hour);
                cout << "The Scheduled Cleaning time is:" << hour << "h" << endl;
            }else {
                 cout << "You do not have the right to do this action" << endl;
            }
        }

        void TaskSetManual(int login_check){
            if ((login_check == 1) || (login_check == 2)){
                if ((CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Auto)&&(CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Off)&&(CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Scheduled)){
                    cout << "In order to set the Robot to Manual Mode it has to be in Scheduled, Off or Auto." << endl;
                } else {
                    CommunicationManager::GetInstance()->StartManualRobotMode();
                    cout << "The robot is now in manual mode" << endl;
                }    
            } else {
                cout << "You do not have the right to do this action" << endl;
            }
        }

        
};