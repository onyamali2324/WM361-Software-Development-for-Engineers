
#include <iostream>
#include <ctime>

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
        int CleaningDurationMs = 2*60*60*1000;
        
        Coordinates Position = {0,0};



        int GetDirtCollected(){
            std::time_t TimeCleaning;
            if(this->_robotStatus == Statuses::Auto || this->_robotStatus == Statuses::Manual){
                TimeCleaning = time(nullptr) - LastCleaningTime;
            } else {
                TimeCleaning = CleaningDurationMs;
            }

            int DirtCollected = TimeCleaning * (1/33000) * (this->_power / 10);

            if(DirtCollected/7200000>0.6){
                _dustLevel = LevelValue::High;
            }else if(DirtCollected/7200000>0.3){
                _dustLevel = LevelValue::Medium;
            }else{
                _dustLevel = LevelValue::Low;
            }
            return DirtCollected;
        }
    
        void UpdateBatteryLevel(){


        }

        void UpdateRobot(){
            if(_robotStatus == Statuses::Scheduled && NextCleanTime < std::time(nullptr)){
                LastCleaningTime =NextCleanTime;
                this->_robotStatus = Statuses::Auto;
            } else if (this->_robotStatus == Statuses::Auto && LastCleaningTime+CleaningDurationMs < std::time(nullptr)) {
                this->_robotStatus=Statuses::GoingHome;
                 
            }

        }


    public:

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
            return _movementSpeed;
        }

        LevelValue GetPower(){
            return _power;
        }

        Statuses GetStatus(){
            return _robotStatus;
        }

        int GetBatteryStatus(){
            return _batteryPercentage;
        }

//------------------------------------------------------------------------------------
        void SetSpeed(LevelValue NewSpeed){
            _movementSpeed = NewSpeed;
        }

        void SetPower(LevelValue NewPower){
            _power = NewPower;
        }

        void SetStatus(Statuses NewStatus){                // Maybe remove this so we can change other variables as start cleaning and stop cleaning
            _robotStatus = NewStatus;
        }



//---------------------------------------------------------------------------------
        void SendHome(){
            _robotStatus = Statuses::GoingHome;
        }

};