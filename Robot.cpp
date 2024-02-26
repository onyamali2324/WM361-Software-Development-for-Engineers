#include "Defines.h"

class Robot {
    private:{
        // Preset Variables
        const int _robotID;
        int _softwareVerion;

        // Inherited Values
        int _batteryPercentage;

        // Changeable Variables
        int _speed = MEDIUM;
        int _power = MEDIUM;
        int _cleaningMode = AUTO;
    }


    public:{

        Robot(){
            // Set Default values
            _robotID = 1; // Change to Dynamic assignment although shouldn't matter as this would be preset
            _softwareVerion = 1; // also preset
        }


        void SetVALUE(int VariableNumber, int Value){
            switch(VariableNumber){
                    
                case SPEEDVAR:
                    _speed = Value
                    break;

                case POWERVAR:
                    _power = Value
                    break;

                case CLEANINGVAR:
                    _cleaningMode = Value
                    break;

                default:
                    cout << "Error!!";

            }


        }

        int getVALUE(int VariableNumber, int Value){
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
            }
        }

        void SendHome(){
            _cleaningMode = GOHOME;
        }

    }

};