#include <string>

class User{
    private:
        std::string Password;

    public:
        std::string Username;
        int AccessLevel;

        User(){};

        User(std::string _username, std::string _password, int _accessLevel){
            this->Username = _username;
            this->Password = _password;
            this->AccessLevel = _accessLevel;
        };

        std::string getUsername(){
            return this->Username;
        }

        std::string getPassword(){
            return this->Password;
        }

        int getAccessLevel(){
            return this->AccessLevel;
        }

};