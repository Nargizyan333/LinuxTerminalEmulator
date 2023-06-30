#include "Parser.h"
#include <iostream>

std::string Emulator::Parser::Parser::getCommand(const std::string &command) {
    return command.substr(0, command.find(' '));
}

std::vector<char> Emulator::Parser::Parser::getOptions(const std::string &command) {
    std::vector<char> options;
    for (int i = 1; i < command.size() - 1; ++i) {
        if (command[i] == '-') {
            if (command[i-1] == ' ') {
                int j = i + 1;
                while (command[j] != ' ' && command[j] != '\0') {
                    options.push_back(command[j]);
                    ++j;
                }
            }
        }
    }
    return options;
}

std::vector<std::string> Emulator::Parser::Parser::getArguments(const std::string &command) {
    std::stringstream ss(command);
    std::string comp;
    std::vector<std::string> args;
    int count = 0;
    while (std::getline(ss, comp, ' ')) {
        ++count;
        if (count != 1 && comp[0] != '-') {
            args.push_back(comp);
        }
    }
    return args;
}