#include "FSTree.h"
#include "Commands.h"
#include "Parser.h"


void createFS(Emulator::FS::FSTree* fs);
void printPath(Emulator::FS::FSTreeNode* currentDir);
void addCommands();
Emulator::FS::FSTreeNode* cdHelper(const std::string& path);

auto* const fileSystem = new Emulator::FS::FSTree();
Emulator::FS::FSTreeNode* current;

int main() {
    addCommands();
    createFS(fileSystem);
    current = fileSystem -> getRoot();
    std::string command;
    std::string cName;
    std::vector<char> cOpt;
    std::vector<std::string> cArgs;
    do {
        printPath(current);
        std::cout << "\t> ";
        std::getline(std::cin, command);
        if (command == " " || command.empty()) {
            continue;
        }
        cName = Emulator::Parser::Parser::getCommand(command);
        cOpt = Emulator::Parser::Parser::getOptions(command);
        cArgs = Emulator::Parser::Parser::getArguments(command);
        if (Emulator::Commands::CommandExecutor::findCommand(cName)) {
            Emulator::Commands::CommandExecutor::executeCommand(cName, cOpt, cArgs);
        } else {
            std::cout << cName << ": command not found" << std::endl;
        }
    } while (cName != "exit");
    return 0;
}

void createFS(Emulator::FS::FSTree* fs) {
    auto* root = new Emulator::FS::FSTreeNode(new Emulator::File::Directory("/", "root", "root"));
    fs->addNode(nullptr, root);
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("bin", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("boot", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("dev", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("etc", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("home", "root", "root")));
    fs->addNode(fs->findNode("home"), new Emulator::FS::FSTreeNode(fs->findNode("home"), new Emulator::File::Directory("user", "root", "root")));
    auto* tilda = fs->findNode(fs->findNode(root, "home"), "user");
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Desktop", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Documents", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Downloads", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Library", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Movies", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Music", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Pictures", "user", "user")));
    fs->addNode(tilda, new Emulator::FS::FSTreeNode(tilda, new Emulator::File::Directory("Public", "user", "user")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("lib", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("lost+found", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("media", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("mnt", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("opt", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("proc", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("root", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("sbin", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("tmp", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("usr", "root", "root")));
    fs->addNode(fs->findNode("usr"), new Emulator::FS::FSTreeNode(fs->findNode("usr"), new Emulator::File::Directory("bin", "root", "root")));
    fs->addNode(fs->findNode("usr"), new Emulator::FS::FSTreeNode(fs->findNode("usr"), new Emulator::File::Directory("lib", "root", "root")));
    fs->addNode(fs->findNode("usr"), new Emulator::FS::FSTreeNode(fs->findNode("usr"), new Emulator::File::Directory("local", "root", "root")));
    fs->addNode(fs->findNode("usr"), new Emulator::FS::FSTreeNode(fs->findNode("usr"), new Emulator::File::Directory("sbin", "root", "root")));
    fs->addNode(fs->findNode("usr"), new Emulator::FS::FSTreeNode(fs->findNode("usr"), new Emulator::File::Directory("share", "root", "root")));
    fs->addNode(fs->findNode("share"), new Emulator::FS::FSTreeNode(fs->findNode("share"), new Emulator::File::Directory("doc", "root", "root")));
    fs->addNode(root, new Emulator::FS::FSTreeNode(root, new Emulator::File::Directory("var", "root", "root")));
    fs->addNode(fs->findNode("var"), new Emulator::FS::FSTreeNode(fs->findNode("var"), new Emulator::File::Directory("log", "root", "root")));
}

void printPath(Emulator::FS::FSTreeNode* currentDir) {
    std::vector<std::string> dirs;
    while (currentDir) {
        dirs.push_back(currentDir -> value -> getName());
        currentDir = currentDir -> parent;
    }
    for (auto it = dirs.end() - 1; it >= dirs.begin(); --it) {
        std::cout << *it;
        if (*it != "/" && it != dirs.begin()) {
            std::cout << "/";
        }
    }
}

void addCommands() {
    Emulator::Commands::CommandExecutor::addCommand("ls", Emulator::Commands::CommandExecutor::ls);
    Emulator::Commands::CommandExecutor::addCommand("cd", Emulator::Commands::CommandExecutor::cd);
    Emulator::Commands::CommandExecutor::addCommand("pwd", Emulator::Commands::CommandExecutor::pwd);
    Emulator::Commands::CommandExecutor::addCommand("touch", Emulator::Commands::CommandExecutor::touch);
    Emulator::Commands::CommandExecutor::addCommand("mkdir", Emulator::Commands::CommandExecutor::mkdir);
    Emulator::Commands::CommandExecutor::addCommand("help", Emulator::Commands::CommandExecutor::help);
    Emulator::Commands::CommandExecutor::addCommand("exit", Emulator::Commands::CommandExecutor::exit);
    Emulator::Commands::CommandExecutor::addCommand("file", Emulator::Commands::CommandExecutor::file);
    Emulator::Commands::CommandExecutor::addCommand("rmdir", Emulator::Commands::CommandExecutor::rmdir);
    Emulator::Commands::CommandExecutor::addCommand("rm", Emulator::Commands::CommandExecutor::rm);
}

void Emulator::Commands::CommandExecutor::ls(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    if (arguments.empty()) {
        if (std::count(options.begin(), options.end(), 'l')) {
            if (std::count(options.begin(), options.end(), 'a')) {
                current->value->printLong();
                if (current -> parent) {
                    current->parent->value->printLong();
                } else {
                    current->value->printLong();
                }
                Emulator::FS::FSTree::printCurrentHiddenLong(current);
            } else if (std::count(options.begin(), options.end(), 'A')) {
                Emulator::FS::FSTree::printCurrentHiddenLong(current);
            }
            Emulator::FS::FSTree::printCurrentLong(current);
        } else {
            if (std::count(options.begin(), options.end(), 'a')) {
                current->value->printShort();
                if (current -> parent) {
                    current->parent->value->printShort();
                } else {
                    current->value->printShort();
                }
                Emulator::FS::FSTree::printCurrentHiddenShort(current);
            } else if (std::count(options.begin(), options.end(), 'A')) {
                Emulator::FS::FSTree::printCurrentHiddenLong(current);
            }
            Emulator::FS::FSTree::printCurrentShort(current);
        }
        std::cout << std::endl;
    } else {
        for (auto& arg : arguments) {
            Emulator::FS::FSTreeNode* node = cdHelper(arg);
            if (dynamic_cast<Emulator::File::File*>(node->value)) {
                std::cout << arg << std::endl;
                continue;
            }
            if (arguments.size() != 1) {
                std::cout << arg << ":" << std::endl;
            }
            if (std::count(options.begin(), options.end(), 'l')) {
                if (std::count(options.begin(), options.end(), 'a')) {
                    node->value->printLong();
                    if (node -> parent) {
                        node->parent->value->printLong();
                    } else {
                        node->value->printLong();
                    }
                    Emulator::FS::FSTree::printCurrentHiddenLong(node);
                } else if (std::count(options.begin(), options.end(), 'A')) {
                    Emulator::FS::FSTree::printCurrentHiddenLong(node);
                }
                Emulator::FS::FSTree::printCurrentLong(node);
            } else {
                if (std::count(options.begin(), options.end(), 'a')) {
                    node->value->printShort();
                    if (node -> parent) {
                        node->parent->value->printShort();
                    } else {
                        node->value->printShort();
                    }
                    Emulator::FS::FSTree::printCurrentHiddenShort(node);
                } else if (std::count(options.begin(), options.end(), 'A')) {
                    Emulator::FS::FSTree::printCurrentHiddenLong(node);
                }
                Emulator::FS::FSTree::printCurrentShort(node);
            }
            std::cout << std::endl;
        }
    }
}

void Emulator::Commands::CommandExecutor::cd(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    if (!options.empty()) {
        std::cout << "cd: can't get options" << std::endl;
    }
    if (arguments.size() > 1) {
        std::cout << "cd: too many arguments" << std::endl;
    } else {
        if (cdHelper(arguments[0])) {
            if (dynamic_cast<Emulator::File::File*>(cdHelper(arguments[0])->value)) {
                std::cout << "cd: not a directory: " << arguments[0] << std::endl;
            } else {
                current = cdHelper(arguments[0]);
            }
        } else {
            std::cout << "cd: " << arguments[0] << ": no such file or directory" << std::endl;
        }
    }
}

Emulator::FS::FSTreeNode* cdHelper(const std::string& path) {
    Emulator::FS::FSTreeNode* node = nullptr;
    if (path == "..") {
        node = current;
        if (current->parent) {
            node = current->parent;
        }
        return node;
    }
    if (path[0] == '.') {
        node = current;
        if (path == ".") {
            return node;
        }
        std::string dir;
        std::stringstream ss(path);
        while (std::getline(ss, dir, '/')) {
            if (dir.empty()) {
                node = fileSystem->getRoot();
                continue;
            }
            if (dir == ".") {
                continue;
            } else if (dir == "..") {
                if (node->parent) {
                    node = node->parent;
                }
                continue;
            } else {
                if (fileSystem->findNode(node, dir)) {
                    node = fileSystem->findNode(node, dir);
                } else {
                    return nullptr;
                }
            }
        }
    } else if (path[0] == '/') {
        std::stringstream ss(path);
        std::string dir;
        while (getline(ss, dir, '/')) {
            if (dir.empty()) {
                node = fileSystem->getRoot();
                continue;
            }
            if (dir == ".") {
                continue;
            } else if (dir == "..") {
                if (node->parent) {
                    node = node->parent;
                }
                continue;
            } else {
                if (fileSystem->findNode(node, dir)) {
                    node = fileSystem->findNode(node, dir);
                } else {
                    return nullptr;
                }
            }
        }
    } else {
        node = current;
        std::stringstream ss(path);
        std::string dir;
        while (std::getline(ss, dir, '/')) {
            if (dir.empty()) {
                node = fileSystem->getRoot();
            }
            if (dir == ".") {
                continue;
            } else if (dir == "..") {
                if (node->parent) {
                    node = node->parent;
                }
                continue;
            } else {
                if (fileSystem->findNode(node, dir)) {
                    node = fileSystem->findNode(node, dir);
                } else {
                    return nullptr;
                }
            }
        }
    }
    return node;
}

void Emulator::Commands::CommandExecutor::pwd(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    printPath(current);
    std::cout << std::endl;
}

void Emulator::Commands::CommandExecutor::touch(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    for (auto& arg : arguments) {
        if (arg[0] != '/' && arg[0] != '.' && std::count(arg.begin(), arg.end(), '/')) {
            std::size_t index = arg.size() - 1;
            while (arg[index] != '/') {
                --index;
            }
            Emulator::FS::FSTreeNode* node = cdHelper(arg.substr(0, index));
            if (!node) {
                std::cout << "touch: " << arg << ": No such file or directory" << std::endl;
                return;
            }
            if (dynamic_cast<Emulator::File::File*>(node->value)) {
                std::cout << "touch: " << arg << ": Not a directory" << std::endl;
            }
            std::string file = arg.substr(index + 1, arg.size() - index - 1);
            std::string fileName;
            std::string extension = "txt";
            std::size_t dotIndex = file.size() - 1;
            while (dotIndex > 0 && file[dotIndex] != '.') {
                --dotIndex;
            }
            if (dotIndex == 0) {
                fileName = file;
            } else {
                fileName = file.substr(0, dotIndex);
                extension = file.substr(dotIndex + 1, file.size() - dotIndex - 1);
            }
            node -> addChild(new Emulator::FS::FSTreeNode(node, new Emulator::File::File(fileName, extension, "user", "user")));
        } else if (arg[0] != '/' && arg[0] != '.' && !std::count(arg.begin(), arg.end(), '/')) {
            std::string fileName;
            std::string extension = "txt";
            std::size_t dotIndex = arg.size() - 1;
            while (dotIndex > 0 && arg[dotIndex] != '.') {
                --dotIndex;
            }
            if (dotIndex == 0) {
                fileName = arg;
            } else {
                fileName = arg.substr(0, dotIndex);
                extension = arg.substr(dotIndex + 1, arg.size() - dotIndex - 1);
            }
            current -> addChild(new Emulator::FS::FSTreeNode(current, new Emulator::File::File(fileName, extension, "user", "user")));
        } else {
            std::string fileName;
            std::string extension = "txt";
            if (arg[0] == '.' && !std::count(arg.begin(), arg.end(), '/')) {
                std::size_t dotIndex = arg.size() - 1;
                while (dotIndex > 0 && arg[dotIndex] != '.') {
                    --dotIndex;
                }
                if (dotIndex == 0) {
                    fileName = arg;
                } else {
                    fileName = arg.substr(0, dotIndex);
                    extension = arg.substr(dotIndex + 1, arg.size() - dotIndex - 1);
                }
                current -> addChild(new Emulator::FS::FSTreeNode(current, new Emulator::File::File(fileName, extension, "user", "user")));
            } else if (arg[0] == '.' && std::count(arg.begin(), arg.end(), '/')) {
                std::size_t index = arg.size() - 1;
                while (arg[index] != '/') {
                    --index;
                }
                Emulator::FS::FSTreeNode* node = cdHelper(arg.substr(0, index));
                if (!node) {
                    std::cout << "touch: " << arg << ": No such file or directory" << std::endl;
                    return;
                }
                if (dynamic_cast<Emulator::File::File*>(node->value)) {
                    std::cout << "touch: " << arg << ": Not a directory" << std::endl;
                }
                std::string file = arg.substr(index + 1, arg.size() - index - 1);
                std::size_t dotIndex = file.size() - 1;
                while (dotIndex > 0 && file[dotIndex] != '.') {
                    --dotIndex;
                }
                if (dotIndex == 0) {
                    fileName = file;
                } else {
                    fileName = file.substr(0, dotIndex);
                    extension = file.substr(dotIndex + 1, file.size() - dotIndex - 1);
                }
                node -> addChild(new Emulator::FS::FSTreeNode(node, new Emulator::File::File(fileName, extension, "user", "user")));
            } else {
                std::size_t index = arg.size() - 1;
                while (arg[index] != '/') {
                    --index;
                }
                Emulator::FS::FSTreeNode* node = cdHelper(arg.substr(0, index));
                if (!node) {
                    std::cout << "touch: " << arg << ": No such file or directory" << std::endl;
                    return;
                }
                if (dynamic_cast<Emulator::File::File*>(node->value)) {
                    std::cout << "touch: " << arg << ": Not a directory" << std::endl;
                }
                std::string file = arg.substr(index + 1, arg.size() - index - 1);
                std::size_t dotIndex = file.size() - 1;
                while (dotIndex > 0 && file[dotIndex] != '.') {
                    --dotIndex;
                }
                if (dotIndex == 0) {
                    fileName = file;
                } else {
                    fileName = file.substr(0, dotIndex);
                    extension = file.substr(dotIndex + 1, file.size() - dotIndex - 1);
                }
                node -> addChild(new Emulator::FS::FSTreeNode(node, new Emulator::File::File(fileName, extension, "user", "user")));
            }
        }
    }
}

void Emulator::Commands::CommandExecutor::mkdir(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    for (auto& arg : arguments) {
        if (std::count(options.begin(), options.end(), 'p')) {
            std::string dir;
            std::stringstream ss(arg);
            Emulator::FS::FSTreeNode* node = current;
            while (std::getline(ss, dir, '/')) {
                if (dir.empty()) {
                    node = fileSystem->getRoot();
                } else if (dir == ".") {
                    continue;
                } else if (dir == "..") {
                    if (node->parent) {
                        node = node -> parent;
                    }
                } else {
                    if (fileSystem->findNode(current, dir)) {
                        node = fileSystem->findNode(current, dir);
                    } else {
                        node->addChild(new Emulator::FS::FSTreeNode(node, new Emulator::File::Directory(dir, "user", "user")));
                        node = fileSystem->findNode(node, dir);
                    }
                }
            }
        } else {
            std::size_t index = arg.size() - 1;
            while (index > 0 && arg[index] != '/') {
                --index;
            }
            if (index == 0) {
                current->addChild(new Emulator::FS::FSTreeNode(current, new Emulator::File::Directory(arg, "user", "user")));
            } else {
                std::string path = arg.substr(0, index);
                std::string dirName = arg.substr(index + 1, arg.size() - index - 1);
                Emulator::FS::FSTreeNode* node = cdHelper(path);
                if (!node) {
                    std::cout << "mkdir: " << path << ": No such file or directory" << std::endl;
                    return;
                }
                if (dynamic_cast<Emulator::File::File*>(node->value)) {
                    std::cout << "mkdir: " << path << ": Not a directory" << std::endl;
                }
                node->addChild(new Emulator::FS::FSTreeNode(node, new Emulator::File::Directory(dirName, "user", "user")));
            }
        }
    }
}

void Emulator::Commands::CommandExecutor::help(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    for (auto & it : CommandsList) {
        std::cout << it.first << std::endl;
    }
}

void Emulator::Commands::CommandExecutor::exit(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    std::cout << "\nSaving session...completed." << std::endl;
    std::cout << "Deleting expired sessions...none found." << std::endl;
    std::cout << "\n[Process completed]\n" << std::endl;
}

void Emulator::Commands::CommandExecutor::file(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    for (auto& arg : arguments) {
        Emulator::FS::FSTreeNode* node = cdHelper(arg);
        if (!node) {
            std::cout << arg << ": cannot open `" << arg << "' (No such file or directory)" << std::endl;
        } else if (dynamic_cast<Emulator::File::File*>(node->value)) {
            std::cout << arg << ": ." << dynamic_cast<Emulator::File::File*>(node->value)->getExtension() << " file" << std::endl;
        } else {
            std::cout << arg << ": directory" << std::endl;
        }
    }
}

void Emulator::Commands::CommandExecutor::rmdir(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    if (std::count_if(options.begin(), options.end(), [](char sym) {
        return sym != 'p' && sym != 'v';
    })) {
        std::cout << "rmdir: illegal options" << std::endl;
    }
    for (auto& arg : arguments) {
        Emulator::FS::FSTreeNode* node = cdHelper(arg);
        if (!node) {
            std::cout << "rmdir: " << arg << ": No such file or directory" << std::endl;
        } else {
            if (dynamic_cast<Emulator::File::File*>(node->value)) {
                std::cout << "rmdir: " << arg << ": Not a directory" << std::endl;
            } else {
                if (node -> children.empty()) {
                    fileSystem->deleteNode(node);
                } else {
                    std::cout << "rmdir: " << arg << ": Directory not empty" << std::endl;
                }
            }
        }
    }
}

void Emulator::Commands::CommandExecutor::rm(const std::vector<char> &options, const std::vector<std::string> &arguments) {
    Emulator::FS::FSTreeNode* node = nullptr;
    if (std::count(options.begin(), options.end(), 'r')) {
        for (auto& arg : arguments) {
            node = cdHelper(arg);
            if (node) {
                fileSystem -> deleteNode(node);
            } else {
                std::cout << "rm: " << arg << ": No such file or directory" << std::endl;
            }
        }
    } else {
        for (auto& arg : arguments) {
            node = cdHelper(arg);
            if (node) {
                if (dynamic_cast<Emulator::File::Directory*>(node->value)) {
                    std::cout << "rm: " << arg << ": is a directory" << std::endl;
                } else {
                    fileSystem -> deleteNode(node);
                }
            } else {
                std::cout << "rm: " << arg << ": No such file or directory" << std::endl;
            }
        }
    }
}