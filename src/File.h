#ifndef FILE_H
#define FILE_H

#include "Permissions.h"
#include <array>
#include <string>
#include <ctime>
#include <iomanip>

#define RESET_COLOR     "\033[0m"
#define BLUE_COLOR      "\033[34m"
#define MAGENTA_COLOR   "\033[35m"
#define CYAN_COLOR      "\033[36m"

namespace Emulator {
    namespace File {
        class IFile {
        public:
            virtual void printShort() const = 0;
            virtual void printLong() const = 0;
            virtual void setName(const std::string& newName) = 0;
            virtual void setPermissions(const std::array<char, 3>& newPermissions) = 0;
            virtual void setLastModDate(const std::time_t& newDate) = 0;
            [[nodiscard]] virtual std::string getName() const = 0;
            [[nodiscard]] virtual Emulator::Permissions::Permissions getPermissions() const = 0;
            [[nodiscard]] virtual std::string getOwnerUser() const = 0;
            [[nodiscard]] virtual std::string getOwnerGroup() const = 0;
            [[nodiscard]] virtual std::time_t getLastModDate() const = 0;
            [[nodiscard]] virtual bool isFileHidden() const = 0;
            virtual ~IFile() = 0;
        };

        class File : public IFile {
        private:
            std::string filename;
            std::string extension;
            Emulator::Permissions::Permissions permissions;
            std::string content;
            std::string ownerUsername;
            std::string ownerGroup;
            std::time_t lastModDate;
            bool isHidden = false;
        public:
            File(std::string filename, std::string user, std::string group);
            File(std::string filename, std::string extension, std::string user, std::string group);
            File(std::string filename, std::string extension, std::string content, std::string user, std::string group);
            File(const File& rhs);
            File(File&& rhs) noexcept;
            File& operator=(const File& rhs);
            File& operator=(File&& rhs) noexcept;
            void printShort() const override;
            void printLong() const override;
            void setName(const std::string& newName) override;
            void setExtension(const std::string& newExtension);
            void setPermissions(const std::array<char, 3>& newPermissions) override;
            void setContent(const std::string& newContent);
            void setLastModDate(const std::time_t& newDate) override;
            [[nodiscard]] std::string getName() const override;
            [[nodiscard]] std::string getExtension() const;
            [[nodiscard]] Emulator::Permissions::Permissions getPermissions() const override;
            [[nodiscard]] std::string getContent() const;
            [[nodiscard]] std::string getOwnerUser() const override;
            [[nodiscard]] std::string getOwnerGroup() const override;
            [[nodiscard]] std::time_t getLastModDate() const override;
            [[nodiscard]] bool isFileHidden() const override;
            ~File() override;
        };

        class Directory : public IFile {
        private:
            std::string name;
            Emulator::Permissions::Permissions permissions;
            std::string ownerUsername;
            std::string ownerGroup;
            std::time_t lastModDate;
            bool isHidden = false;
        public:
            Directory(std::string name, std::string user, std::string group);
            Directory(const Directory& rhs);
            Directory(Directory&& rhs) noexcept;
            Directory& operator=(const Directory& rhs);
            Directory& operator=(Directory&& rhs) noexcept;
            void printShort() const override;
            void printLong() const override;
            void setName(const std::string &newName) override;
            void setPermissions(const std::array<char, 3> &newPermissions) override;
            void setLastModDate(const std::time_t &newDate) override;
            [[nodiscard]] std::string getName() const override;
            [[nodiscard]] Emulator::Permissions::Permissions getPermissions() const override;
            [[nodiscard]] std::string getOwnerUser() const override;
            [[nodiscard]] std::string getOwnerGroup() const override;
            [[nodiscard]] std::time_t getLastModDate() const override;
            [[nodiscard]] bool isFileHidden() const override;
            ~Directory() override;
        };
    } // File
} // Emulator

#endif // File_H