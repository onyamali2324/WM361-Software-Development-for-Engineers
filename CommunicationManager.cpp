using namespace std;

#define COMMCPP

#ifndef ROBOTCPP
#define ROBOTCPP
#include "Robot.cpp"
#endif

class CommunicationManager{

    private:
        Robot _connectedRobot;

        static CommunicationManager* instancePointer;

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



        void ConnectRobot(int ConnectionPath){
            // switch(ConnectionPath){
                    
            //     case CONNECTBLUETOOTH:
            //         BluetoothConnection = new Robot(GetInstance(),CONNECTBLUETOOTH);
            //         break;

            //     case CONNECTUSB:
            //         USBConnection = new Robot(GetInstance(),CONNECTUSB);
            //         break;

            //     case CONNECTWIRE:
            //         WireConection = new Robot(GetInstance(),CONNECTWIRE);
            //         break;

            //     default:
            //         cout << "Error!!";

            // }

            _connectedRobot = Robot();

        }
};