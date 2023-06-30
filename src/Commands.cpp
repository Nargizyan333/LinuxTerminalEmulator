#include "Commands.h"
#include "FSTree.h"

std::unordered_map<std::string, Emulator::Commands::command> Emulator::Commands::CommandExecutor::CommandsList;

void Emulator::Commands::CommandExecutor::addCommand(const std::string &commandName, const std::function<void(const std::vector<char> &,
                                                                                          const std::vector<std::string> &)> &command) {
    CommandsList[commandName] = command;
}

bool Emulator::Commands::CommandExecutor::findCommand(const std::string &command) {
    return CommandsList.find(command) != CommandsList.end();
}

void Emulator::Commands::CommandExecutor::executeCommand(const std::string &command, const std::vector<char> &options,
                                     const std::vector<std::string> &arguments) {
    CommandsList[command](options, arguments);
}