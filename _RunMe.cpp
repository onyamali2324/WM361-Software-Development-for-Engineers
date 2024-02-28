#include <iostream>
#include<string>

//using namespace std;

void WelcomeMessage (){
    
    std::cout << "\\                         /  ________             ________  ________   ___      ___   ________   "   <<std:: endl;
    std::cout << " \\                        /|          |         |         |        | |   \\    /   | |          "    << std::endl;
    std::cout << "  \\          __          / |          |         |         |        | |    \\  /    | |          "    << std::endl;
    std::cout << "   \\        /  \\        /  |_____     |         |         |        | |     \\/     | |_____     "   << std::endl;
    std::cout << "    \\      /    \\      /   |          |         |         |        | |            | |          "    << std::endl;
    std::cout << "     \\    /      \\    /    |          |         |         |        | |            | |          "    << std::endl;
    std::cout << "      \\__/        \\__/     |________  |________ |________ |________| |            | |________  "    << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------"       << std::endl;
}

int LoginPrompt(){
    std::cout << "Please enter your User ID:" <<std::endl;
    
    std::string User;
    std::getline(std::cin, User);

    return 0;
}

int main(){
    WelcomeMessage();

    LoginPrompt();


    return 0;
}