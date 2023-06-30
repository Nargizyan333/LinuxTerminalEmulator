#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>

namespace Emulator::Commands {
    using myPair = std::pair<std::string, std::function<void(const std::vector<char>&, const std::vector<std::string>&)>>;
    using command = std::function<void(const std::vector<char>&, const std::vector<std::string>&)>;

    class CommandExecutor {
    private:
        static std::unordered_map<std::string, command> CommandsList;
    public:
        static void addCommand(const std::string& commandName, const std::function<void(const std::vector<char>&, const std::vector<std::string>&)>& command);
        static bool findCommand(const std::string& command);
        static void executeCommand(const std::string& command, const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void ls(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void cd(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void pwd(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void touch(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void mkdir(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void help(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void exit(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void file(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void rmdir(const std::vector<char>& options, const std::vector<std::string>& arguments);
        static void rm(const std::vector<char>& options, const std::vector<std::string>& arguments);
    };
} // Emulator::Commands

#endif // COMMANDS_H