// Speed/Power (suction)
// #define LOW                 0
// #define MEDIUM              1
// #define HIGH                2

enum LevelValue {Low, Medium, High};

// Power (IO)
#define OFF                 0
#define ON                  1

// Robot Mode
// #define AUTO                0
// #define MANUAL              1
// #define GOHOME              2
// #define NOCLEAN             3
// #define SCHEDULE            4


enum DataTypes {Power, Speed, Status};

// #define SPEEDVAR            0
// #define POWERVAR            1
// #define CLEANINGVAR         2       // Probs change to set order but should be useable to select variable to return

enum Statuses {Off, Auto, Manual, GoingHome, AtHome, Scheduled, Error};

struct BasicDataStruct {
    // Preset Variables
    std::string _robotName;
    int ModelNumber;
    int _softwareVerion;

    // Inherited Values
    int _batteryPercentage;
    LevelValue DustTrayLevel;

    // Changeable Variables
    LevelValue _movementSpeed = LevelValue::Medium;
    LevelValue _power = LevelValue::Medium;

    Statuses _robotStatus = Statuses::Auto;
    std::time_t NextCleanTime;


};


struct AdvancedDataStruct{
    int DustCollected;
    std::time_t TimeCleaned;
    std::string ErrorLog;
    
};

#define NULLID              -1







// Add function definintions or a new header file for function definintions?