using namespace std;


// Includes and Defines
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

// CommunicationManager is used to manage communication with the robot.
class CommunicationManager{

    private:
        // Pointer towards instance of CommunicationManager
        static CommunicationManager* instancePointer;

        // Robot that is connected to the CLI
        Robot _connectedRobot;

        CommunicationManager(){
            cout << "Made Comms Manager at Address: " << instancePointer<< endl;
        }


    public:
        // Gets or creates the singleton of CommunicationManager
        static CommunicationManager* GetInstance(){
            if( instancePointer == NULL ) {
                instancePointer = new CommunicationManager();
            }

            return instancePointer;
        }


        // Creates new robot instance with RobotID = 2
        void ConnectRobot(){
            _connectedRobot = Robot(2);
        }


        // Checks if robot is connected
        bool IsRobotConnected(int ConnectedRobotID) {
            // checking if ANY robot is connected
            if(ConnectedRobotID == NULLID) {
                // if no robot connected
                if(_connectedRobot.GetRobotID() == NULLID){
                    return false;
                } else {
                    return true;
                }
            } else {
                // if specified robot is connected
                if(_connectedRobot.GetRobotID() == ConnectedRobotID){
                    return true;
                } else {
                    return false;
                }
            }
        }


//-----------------------------------------
        // Requests and checks the Robot's current speed setting before passing back
        int GetRobotSpeed(){
            LevelValue CurrRobotSpeed = _connectedRobot.GetSpeed();
            if(CurrRobotSpeed>=LevelValue::Low && CurrRobotSpeed<=LevelValue::High){
                return CurrRobotSpeed;
            } else{
                return -1;
            }
        }

        // Instructs Robot to set it's speed to the new specified value after checking validity
        int SetRobotSpeed(LevelValue NewSpeed){
            if(NewSpeed>=LevelValue::Low && NewSpeed<=LevelValue::High){
                _connectedRobot.SetSpeed(NewSpeed);
                return 0;
            } else{
                return -1;
            }
        }
//-----------------------------------------
        // Requests and checks the Robot's current power setting before passing back
        int GetRobotPower(){
            LevelValue CurrRobotPower = _connectedRobot.GetPower();
            if(CurrRobotPower>=LevelValue::Low && CurrRobotPower<=LevelValue::High){
                return CurrRobotPower;
            } else{
                return -1;
            }
        }

        // Instructs Robot to set it's power to the new specified value after checking validity
        int SetRobotPower(LevelValue NewPower){
            if(NewPower>=LevelValue::Low && NewPower<=LevelValue::High){
                _connectedRobot.SetPower(NewPower);
                return 0;
            } else{
                return -1;
            }
        }
//-----------------------------------------
        // Requests and checks the Robot's current status setting before passing back
        Statuses GetRobotStatus(){
            Statuses RobotState = _connectedRobot.GetStatus();
            if(RobotState >= Statuses::Off && RobotState <= Statuses::Error){
            return RobotState;
            } else {
                return Statuses::Error;
            }
        }

        // Requests and checks the Robot's current battery setting before passing back
        int GetRobotBattery(){
            int BatteryPercentage = _connectedRobot.GetBatteryStatus();
            if(BatteryPercentage>=0 && BatteryPercentage <=100){
                return BatteryPercentage;
            }else{
                return -1;
            }
        }

        // Requests the Robot's current position and passes back
        Coordinates GetRobotPosition(){
            return _connectedRobot.GetRobotPosition();
        }

//----------------------------------------
        // Requests the Robot's Advanced Data package and passes back
        AdvancedDataStruct GetRobotsAdvancedData(){
            return _connectedRobot.GetAdvancedData();
        }

        // Requests the Robot's Basic/General Data package and passes back
        BasicDataStruct GetRobotsBasicData(){
            return _connectedRobot.GetBasicData();
        }

//----------------------------------------
        // Sets Robot to be in manual control mode
        void StartManualRobotMode(){
            _connectedRobot.StartManualClean();     //Need check?
        }
        // If robot is in manual mode, tells robot to advance forward (North)
        int MoveRobotForward(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
                _connectedRobot.ManualMoveForward();
                return 0;
            } else {
                return -1;
            }
        }
        // If robot is in manual mode, tells robot to move backwards (South)
        int MoveRobotBackward(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.ManualMoveBackward();
                return 0;
            } else {
                return -1;
            }
        }
        // If robot is in manual mode, tells robot to move left (west)
        int MoveRobotLeft(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.ManualMoveLeft();
                return 0;
            } else {
                return -1;
            }
        }
        // If robot is in manual mode, tells robot to move right (east)
        int MoveRobotRight(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
            _connectedRobot.ManualMoveRight();
                return 0;
            } else {
                return -1;
            }
        }
        // If robot is in manual mode, tells robot to go home
        int SendRobotHome(){
            if(_connectedRobot.GetStatus() == Statuses::Manual){
                _connectedRobot.SendHome();
                return 0;
            } else {
                return -1;
            }
        }

//------------------------------------------
        // Requests the next time the robot is scheduled to clean and passes back
        std::time_t GetRobotScheduledTime(){
            return _connectedRobot.GetScheduledTime();
        }

        // Takes in new scheduled hour and instructs robot to set next scheduled time after checking validity
        int SetRobotSchedule(int Hour){
            // Is Hour in correct range
            if(Hour>=0 && Hour<=23){
                // Get current time and adjust to be the hour scheduled on today
                std::time_t TimeSeconds = time(nullptr);
                struct std::tm *TimeInfo = localtime(&TimeSeconds);
                TimeInfo->tm_hour = Hour;
                TimeInfo->tm_min = 0;
                TimeInfo->tm_sec = 0;

                std::time_t ScheduledSeconds = mktime(TimeInfo);

                // if scheduled time has been passed today
                if(TimeSeconds>ScheduledSeconds){
                    // Change time to tomorrow
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