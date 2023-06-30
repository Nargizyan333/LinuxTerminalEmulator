#include "Permissions.h"

Emulator::Permissions::Permissions::Permissions(std::array<char, 3> permissions) : permissions(permissions) {}

Emulator::Permissions::Permissions::Permissions(const Permissions &rhs) {
    permissions = rhs.permissions;
}

Emulator::Permissions::Permissions::Permissions(Emulator::Permissions::Permissions &&rhs) noexcept {
    permissions = rhs.permissions;
}

Emulator::Permissions::Permissions &Emulator::Permissions::Permissions::operator=(const Permissions &rhs) {
    if (this != &rhs) {
        permissions = rhs.permissions;
    }
    return *this;
}

Emulator::Permissions::Permissions &Emulator::Permissions::Permissions::operator=(Permissions &&rhs) noexcept {
    if (this != &rhs) {
        permissions = rhs.permissions;
    }
    return *this;
}

std::array<char, 3> Emulator::Permissions::Permissions::getPermissions() const {
    return permissions;
}

void Emulator::Permissions::Permissions::setPermissions(const std::array<char, 3> &newPermissions) {
    permissions = newPermissions;
}

void Emulator::Permissions::Permissions::print() const {
    for (char permission : permissions) {
        if (permission >= 4) {
            std::cout << 'r';
            permission -= 4;
        } else {
            std::cout << '-';
        }
        if (permission >= 2) {
            std::cout << 'w';
            permission -= 2;
        } else {
            std::cout << '-';
        }
        if (permission) {
            std::cout << 'x';
        } else {
            std::cout << '-';
        }
    }
}