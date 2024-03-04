#include <iostream>
#include<ostream>
#include <string>
#include <functional>
#include <map>
#include <fstream>
#include <sstream>

class LoginManager{
    public:
        std::map<std::string, std::string> LoginPrompt(){
        std::cout << "Please enter your User ID:" <<std::endl;
        std::string User;
        std::getline(std::cin, User);
        std::cout << "Please enter your password:" <<std::endl;
        std::string Pwd;
        std::getline(std::cin, Pwd);
        std::map<std::string, std::string> entered_logins = {
            {User,Pwd}
        };
        return entered_logins;
        }
        int login_checker(std::map<std::string, std::string> entered_logins){
                std::map<std::string, std::string> userPasswordMap;

    // Open the file
    std::ifstream inputFile("logins.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1; // Return an error code
    }

    // Read each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string username, password;

        // Split the line into username and password
        if (std::getline(iss, username, ',') && std::getline(iss, password, ',')) {
            // Store the pair in the map
        password.erase(std::remove_if(password.begin(), password.end(), [](char c) { return !std::isalpha(c); }),password.end());
            userPasswordMap[username] = password;
        } else {
            std::cerr << "Invalid format in line: " << line << std::endl;
        }
    }

    // Close the file
    inputFile.close();
            auto it = userPasswordMap.find(entered_logins.begin()->first);
            if (it != userPasswordMap.end()) {
            // Username found, now check if the password matches
            if (it->second == entered_logins.begin()->second) {
            std::cout << "Login successful!" << std::endl;
            if (entered_logins.begin()->first=="user"){
                return 0;
            } else if (entered_logins.begin()->first=="owner"){
                return 1;
            } else if (entered_logins.begin()->first=="admin"){
                return 2;
            }
            }else {
            std::cout << "Incorrect password. Exitting Program." << std::endl;

            }
        } else {
        std::cout << "Username not found. Exitting Program." << std::endl;
        }
        return -1;
}
};