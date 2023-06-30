#ifndef FSTREENODE_H
#define FSTREENODE_H

#include "File.h"
#include <vector>

namespace Emulator::FS {
    class FSTreeNode {
    public:
        FSTreeNode* parent;
        Emulator::File::FileI* value;
        std::vector<FSTreeNode*> children;
        FSTreeNode();
        explicit FSTreeNode(Emulator::File::FileI* value);
        explicit FSTreeNode(FSTreeNode* parent);
        FSTreeNode(FSTreeNode* parent, Emulator::File::FileI* value);
        FSTreeNode(const FSTreeNode& rhs);
        FSTreeNode(FSTreeNode&& rhs) noexcept;
        FSTreeNode& operator=(const FSTreeNode& rhs);
        FSTreeNode& operator=(FSTreeNode&& rhs) noexcept;
        [[nodiscard]] bool isChild(FSTreeNode* node) const;
        void addChild(FSTreeNode* node);
        [[nodiscard]] bool isRoot() const;
        [[nodiscard]] bool isLeaf() const;
        ~FSTreeNode();
    };
}

#endif
