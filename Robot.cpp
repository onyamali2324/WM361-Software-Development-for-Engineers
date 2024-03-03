
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

        std::string _errorLog = "05/03/2024 15:09 - Error: Dust Collection Bin Full! \n 06/03/2024 17:46 - Warning: Low Battery, Robot going home." ;
        std::string _auditLog = "04/03/2024 09:00 - Robot Software Updated to version 3. \n 05/03/2024 18:34 - Emptied Dust Collection Bin.";


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
            _robotID = rand(); // Change to Dynamic assignment although shouldn't matter as this would be preset
            _softwareVerion = 9.4; // also preset
            _robotModel = 3;
        }

        Robot(int RobotID){
            _robotID = RobotID;
            _softwareVerion = 9.4;
            _robotModel = 3;
        }

        int GetRobotID(){
            return _robotID;
        }



// --------------------------------------------------------------------------------------
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

        int StartManualClean(){
            UpdateRobot();
            if(_batteryPercentage > 7){
                this->LastCleaningTime = time(nullptr);
                this->_robotStatus = Statuses::Manual;
                return 0;
            } else{
                return -1;
            }
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
        UpdateRobot();
    }

    void TurnOff(){
        NextCleanTime = NULLID;
        _robotStatus = Statuses::Off;
        UpdateRobot();
    }
};