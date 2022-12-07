#include <list>
#include "../common/input_utils.h"
#include "../common/string_utils.h"

using namespace std;

struct dir;

struct file {
    string name;
    long size;
    dir* dir;
};

struct dir {
    long size;
    string name;
    dir* parent;
    list<dir*> subDirectories;
    list<file*> files;
};

bool hasDir (dir* current, string &name) {
    for (auto sub : current->subDirectories) {
        if (sub->name == name) {
            return true;
        }
    }
    return false;
}

bool hasFile(dir* current, string &name) {
    for (auto sub : current->files) {
        if (sub->name == name) {
            return true;
        }
    }
    return false;
}

const long MAX_DIR_SIZE = 100000;
const long MIN_UNUSED_SPACE = 30000000;
const long DISK_SPACE = 70000000;

void printTree(dir* current, string indent) {

    cout << current->name << ": " << indent;
    for (auto file : current->files) {
        cout << file->name <<  "(" <<file->size << ") ";
    }

    for (auto sub : current->subDirectories) {
        cout << sub->name << " ";
    }
    cout << "\n";

    indent = indent + "    ";

    for (auto sub : current->subDirectories) {
        printTree(sub, indent);
    }
}

long getDirSizes(dir* current, list<dir*> &dirSizes) {

    long sum = 0;
    for (auto file : current->files) {
       sum += (file->size);
    }

    long subSum = 0;
     for (auto sub : current->subDirectories) {
         subSum += getDirSizes(sub, dirSizes);
    }

     current->size = subSum + sum;

     dirSizes.push_back(current);

     return subSum + sum;

}

int main() {

    vector<string> commands = input_utils::readLines("../data/day07/input.txt");

    dir root;
    root.parent = nullptr;
    root.name= "/";
    dir* current = &root;

    for (auto command : commands) {
        vector<string> split = string_utils::split(command);

        if (split.at(0) == "$") {
            if (split.at(1) == "cd") {
                if (split.at(2) == "/") {
                    current = &root;
                } else {
                    if (split.at(2) == "..") {
                        if (current->parent != nullptr) {
                            current = current->parent;
                        }
                    } else {
                        for (auto dir : current->subDirectories) {
                            if (dir->name == split.at(2)) {
                                current = dir;
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            if (split.at(0) == "dir") {
                if (!hasDir(current, split.at(1))) {
                    dir *dirPtr = new dir;
                    dirPtr->parent = current;
                    dirPtr->name = split.at(1);
                    (current->subDirectories).push_back(dirPtr);
                }
            } else {
                if (!hasFile(current, split.at(1))) {
                    file *filePtr = new file;
                    filePtr->size = stol(split.at(0));
                    filePtr->dir = current;
                    filePtr->name = split.at(1);
                    (current->files).push_back(filePtr);
                }
            }
        }
    }

    current = &root;
    cout << "DIRECTORY STRUCTURE\n";
    cout << "----------------------------------------------\n";
    printTree(current, (string &) "");
    list<dir*> dirs;
    long usedSpace = getDirSizes(current, dirs);

    cout << "----------------------------------------------\n";
    cout << "SIZES\n";
    cout << "----------------------------------------------\n";

    long counter = 0;

    int id = 0;

    for (auto &dir : dirs) {
        cout << id << " " << dir->name << ": " << dir->size;
        if (dir->size <= MAX_DIR_SIZE) {
            counter += dir->size;
        }
        cout<< "\n";
        id++;
    }



    long unusedSpace = DISK_SPACE - usedSpace;
    dir* dirToDelete = &root;

    for (auto &dir : dirs) {
        if ((unusedSpace + dir->size) >= MIN_UNUSED_SPACE && dir->size < dirToDelete->size ) {
            dirToDelete = dir;
        }
    }


    cout << "----------------------------------------------\n";
    cout << "RESULT\n";
    cout << "----------------------------------------------\n";

    cout << counter << "\n";

    cout << "----------------------------------------------\n";
    cout << "TO DELETE \n";
    cout << "----------------------------------------------\n";

    cout << dirToDelete->name << "(" << dirToDelete->size << ")";

    return 0;
}


