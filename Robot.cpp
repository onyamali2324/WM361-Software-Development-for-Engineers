
#include <iostream>

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

        // Inherited Values
        int _batteryPercentage;

        // Changeable Variables
        LevelValue _movementSpeed = LevelValue::Medium;
        LevelValue _power = LevelValue::Medium;

        Statuses _robotStatus = Statuses::Auto; 


        std::time_t StartCleanTime;



    
    public:

        Robot(){
            // Set Default values
            _robotID = 1; // Change to Dynamic assignment although shouldn't matter as this would be preset
            _softwareVerion = 1; // also preset
        }

        Robot(int IDandVersion){
            _robotID = IDandVersion;
            _softwareVerion = IDandVersion;
        }

        int GetRobotID(){
            return _robotID;
        }






// Might have to split all the getting and setting of types due to inconsistent enum usage throughout variables

        void setVALUE(DataTypes VariableNumber, LevelValue Value){
            switch(VariableNumber){
                    
                case DataTypes::Power:
                    _power = Value;
                    break;

                case DataTypes::Speed:
                    _movementSpeed = Value;
                    break;

                case DataTypes::Status:
                    //_robotStatus = Value;
                    break;

                default:
                    cout << "Error!!";
            }

        }


        //probably going to have to split due to the int return removes the relation to the enum and not all return paths give same enum
        int getVALUE(DataTypes VariableNumber){
            switch(VariableNumber){
                case DataTypes::Power:
                    return _power;
                    break;

                case DataTypes::Speed:
                    return _movementSpeed;
                    break;

                case DataTypes::Status:
                    return _robotStatus;
                    break;

                default:
                    cout << "Error!!";
                    return -1;
            }
        }


// --------------------------------------------------------------------------------------
        int GetAdvancedData(){          // Change to Struct
            return 1;
        }

        int GetBasicData(){          // Change to Struct
            return 1;
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