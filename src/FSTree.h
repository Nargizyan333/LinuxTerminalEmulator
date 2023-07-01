#ifndef FSTREE_H
#define FSTREE_H

#include "FSTreeNode.h"

namespace Emulator {
    namespace FS {
        class FSTree {
            public:
                FSTree();
                explicit FSTree(FSTreeNode* root);
                FSTree(const FSTree& rhs);
                FSTree(FSTree&& rhs) noexcept;
                FSTree& operator=(const FSTree& rhs);
                FSTree& operator=(FSTree&& rhs) noexcept;
                void addNode(FSTreeNode* parent, FSTreeNode* node);
                void deleteNode(FSTreeNode* node);
                [[nodiscard]] bool isEmpty() const;
                void printShort() const;
                void printLong() const;
                static void printCurrentShort(FSTreeNode* current);
                static void printCurrentLong(FSTreeNode* current);
                static void printCurrentHiddenShort(FSTreeNode* current);
                static void printCurrentHiddenLong(FSTreeNode* current);
                [[nodiscard]] FSTreeNode* getRoot() const;
                [[nodiscard]] int getCount() const;
                [[nodiscard]] FSTreeNode* findNode(const std::string& name) const;
                [[nodiscard]] FSTreeNode* findNode(FSTreeNode* subtree, const std::string& name) const;
            protected:
                FSTreeNode* copyHelper(FSTreeNode* node) const;
                FSTreeNode* findHelper(FSTreeNode* subtree, const std::string& name) const;
                void printShortHelper(FSTreeNode* subtree) const;
                void printLongHelper(FSTreeNode* subtree) const;
            private:
                FSTreeNode* root;
                int count = 0;
        };
    } // FS
} // Emulator


#endif // FSTREE_H