using namespace std;

#define COMMCPP

#ifndef DEFINEH
#define DEFINEH
#include "Defines.h"
#endif

#ifndef ROBOTCPP
#define ROBOTCPP
#include "Robot.cpp"
#endif

class CommunicationManager{

    private:
        static CommunicationManager* instancePointer;

        Robot _connectedRobot;

        CommunicationManager(){
            cout << "Made Comms Manager at Address: " << instancePointer<< endl;
        }


    public:


        static CommunicationManager* GetInstance(){
            if( instancePointer == NULL ) {
                instancePointer = new CommunicationManager();
            }

            return instancePointer;
        }



        void ConnectRobot(){
            _connectedRobot = Robot(2);


            
        }


        bool IsRobotConnected(int ConnectedRobotID) {
            if(ConnectedRobotID == NULLID) {            // if checking if ANY robot is connected
                if(_connectedRobot.GetRobotID() == NULLID){     // if no robot connected
                    return false;
                } else {
                    return true;
                }
            } else {
                if(_connectedRobot.GetRobotID() == ConnectedRobotID){     // if specified robot is connected
                    return true;
                } else {
                    return false;
                }
            }
        }

        
};