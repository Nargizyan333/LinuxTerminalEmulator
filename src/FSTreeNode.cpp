#include "FSTreeNode.h"

Emulator::FS::FSTreeNode::FSTreeNode()
    : parent(nullptr), value(nullptr), children() {}

Emulator::FS::FSTreeNode::FSTreeNode(Emulator::File::IFile *value)
    : parent(nullptr), value(value), children() {}

Emulator::FS::FSTreeNode::FSTreeNode(FSTreeNode *parent)
    : parent(parent), value(nullptr), children() {}

Emulator::FS::FSTreeNode::FSTreeNode(FSTreeNode *parent, Emulator::File::IFile *value)
    : parent(parent), value(value), children() {}

Emulator::FS::FSTreeNode::FSTreeNode(const FSTreeNode &rhs) {
    parent = rhs.parent;
    children = rhs.children;
    value = rhs.value;
}

Emulator::FS::FSTreeNode::FSTreeNode(FSTreeNode &&rhs) noexcept {
    parent = rhs.parent;
    children = rhs.children;
    value = rhs.value;
}

Emulator::FS::FSTreeNode &Emulator::FS::FSTreeNode::operator=(const FSTreeNode &rhs) {
    if (this != &rhs) {
        parent = rhs.parent;
        children = rhs.children;
        value = rhs.value;
    }
    return *this;
}

Emulator::FS::FSTreeNode &Emulator::FS::FSTreeNode::operator=(FSTreeNode &&rhs) noexcept {
    if (this != &rhs) {
        parent = rhs.parent;
        children = rhs.children;
        value = rhs.value;
    }
    return *this;
}

bool Emulator::FS::FSTreeNode::isChild(FSTreeNode *node) const {
    return std::count(children.begin(), children.end(), node);
}

void Emulator::FS::FSTreeNode::addChild(FSTreeNode *node) {
    if (!dynamic_cast<Emulator::File::File*>(value)) {
        children.push_back(node);
    }
}

bool Emulator::FS::FSTreeNode::isRoot() const {
    return !parent;
}

bool Emulator::FS::FSTreeNode::isLeaf() const {
    return children.empty();
}

Emulator::FS::FSTreeNode::~FSTreeNode() {
    delete value;
}