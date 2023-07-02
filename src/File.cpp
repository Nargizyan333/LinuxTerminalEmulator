#include "File.h"
#include <iostream>

Emulator::File::IFile::~IFile() {}

// File

Emulator::File::File::File(std::string filename, std::string user, std::string group)
    : filename(std::move(filename)), extension("txt"), ownerUsername(std::move(user)), ownerGroup(std::move(group)),
    permissions({6,4,4}), lastModDate(std::time(nullptr)) {
    if (this->filename[0] == '.') {
        isHidden = true;
    }
}

Emulator::File::File::File(std::string filename, std::string extension, std::string user, std::string group)
    : filename(std::move(filename)), extension(std::move(extension)), ownerUsername(std::move(user)), ownerGroup(std::move(group)),
    permissions({6,4,4}), lastModDate(std::time(nullptr)) {
    if (this->filename[0] == '.') {
        isHidden = true;
    }
}

Emulator::File::File::File(std::string filename, std::string extension, std::string content, std::string user, std::string group)
    : filename(std::move(filename)), extension(std::move(extension)), content(std::move(content)), ownerUsername(std::move(user)), ownerGroup(std::move(group)),
    permissions({6,4,4}), lastModDate(std::time(nullptr)) {
    if (this->filename[0] == '.') {
        isHidden = true;
    }
}

Emulator::File::File::File(const File &rhs) : permissions({6,4,4}){
    filename = rhs.filename;
    extension = rhs.extension;
    content = rhs.content;
    ownerUsername = rhs.ownerUsername;
    ownerGroup = rhs.ownerGroup;
    lastModDate = std::time(nullptr);
    isHidden = rhs.isHidden;
}

Emulator::File::File::File(File &&rhs) noexcept : permissions({6,4,4}){
    filename = std::move(rhs.filename);
    extension = std::move(rhs.extension);
    permissions = std::move(rhs.permissions);
    content = std::move(rhs.content);
    ownerUsername = std::move(rhs.ownerUsername);
    ownerGroup = std::move(rhs.ownerGroup);
    lastModDate = std::time(nullptr);
    isHidden = rhs.isHidden;
}

Emulator::File::File &Emulator::File::File::operator=(const File &rhs) {
    if (this != &rhs) {
        filename = rhs.filename;
        extension = rhs.extension;
        permissions = rhs.permissions;
        content = rhs.content;
        ownerUsername = rhs.ownerUsername;
        ownerGroup = rhs.ownerGroup;
        lastModDate = std::time(nullptr);
        isHidden = rhs.isHidden;
    }
    return *this;
}

Emulator::File::File &Emulator::File::File::operator=(File &&rhs) noexcept {
    if (this != &rhs) {
        filename = std::move(rhs.filename);
        extension = std::move(rhs.extension);
        permissions = std::move(rhs.permissions);
        content = std::move(rhs.content);
        ownerUsername = std::move(rhs.ownerUsername);
        ownerGroup = std::move(rhs.ownerGroup);
        lastModDate = std::time(nullptr);
        isHidden = rhs.isHidden;
    }
    return *this;
}

void Emulator::File::File::printShort() const {
    std::cout << filename << '.' << extension << " ";
}

void Emulator::File::File::printLong() const {
    std::cout << "-";
    permissions.print();
    std::cout << '\t' << 1 << '\t' << ownerUsername << '\t' << ownerGroup << '\t' << content.size() << '\t' << std::put_time(std::localtime(&lastModDate), "%b %d %H:%M:%S") << "\t\t" << filename << '.' << extension << std::endl;
}

void Emulator::File::File::setName(const std::string &newName) {
    filename = newName;
    lastModDate = std::time(nullptr);
}

void Emulator::File::File::setExtension(const std::string &newExtension) {
    extension = newExtension;
    lastModDate = std::time(nullptr);
}

void Emulator::File::File::setPermissions(const std::array<char, 3>& newPermissions) {
    permissions.setPermissions(newPermissions);
    lastModDate = std::time(nullptr);
}

void Emulator::File::File::setContent(const std::string &newContent) {
    content = newContent;
    lastModDate = std::time(nullptr);
}

void Emulator::File::File::setLastModDate(const std::time_t &newDate) {
    lastModDate = newDate;
}

std::string Emulator::File::File::getName() const {
    return filename;
}

std::string Emulator::File::File::getExtension() const {
    return extension;
}

Emulator::Permissions::Permissions Emulator::File::File::getPermissions() const {
    return permissions;
}

std::string Emulator::File::File::getContent() const {
    return content;
}

std::string Emulator::File::File::getOwnerUser() const {
    return ownerUsername;
}

std::string Emulator::File::File::getOwnerGroup() const {
    return ownerGroup;
}

std::time_t Emulator::File::File::getLastModDate() const {
    return lastModDate;
}

bool Emulator::File::File::isFileHidden() const {
    return isHidden;
}

Emulator::File::File::~File() = default;

// Directory

Emulator::File::Directory::Directory(std::string name, std::string user, std::string group)
    : name(std::move(name)), ownerUsername(std::move(user)), ownerGroup(std::move(group)),
    permissions({7,5,5}), lastModDate(std::time(nullptr)) {
    if (this->name[0] == '.') {
        isHidden = true;
    }
}

Emulator::File::Directory::Directory(const Directory &rhs) : permissions({7,5,5}){
    name = rhs.name;
    ownerUsername = rhs.ownerUsername;
    ownerGroup = rhs.ownerGroup;
    lastModDate = std::time(nullptr);
    isHidden = rhs.isHidden;
}

Emulator::File::Directory::Directory(Directory &&rhs) noexcept : permissions({7,5,5}) {
    name = std::move(rhs.name);
    ownerUsername = std::move(rhs.ownerUsername);
    ownerGroup = std::move(rhs.ownerGroup);
    lastModDate = std::time(nullptr);
    isHidden = rhs.isHidden;
}

Emulator::File::Directory &Emulator::File::Directory::operator=(const Directory &rhs) {
    if (this != &rhs) {
        name = rhs.name;
        ownerUsername = rhs.ownerUsername;
        ownerGroup = rhs.ownerGroup;
        lastModDate = std::time(nullptr);
        isHidden = rhs.isHidden;
    }
    return *this;
}

Emulator::File::Directory &Emulator::File::Directory::operator=(Directory &&rhs) noexcept {
    if (this != &rhs) {
        name = std::move(rhs.name);
        ownerUsername = std::move(rhs.ownerUsername);
        ownerGroup = std::move(rhs.ownerGroup);
        lastModDate = std::time(nullptr);
        isHidden = rhs.isHidden;
    }
    return *this;
}

void Emulator::File::Directory::printShort() const {
    std::cout << CYAN_COLOR << name << "/" << RESET_COLOR << " ";
}

void Emulator::File::Directory::printLong() const {
    std::cout << "d";
    permissions.print();
    std::cout << '\t' << 1 << '\t' << ownerUsername << '\t' << ownerGroup << '\t' << 256 << '\t' << std::put_time(std::localtime(&lastModDate), "%b %d %H:%M:%S") << "\t\t" << CYAN_COLOR << name << "/" << RESET_COLOR << std::endl;
}

void Emulator::File::Directory::setName(const std::string &newName) {
    name = newName;
    lastModDate = std::time(nullptr);
}

void Emulator::File::Directory::setPermissions(const std::array<char, 3> &newPermissions) {
    permissions.setPermissions(newPermissions);
    lastModDate = std::time(nullptr);
}

void Emulator::File::Directory::setLastModDate(const std::time_t &newDate) {
    lastModDate = newDate;
}

std::string Emulator::File::Directory::getName() const {
    return name;
}

Emulator::Permissions::Permissions Emulator::File::Directory::getPermissions() const {
    return permissions;
}

std::string Emulator::File::Directory::getOwnerUser() const {
    return ownerUsername;
}

std::string Emulator::File::Directory::getOwnerGroup() const {
    return ownerGroup;
}

std::time_t Emulator::File::Directory::getLastModDate() const {
    return lastModDate;
}

bool Emulator::File::Directory::isFileHidden() const {
    return isHidden;
}

Emulator::File::Directory::~Directory() = default;