#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <cstdlib>
#include <ctime>

int checkPasswordLength(std::string str) {
    //error checking for whatever's input for passwordLength
    int passwordLength;

    try {
        passwordLength = std::stoi(str);
    }
    catch (...) {
        std::cout << "Invalid password length." << std::endl;
        return -1;
    }

    if (passwordLength<1||passwordLength>50) {
        std::cout << "Invalid password length." << std::endl;
        return -1;
    }
    return passwordLength;
}

int getPasswordLength() {
    std::string str;
    
    std::cout << "Password length: ";
    getline(std::cin, str);

    return checkPasswordLength(str);
}

std::set<int> getOptions() {
    std::cout << "Character set options:" << std::endl;
    std::cout << "  Lowercase (i.e. abcdef) - LC" << std::endl;
    std::cout << "  Uppercase (i.e. ABCDEF) - UC" << std::endl;
    std::cout << "  Digits (i.e. 012345) - DG" << std::endl;
    std::cout << "  Symbols (i.e. !@<{, ) - SM" << std::endl;
    std::cout << "  All - AL" << std::endl << std::endl;

    std::cout << "You may choose All or any combination of the first 5 options. Type all desired options separated by a space, then hit \"ENTER\"." << std::endl << std::endl;
    std::cout << "Option(s): ";

    std::string optionInput;
    getline(std::cin, optionInput);

    //interpret input
    std::set<int> options;
    
    std::istringstream iss(optionInput);
    std::string token;
    while (iss >> token) {
        if (token=="LC"||token=="lc") {
            options.insert(1);
        }
        else if (token=="UC"||token=="uc") {
            options.insert(2);
        }
        else if (token=="DG"||token=="dg") {
            options.insert(3);
        }
        else if (token=="SM"||token=="sm") {
            options.insert(4);
        }
        else if (token=="AL"||token=="al") {
            options.insert(0);
        }
        else {
            std::cout << "Invalid option." << std::endl;
            exit(1);
        }
    }

    return options;
}

std::string generateRandCharSet(std::set<int>* options, int passwordLength) {
    std::string characterSets = "";

    while (characterSets.length()!=passwordLength) {
        int result = 1 + (rand() % 4);

        if (result==1&&(options->find(1)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=std::to_string(result);
        }
        else if (result==2&&(options->find(2)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=std::to_string(result);
        }
        else if (result==3&&(options->find(3)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=std::to_string(result);
        }
        else if (result==4&&(options->find(4)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=std::to_string(result);
        }
    }

    return characterSets;
}

std::string generatePassword(std::set<int>* options, int passwordLength) {

    std::string characterSets;

    //generates a string with the length of passwordLength where each digit is a random approved character set for the password
    //i.e. 224332 is approved if they chose lowercase, uppercase, and digits
    bool error = true;
    while (error) {
        characterSets = generateRandCharSet(options, passwordLength);
        
        error = false;
        if ((options->find(1)!=options->end()||options->find(0)!=options->end())&&characterSets.find("1")==std::string::npos) {
            error = true;
        }
        if ((options->find(2)!=options->end()||options->find(0)!=options->end())&&characterSets.find("2")==std::string::npos) {
            error = true;
        }
        if ((options->find(3)!=options->end()||options->find(0)!=options->end())&&characterSets.find("3")==std::string::npos) {
            error = true;
        }
        if ((options->find(4)!=options->end()||options->find(0)!=options->end())&&characterSets.find("4")==std::string::npos) {
            error = true;
        }
    }
    
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string digits = "0123456789";
    std::string symbols = " ~!@#$%^&*()-=+[{]}\\;:'""/?.>,<";

    //generates the password by choosing a random character from each character set in the string characterSets
    std::string password = "";
    for (int i = 0; i < passwordLength; i++) {
        if (characterSets[i]=='1') {
            password+=lowercase[rand() % lowercase.length()];
        }
        else if (characterSets[i]=='2') {
            password+=uppercase[rand() % uppercase.length()];
        }
        else if (characterSets[i]=='3') {
            password+=digits[rand() % digits.length()];
        }
        else if (characterSets[i]=='4') {
            password+=symbols[rand() % symbols.length()];
        }
    }

    return password;
}

int main(int argc, char* argv[]) {

    int passwordLength;

    if (argc>1) {
        passwordLength = checkPasswordLength(argv[1]);
    }
    else {
        passwordLength = getPasswordLength();
    }

    if (passwordLength==-1) {
        return 1;
    }

    std::set<int> options = getOptions();

    srand((unsigned) time(0));

    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << generatePassword(&options, passwordLength) << std::endl;
    }

    return 0;
}