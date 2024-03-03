
#include <iostream>
#include <ctime>
//#include <stdlib.h>

#define ROBOTCPP

#ifndef DEFINEH
#define DEFINEH
#include "Defines.h"
#endif
// #ifndef COMMCPP
// #define COMMCPP
// #include "CommunicationManager.cpp"
// #endif




using namespace std;

class Robot {
    private:
       // Preset Variables
        int _robotID;
        int _softwareVerion;
        int _robotModel;

        // Inherited Values
        int _batteryPercentage;

        // Changeable Variables
        LevelValue _movementSpeed = LevelValue::Medium;
        LevelValue _power = LevelValue::Medium;
        LevelValue _dustLevel = LevelValue::Low;

        Statuses _robotStatus = Statuses::Auto; 


        std::time_t LastCleaningTime;
        std::time_t NextCleanTime;
        int CleaningDurationS = 2*60*60;
        
        Coordinates Position = {0,0};



        int GetDirtCollected(){
            std::time_t TimeCleaning = GetRecentCleaningTime();

            int DirtCollected = TimeCleaning * (1/25) * (this->_power / 10);

            if(DirtCollected/7200>0.6){
                _dustLevel = LevelValue::High;
            }else if(DirtCollected/7200>0.3){
                _dustLevel = LevelValue::Medium;
            }else{
                _dustLevel = LevelValue::Low;
            }
            return DirtCollected;
        }
    
        void UpdateBatteryLevel(){
            if(this->_robotStatus == Statuses::Auto || this->_robotStatus == Statuses::Manual){
                std::time_t TimeCleaning = GetRecentCleaningTime();
                _batteryPercentage =  (93*TimeCleaning/7200) + 7;
            }else{
                std::time_t TimeOnCharge = std::time(nullptr) - (LastCleaningTime + CleaningDurationS);
                if(TimeOnCharge<4*60*60){
                    _batteryPercentage = (TimeOnCharge*93/(4*60*60)) + 7;
                } else {
                    _batteryPercentage = 100;
                }
            }
        }

        void UpdatePosition(){
            if(this->_robotStatus == Statuses::Auto){
                Position.X = rand();
                Position.Y = rand();
            }
        }

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

        std::time_t GetRecentCleaningTime(){
            std::time_t TimeCleaning;
            if(this->_robotStatus == Statuses::Auto || this->_robotStatus == Statuses::Manual){
                TimeCleaning = time(nullptr) - LastCleaningTime;
            } else {
                TimeCleaning = CleaningDurationS;
            }
            return TimeCleaning;
        }

        Robot(){
            // Set Default values
            _robotID = 1; // Change to Dynamic assignment although shouldn't matter as this would be preset
            _softwareVerion = 1; // also preset
            _robotModel = 1;
        }

        Robot(int IDandVersion){
            _robotID = IDandVersion;
            _softwareVerion = IDandVersion;
        }

        int GetRobotID(){
            return _robotID;
        }



// --------------------------------------------------------------------------------------
        AdvancedDataStruct GetAdvancedData(){
            UpdateRobot();
            AdvancedDataStruct AdvData;

            AdvData.AuditLogs = "BingoBongo";
            AdvData.ErrorLog = "Shit! the house is on fire!";
            AdvData.ModelNumber = this->_robotModel;
            AdvData._softwareVerion = this->_softwareVerion;
            AdvData.LastDirtCollected = this->GetDirtCollected();
            AdvData.TimeCleaned = this->LastCleaningTime;
            return AdvData;
        }

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

        LevelValue GetSpeed(){
            UpdateRobot();
            return _movementSpeed;
        }

        LevelValue GetPower(){
            UpdateRobot();
            return _power;
        }

        Statuses GetStatus(){
            UpdateRobot();
            return _robotStatus;
        }

        int GetBatteryStatus(){
            UpdateRobot();
            return _batteryPercentage;
        }

        Coordinates GetRobotPosition(){
            UpdateRobot();
            return Position;
        }

//------------------------------------------------------------------------------------
        void SetSpeed(LevelValue NewSpeed){
            UpdateRobot();
            _movementSpeed = NewSpeed;
        }

        void SetPower(LevelValue NewPower){
            UpdateRobot();
            _power = NewPower;
        }

//---------------------------------------------------------------------------------

        void StartManualClean(){
            this->LastCleaningTime = time(nullptr);
            this->_robotStatus = Statuses::Manual;
        }

        void ManualMoveForward(){
            Position.Y +=1;
        }
        void ManualMoveBackward(){
            Position.Y -=1;
        }
        void ManualMoveLeft(){
            Position.X -=1;
        }
        void ManualMoveRight(){
            Position.X +=1;
        }

        void SendHome(){
            _robotStatus = Statuses::GoingHome;
            std::cout << "Robot returning Home..." << std::endl;
            std::time_t StartHomeTime = std::time(nullptr);
            std::time_t TimeRunning = std::time(nullptr) - StartHomeTime;
            while(TimeRunning < 5){
                TimeRunning = std::time(nullptr) - StartHomeTime;
            }
            Position = {0,0};
            std::cout << "Robot at home" << std::endl;
        }

//---------------------------------------------------------------------------

    std::time_t GetScheduledTime(){
        if(_robotStatus == Statuses::Scheduled){
            return this->NextCleanTime;
        } else {
            return -1;
        }
    } 

    void SetSchedule(time_t NewScheduledTime){
        NextCleanTime = NewScheduledTime;
        _robotStatus = Statuses::Scheduled;
    }

    void TurnOff(){
        NextCleanTime = NULLID;
        _robotStatus = Statuses::Off;
    }
};