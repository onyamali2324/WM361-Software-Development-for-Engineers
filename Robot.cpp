// Includes and defines

#include <iostream>
#include <ctime>

#define ROBOTCPP

#ifndef DEFINEH
#define DEFINEH
#include "Defines.h"
#endif




using namespace std;

class Robot {
    private:
       // Variables
        int _robotID;
        int _softwareVerion;
        int _robotModel;

        int _batteryPercentage = 100;
        LevelValue _dustLevel = LevelValue::Low;

        LevelValue _movementSpeed = LevelValue::Medium;
        LevelValue _power = LevelValue::Medium;
        Statuses _robotStatus = Statuses::Auto; 

        std::time_t LastCleaningTime;
        std::time_t NextCleanTime = NULLID;
        int CleaningDurationS = 2*60*60;
        
        Coordinates Position = {0,0};

        std::string _errorLog = "05/03/2024 15:09 - Error: Dust Collection Bin Full! \n 06/03/2024 17:46 - Warning: Low Battery, Robot going home." ;
        std::string _auditLog = "04/03/2024 09:00 - Robot Software Updated to version 3. \n 05/03/2024 18:34 - Emptied Dust Collection Bin.";

        // Updates the dust level and returns the weight of dust collected
        int GetDirtCollected(){
            std::time_t TimeCleaning = GetRecentCleaningTime();

            // Dummy Calculation on how much dirt was collected
            int DirtCollected = TimeCleaning * (1/25) * (this->_power / 10);

            // Sets dust level according to amount of dust collected
            if(DirtCollected/7200>0.6){
                _dustLevel = LevelValue::High;
            }else if(DirtCollected/7200>0.3){
                _dustLevel = LevelValue::Medium;
            }else{
                _dustLevel = LevelValue::Low;
            }
            return DirtCollected;
        }
    
        // Updates the battery level depending on how long the robot has been on charge/running for
        void UpdateBatteryLevel(){
            // if the robot is cleaning work out based on time cleaning.
            if(this->_robotStatus == Statuses::Auto || this->_robotStatus == Statuses::Manual){
                std::time_t TimeCleaning = GetRecentCleaningTime();
                _batteryPercentage =  (93*TimeCleaning/7200) + 7;
            }else{
                //if the robot is charging then work out based on time its been charging
                std::time_t TimeOnCharge = std::time(nullptr) - (LastCleaningTime + CleaningDurationS);
                if(TimeOnCharge<4*60*60){
                    _batteryPercentage = (TimeOnCharge*93/(4*60*60)) + 7;
                } else {
                    _batteryPercentage = 100;
                }
            }
        }

        // Fake tracking the position of the robot if the robot it in auto mode
        void UpdatePosition(){
            if(this->_robotStatus == Statuses::Auto){
                Position.X = rand();
                Position.Y = rand();
            }
        }

        // Updates inherited characteristics of robot and checks status switch
        void UpdateRobot(){
            UpdateBatteryLevel();
            GetDirtCollected();
            UpdatePosition();
            if(_robotStatus == Statuses::Scheduled && NextCleanTime < std::time(nullptr)){
                LastCleaningTime =NextCleanTime;
                this->_robotStatus = Statuses::Auto;
            } else if (this->_robotStatus == Statuses::Auto && (LastCleaningTime+CleaningDurationS < std::time(nullptr) || _batteryPercentage <= 7)) {  //Indicator its scheduled cleaning again
                this->_robotStatus=Statuses::GoingHome;
                this->Position = {0,0};
                if(this->NextCleanTime == NULLID){
                    this->_robotStatus=Statuses::Off;
                }else{
                    this->_robotStatus=Statuses::Scheduled;
                }
            }
        }


    public:

        // gets the time of the last clean and if currently cleaning then the time so far
        std::time_t GetRecentCleaningTime(){
            std::time_t TimeCleaning;
            if(this->_robotStatus == Statuses::Auto || this->_robotStatus == Statuses::Manual){
                TimeCleaning = time(nullptr) - LastCleaningTime;
            } else {
                TimeCleaning = CleaningDurationS;
            }
            return TimeCleaning;
        }

        // Constructor for the robot with no values
        Robot(){
            // Set Default values
            _robotID = rand(); // Change to Dynamic assignment although shouldn't matter as this would be preset
            _softwareVerion = 9.4; // also preset
            _robotModel = 3;
        }

        // Constructor for the robot with given RobotID
        Robot(int RobotID){
            _robotID = RobotID;
            _softwareVerion = 9.4;
            _robotModel = 3;
        }

        // Returns the robot ID of the instance
        int GetRobotID(){
            return _robotID;
        }



// --------------------------------------------------------------------------------------
        // Used to request the Advanced Data: creates and passes Advanced data struct
        AdvancedDataStruct GetAdvancedData(){
            UpdateRobot();
            AdvancedDataStruct AdvData;

            AdvData.AuditLogs = this->_auditLog;
            AdvData.ErrorLog = this->_errorLog;
            AdvData.ModelNumber = this->_robotModel;
            AdvData._softwareVerion = this->_softwareVerion;
            AdvData.LastDirtCollected = this->GetDirtCollected();
            AdvData.TimeCleaned = this->LastCleaningTime;
            return AdvData;
        }

        // Used to request the Basic Data: creates and passes Basic data struct
        BasicDataStruct GetBasicData(){
            UpdateRobot();
            BasicDataStruct BasicData;

            BasicData.RobotName = this->_robotID;
            // Inherited Values
            BasicData.BatteryPercentage = this->_batteryPercentage;
            BasicData.DustTrayLevel = this->_dustLevel;
            // Changeable Variables
            BasicData.MovementSpeed = this->_movementSpeed;
            BasicData.Power = this->_power;
            BasicData.RobotStatus = this->_robotStatus;
            BasicData.NextCleanTime = this->NextCleanTime;

            return BasicData;
        }

//-------
        // Updates robot values then returns the current speed setting of the robot
        LevelValue GetSpeed(){
            UpdateRobot();
            return _movementSpeed;
        }

        // Updates robot values then returns the current power setting of the robot
        LevelValue GetPower(){
            UpdateRobot();
            return _power;
        }

        // Updates robot values then returns the current status of the robot
        Statuses GetStatus(){
            UpdateRobot();
            return _robotStatus;
        }

        // Updates robot values then returns the current battery level of the robot
        int GetBatteryStatus(){
            UpdateRobot();
            return _batteryPercentage;
        }

        // Updates robot values then returns the current position of the robot
        Coordinates GetRobotPosition(){
            UpdateRobot();
            return Position;
        }

//------------------------------------------------------------------------------------
        // Updates robot then assigns given speed as new value
        void SetSpeed(LevelValue NewSpeed){
            UpdateRobot();
            _movementSpeed = NewSpeed;
        }

        // Updates robot then assigns given power as new value
        void SetPower(LevelValue NewPower){
            UpdateRobot();
            _power = NewPower;
        }

//---------------------------------------------------------------------------------
        // Changes robot into manual mode if the robot has enough battery
        int StartManualClean(){
            UpdateRobot();
            if(_batteryPercentage > 7){
                this->LastCleaningTime = time(nullptr);
                this->_robotStatus = Statuses::Manual;
                this->NextCleanTime = NULLID;
                return 0;
            } else{
                return -1;
            }
        }

        // Moves the robot forwards (north)
        void ManualMoveForward(){
            Position.Y +=1;
        }
        // Moves the robot backwards (south)
        void ManualMoveBackward(){
            Position.Y -=1;
        }
        // Moves the robot left (west)
        void ManualMoveLeft(){
            Position.X -=1;
        }
        // Moves the robot right (east)
        void ManualMoveRight(){
            Position.X +=1;
        }

        // Sends robot home and stops manual mode
        void SendHome(){
            _robotStatus = Statuses::GoingHome;
            std::cout << "Robot returning Home..." << std::endl;
            std::time_t StartHomeTime = std::time(nullptr);
            std::time_t TimeRunning = std::time(nullptr) - StartHomeTime;
            while(TimeRunning < 5){
                TimeRunning = std::time(nullptr) - StartHomeTime;
            }
            Position = {0,0};
            _robotStatus = Statuses::Off;
            std::cout << "Robot at home" << std::endl;
        }

//---------------------------------------------------------------------------
        // Returns the next scheduled time if the robot is scheduled to clean
        std::time_t GetScheduledTime(){
            if(_robotStatus == Statuses::Scheduled){
                return this->NextCleanTime;
            } else {
                return -1;
            }
        } 

        // Sets the robot to start cleaning at given time and changed mode to scheduled
        void SetSchedule(time_t NewScheduledTime){
            NextCleanTime = NewScheduledTime;
            _robotStatus = Statuses::Scheduled;
            UpdateRobot();
        }

        // Turns robot off
        void TurnOff(){
            NextCleanTime = NULLID;
            _robotStatus = Statuses::Off;
            UpdateRobot();
        }

        // Default no update to robot software
        int UpdateSoftware(){
            return -1;
        }

};