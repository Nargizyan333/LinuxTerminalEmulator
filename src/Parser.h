#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <sstream>

namespace Emulator {
    namespace Parser {
        class Parser {
        public:
            static std::string getCommand(const std::string& command);
            static std::vector<char> getOptions(const std::string& command);
            static std::vector<std::string> getArguments(const std::string& command);
        };
    } // Parser
} // Emulator


#endif // PARSER_H