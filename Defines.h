// Speed/Power (suction)
// #define LOW                 0
// #define MEDIUM              1
// #define HIGH                2
#include <ctime>
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
};


struct AdvancedDataStruct{
    std::string ErrorLog;
    std::string AuditLogs;

    int ModelNumber;
    int _softwareVerion;
    
    std::time_t TimeCleaned;

    int LastDirtCollected;
     
};

#define NULLID              -1







// Add function definintions or a new header file for function definintions?