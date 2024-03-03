// Speed/Power (suction)
// #define LOW                 0
// #define MEDIUM              1
// #define HIGH                2
#include <iostream>
#include <ostream>
#include <ctime>
#include <string>
enum LevelValue {Low=1, Medium, High};

// Power (IO)
#define OFF                 0
#define ON                  1

// Robot Mode
// #define AUTO                0
// #define MANUAL              1
// #define GOHOME              2
// #define NOCLEAN             3
// #define SCHEDULE            4

// #define SPEEDVAR            0
// #define POWERVAR            1
// #define CLEANINGVAR         2       // Probs change to set order but should be useable to select variable to return

enum Statuses {Off, Auto, Manual, GoingHome, Scheduled, Error};

struct Coordinates{int X,Y;};


struct BasicDataStruct {
    // Preset Variables
    std::string RobotName;

    // Inherited Values
    int BatteryPercentage;
    LevelValue DustTrayLevel;

    // Changeable Variables
    LevelValue MovementSpeed = LevelValue::Medium;
    LevelValue Power = LevelValue::Medium;

    Statuses RobotStatus = Statuses::Auto;
    std::time_t NextCleanTime;
    //friend std::ostream& operator<<(std::ostream os, const BasicDataStruct& val);
};
std::ostream& operator<<(std::ostream& os, const BasicDataStruct& val){
os << "Robot Name :" << val.RobotName << ", Battery Percentage :" << val.BatteryPercentage << ", Dust Tray Level :" << val.DustTrayLevel << ", Speed :" << val.MovementSpeed << ", Power :" << val.Power << ", Robot Status :" << val.RobotStatus << ", Next Clean Time :" << val.NextCleanTime;
return os; 
}


struct AdvancedDataStruct{
    std::string ErrorLog;
    std::string AuditLogs;

    int ModelNumber;
    int _softwareVerion;
    
    std::time_t TimeCleaned;

    int LastDirtCollected;
    
};
std::ostream& operator<<(std::ostream& os, const AdvancedDataStruct& val){
os << "Error Log:" << val.ErrorLog << ", Audit Log:" << val.AuditLogs << ", Model Number :" << val.ModelNumber << ", Software Version :" << val._softwareVerion << ", Time Cleaned :" << val. TimeCleaned << ", Last Dire Collected :" << val.LastDirtCollected;
return os;
}

#define NULLID              -1







// Add function definintions or a new header file for function definintions?