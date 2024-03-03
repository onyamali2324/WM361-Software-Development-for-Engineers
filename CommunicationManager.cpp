using namespace std;

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
            //cout << "Made Comms Manager at Address: " << instancePointer<< endl;
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

        void MoveRobotForward(){
            _connectedRobot.ManualMoveForward();
        }
        void MoveRobotBackward(){
            _connectedRobot.ManualMoveBackward();            
        }
        void MoveRobotLeft(){
            _connectedRobot.ManualMoveLeft();            
        }
        void MoveRobotRight(){
            _connectedRobot.ManualMoveRight();            
        }
        void SendRobotHome(){
            _connectedRobot.SendHome();
        }

//------------------------------------------




};