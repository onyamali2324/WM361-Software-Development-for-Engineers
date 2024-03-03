#include <iostream>
#include<ostream>
#include <string>
#include <functional>
#include <map>

#include "CommunicationManager.cpp"

using namespace std;
class TaskManager{
    public:
        int login_check = 1;
        void TaskGetRobotSpeed(){
            if ((login_check == 1) || (login_check == 2)){
            int temp_val = CommunicationManager::GetInstance()->GetRobotSpeed();
            cout << "The current Robot Speed is" << temp_val << endl;
            } else {

            }
        };
        void TaskGetRobotPower(){
            if ((login_check == 1) || (login_check == 2)){
            int temp_val = CommunicationManager::GetInstance()->GetRobotPower();
            cout << "The current Robot Power is" << temp_val << endl;
            } else{

            }
        }
        void TaskGetRobotStatus(){
            if ((login_check == 1) || (login_check == 2)){
            Statuses temp_val = CommunicationManager::GetInstance()->GetRobotStatus();
            cout << "The current Robot Status is" << temp_val << endl;
            } else {

            }
        }
        void TaskGetRobotSpeed(){
            if ((login_check == 1) || (login_check == 2)){
            int temp_val = CommunicationManager::GetInstance()->GetRobotSpeed();
            cout << "The current Robot Speed is" << temp_val << endl;
            }else {

            }
        }
        void TaskGetRobotBattery(){
            if ((login_check == 1) || (login_check == 2)){
                int temp_val = CommunicationManager::GetInstance()->GetRobotBattery();
                cout << "The current Robot Battery is" << temp_val << endl;
            } else {

            }
        }
        void TaskGetRobotsAdvancedData(){
            if ((login_check == 1) || (login_check == 2)){
                AdvancedDataStruct temp_val = CommunicationManager::GetInstance()->GetRobotsAdvancedData();
                cout << "The robot advanced data is :" << temp_val << endl;
            } else {

            }
        }
        void TaskGetRobotsBasicData(){
            if ((login_check == 1) || (login_check == 2)){
                BasicDataStruct temp_val = CommunicationManager::GetInstance()->GetRobotsBasicData();
                cout << "The robot basic data is :" << temp_val << endl;
            }
        }
        void TaskMoveForward(){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotForward();
                }
            } else {
                
            }
        }
        void TaskMoveBackward(){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotBackward();
                }
            } else {
                
            }
        }
        void TaskMoveRight(){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotRight();
                }
            } else {
                
            }
        }
        void TaskMoveLeft(){
            if ((login_check == 1) || (login_check == 2)){
                if (CommunicationManager::GetInstance()->GetRobotStatus() != Statuses::Manual){
                    cout << "You need to be in Manual to do so !" << endl;
                } else {
                    CommunicationManager::GetInstance()->MoveRobotLeft();
                }
            } else {
                
            }
        }
};