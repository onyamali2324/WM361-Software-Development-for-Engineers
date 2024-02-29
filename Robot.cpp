
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
        int _speed = MEDIUM;
        int _power = MEDIUM;
        int _cleaningMode = AUTO;


    
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

        void SetVALUE(int VariableNumber, int Value){
            switch(VariableNumber){
                    
                case SPEEDVAR:
                    _speed = Value;
                    break;

                case POWERVAR:
                    _power = Value;
                    break;

                case CLEANINGVAR:
                    _cleaningMode = Value;
                    break;

                default:
                    cout << "Error!!";

            }


        }

        int getVALUE(int VariableNumber){
            switch(VariableNumber){
                    
                case SPEEDVAR:
                    return _speed;
                    break;

                case POWERVAR:
                    return _power;
                    break;

                case CLEANINGVAR:
                    return _cleaningMode;
                    break;

                default:
                    cout << "Error!!";
                    return -1;
            }
        }

        void SendHome(){
            _cleaningMode = GOHOME;
        }

};