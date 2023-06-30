#include "FSTree.h"

Emulator::FS::FSTree::FSTree() : root(nullptr) {}

Emulator::FS::FSTree::FSTree(FSTreeNode *root) : root(root) {}

Emulator::FS::FSTree::FSTree(const FSTree &rhs) {
    root = copyHelper(rhs.root);
}

Emulator::FS::FSTree::FSTree(FSTree &&rhs) noexcept : root(rhs.root) {}

Emulator::FS::FSTree &Emulator::FS::FSTree::operator=(const FSTree &rhs) {
    if (this != &rhs) {
        root = copyHelper(rhs.root);
    }
    return *this;
}

Emulator::FS::FSTree &Emulator::FS::FSTree::operator=(FSTree &&rhs) noexcept {
    if (this != &rhs) {
        root = rhs.root;
    }
    return *this;
}


Emulator::FS::FSTreeNode *Emulator::FS::FSTree::copyHelper(FSTreeNode *node) const {
    if (!node) {
        return nullptr;
    } else {
        auto* newNode = new FSTreeNode(node -> parent, node -> value);
        for (auto* child : node->children) {
            newNode->children.push_back(copyHelper(child));
        }
        return newNode;
    }
}

void Emulator::FS::FSTree::addNode(FSTreeNode *parent, FSTreeNode *node) {
    if (!root && !parent) {
        root = node;
        ++count;
        return;
    }
    parent -> children.push_back(node);
    ++count;
}

void Emulator::FS::FSTree::deleteNode(FSTreeNode *node) {
    if (!node) {
        return;
    }
    if (!node -> children.empty()) {
        for (auto & it : node->children) {
            deleteNode(it);
        }
    }
    if (node->parent) {
        node->parent->children.erase(std::find(node->parent->children.begin(), node->parent->children.end(), node));
    }
    delete node;
    node = nullptr;
}

bool Emulator::FS::FSTree::isEmpty() const {
    return !root;
}

void Emulator::FS::FSTree::printShort() const {
    printShortHelper(root);
}

void Emulator::FS::FSTree::printLong() const {
    printLongHelper(root);
}

void Emulator::FS::FSTree::printShortHelper(FSTreeNode *subtree) const {
    if (!subtree) {
        return;
    }
    if (subtree->isRoot()) {
        if (!subtree->value->isFileHidden()) {
            subtree->value->printShort();
        }
        std::cout << std::endl;
    }
    if (!subtree->isLeaf()) {
        for (auto* child : subtree->children) {
            if (!child->value->isFileHidden()) {
                child->value->printShort();
            }
        }
        std::cout << std::endl;
        for (auto* child : subtree->children) {
            printShortHelper(child);
        }
    }
}

void Emulator::FS::FSTree::printLongHelper(FSTreeNode *subtree) const {
    if (!subtree) {
        return;
    }
    if (subtree->isRoot()) {
        if (!subtree->value->isFileHidden()) {
            subtree->value->printLong();
        }
    }
    if (!subtree->isLeaf()) {
        for (auto* child : subtree->children) {
            if (!child->value->isFileHidden()) {
                child->value->printLong();
            }
        }
        for (auto* child : subtree->children) {
            printLongHelper(child);
        }
    }
}

void Emulator::FS::FSTree::printCurrentShort(FSTreeNode *current) {
    for (auto* child : current -> children) {
        if (!child->value->isFileHidden()) {
            child->value->printShort();
        }
    }
}

void Emulator::FS::FSTree::printCurrentLong(FSTreeNode *current) {
    for (auto* child : current->children) {
        if (!child->value->isFileHidden()) {
            child->value->printLong();
        }
    }
}

void Emulator::FS::FSTree::printCurrentHiddenShort(FSTreeNode *current) {
    for (auto* child : current->children) {
        if (child->value->isFileHidden()) {
            child->value->printShort();
        }
    }
}

void Emulator::FS::FSTree::printCurrentHiddenLong(FSTreeNode *current) {
    for (auto* child : current->children) {
        if (child->value->isFileHidden()) {
            child->value->printLong();
        }
    }
}

Emulator::FS::FSTreeNode *Emulator::FS::FSTree::getRoot() const {
    return root;
}

int Emulator::FS::FSTree::getCount() const {
    return count;
}

Emulator::FS::FSTreeNode *Emulator::FS::FSTree::findNode(const std::string &name) const {
    return findHelper(root, name);
}

Emulator::FS::FSTreeNode *Emulator::FS::FSTree::findNode(FSTreeNode *subtree, const std::string &name) const {
    return findHelper(subtree, name);
}

Emulator::FS::FSTreeNode *Emulator::FS::FSTree::findHelper(FSTreeNode *subtree, const std::string &name) const {
    if (!subtree) {
        return root;
    }
    if (name.empty()) {
        return nullptr;
    }
    if (dynamic_cast<Emulator::File::File*>(subtree->value)) {
        if (subtree->value->getName() + "." + dynamic_cast<Emulator::File::File*>(subtree->value)->getExtension() == name) {
            return subtree;
        }
    }
    if (subtree -> value -> getName() == name) {
        return subtree;
    }
    if (!subtree->children.empty()) {
        for (auto* child : subtree->children) {
            auto* result = findHelper(child, name);
            if (result) {
                return result;
            }
        }
    }
    return nullptr;
}