using namespace std;

#include <ctime>

#define COMMCPP

#ifndef DEFINEH
#define DEFINEH
#include "Defines.h"
#endif

#ifndef ROBOTCPP
#define ROBOTCPP
#include "Robot.cpp"
#endif


class CommunicationManager{

    private:
        static CommunicationManager* instancePointer;

        Robot _connectedRobot;

        CommunicationManager(){
            cout << "Made Comms Manager at Address: " << instancePointer<< endl;
        }


    public:
        static CommunicationManager* GetInstance(){
            if( instancePointer == NULL ) {
                instancePointer = new CommunicationManager();
            }

            return instancePointer;
        }



        void ConnectRobot(){
            _connectedRobot = Robot(2);
        }


        bool IsRobotConnected(int ConnectedRobotID) {
            if(ConnectedRobotID == NULLID) {            // if checking if ANY robot is connected
                if(_connectedRobot.GetRobotID() == NULLID){     // if no robot connected
                    return false;
                } else {
                    return true;
                }
            } else {
                if(_connectedRobot.GetRobotID() == ConnectedRobotID){     // if specified robot is connected
                    return true;
                } else {
                    return false;
                }
            }
        }


//-----------------------------------------
        int GetRobotSpeed(){
            LevelValue CurrRobotSpeed = _connectedRobot.GetSpeed();
            if(CurrRobotSpeed>=LevelValue::Low && CurrRobotSpeed<=LevelValue::High){
                return CurrRobotSpeed;
            } else{
                return -1;
            }
        }

        int SetRobotSpeed(LevelValue NewSpeed){
            if(NewSpeed>=LevelValue::Low && NewSpeed<=LevelValue::High){
                _connectedRobot.SetSpeed(NewSpeed);
                return 0;
            } else{
                return -1;
            }
        }
//-----------------------------------------
        int GetRobotPower(){
            LevelValue CurrRobotPower = _connectedRobot.GetPower();
            if(CurrRobotPower>=LevelValue::Low && CurrRobotPower<=LevelValue::High){
                return CurrRobotPower;
            } else{
                return -1;
            }
        }

        int SetRobotPower(LevelValue NewPower){
            if(NewPower>=LevelValue::Low && NewPower<=LevelValue::High){
                _connectedRobot.SetPower(NewPower);
                return 0;
            } else{
                return -1;
            }
        }
//-----------------------------------------
        Statuses GetRobotStatus(){
            Statuses RobotState = _connectedRobot.GetStatus();
            if(RobotState >= Statuses::Off && RobotState <= Statuses::Error){
            return RobotState;
            } else {
                return Statuses::Error;
            }
        }

        int GetRobotBattery(){
            int BatteryPercentage = _connectedRobot.GetBatteryStatus();
            if(BatteryPercentage>=0 && BatteryPercentage <=100){
                return BatteryPercentage;
            }else{
                return -1;
            }
        }

        // Get Position???

//----------------------------------------
        AdvancedDataStruct GetRobotsAdvancedData(){
            return _connectedRobot.GetAdvancedData();
        }

        BasicDataStruct GetRobotsBasicData(){
            return _connectedRobot.GetBasicData();
        }

//----------------------------------------
        void StartManualRobotMode(){
            _connectedRobot.StartManualClean();     //Need check?
        }
        int MoveRobotForward(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
                _connectedRobot.ManualMoveForward();
                return 0;
            } else {
                return -1;
            }
        }
        int MoveRobotBackward(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.ManualMoveBackward();
                return 0;
            } else {
                return -1;
            }
        }
        int MoveRobotLeft(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.ManualMoveLeft();
                return 0;
            } else {
                return -1;
            }
        }
        int MoveRobotRight(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.ManualMoveRight();
                return 0;
            } else {
                return -1;
            }
        }
        int SendRobotHome(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.SendHome();
                return 0;
            } else {
                return -1;
            }
        }

//------------------------------------------

    std::time_t GetRobotScheduledTime(){
        return _connectedRobot.GetScheduledTime();
    }

    int SetRobotSchedule(int Hour){
        if(Hour>=0 && Hour<=23){
            std::time_t TimeSeconds = time(nullptr);
            struct std::tm *TimeInfo = localtime(&TimeSeconds);
            TimeInfo->tm_hour = Hour;
            TimeInfo->tm_min = 0;
            TimeInfo->tm_sec = 0;

            std::time_t ScheduledSeconds = mktime(TimeInfo);

            if(TimeSeconds>ScheduledSeconds){
                TimeInfo->tm_mday += 1;
                ScheduledSeconds = mktime(TimeInfo);
            }

            _connectedRobot.SetSchedule(ScheduledSeconds);
            return 0;
        } else {
            return -1;
        }

    }


};