#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <array>
#include <iostream>

namespace Emulator::Permissions {
    class Permissions {
    public:
        explicit Permissions(std::array<char, 3> permissions);
        Permissions(const Permissions& rhs);
        Permissions(Permissions&& rhs) noexcept;
        Permissions& operator=(const Permissions& rhs);
        Permissions& operator=(Permissions&& rhs) noexcept;
        [[nodiscard]] std::array<char,3> getPermissions() const;
        void setPermissions(const std::array<char, 3>& newPermissions);
        void print() const;
    private:
        std::array<char, 3> permissions;
    };
}

#endif