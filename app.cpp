#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<sstream>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char*, BST*);
int menu();

int main() {
    int x;
    BST* tree = new BST;
    Student student;

    x = menu();
    while (x != 7) {
        if (x == 1) {
            if (!readFile("student.txt", tree)) cout << "\n\nUnexpected error has occured!\n";
        }
        if (x == 2) {
            if (!tree->deepestNodes())
                cout << "\n\nEmpty Tree. Load Something please :)\n";
        }
        if (x == 3) {
            if (tree->empty()) {
                cout << "\n\nEmpty Tree. Load Something please :)\n";
            }
            else {
                int order, source;
                cout << "\n\nChoose the order manner:\n"
                    "1. Ascending\n"
                    "2. Descending\n"
                    "Please enter your choice: ";
                cin >> order;
                cout << "\n\nOutput decision:\n"
                    "1. Display to Screen\n"
                    "2. Save to File\n"
                    "Please enter your choice: ";
                cin >> source;
                if (!tree->display(order, source)) {
                    cout << "\n\nDisplay failed.\n";
                }
            }
        }
        if (x == 4) {
            BST tree2;  // Create a new BST object 
            cout << "\nEnter the Student ID that you wish to be the Root Node in Cloned SubTree: ";
            cin >> student.id;

            if (tree2.CloneSubtree(*tree, student)) {  // Use tree2 object's method to clone subtree
                cout << "\nDisplaying Tree 1 via Pre-Order:\n";
                tree->preOrderPrint();
                cout << "\nDisplaying Cloned Tree 2 Subtree via Pre-Order:\n";
                tree2.preOrderPrint();
            }
            else {
                cout << "\nFailed to clone subtree.\n";
            }
            // No need to delete tree2 as it's a local object with automatic cleanup
        }
        if (x == 5) {
            if (!tree->printLevelNodes()) {
                if (tree->size() == 0) 
                    cout << "\n\nEmpty Tree. Load Something please :)\n";
            }
        }
        if (x == 6) {
            if (!tree->printPath()) 
                cout << "\n\nEmpty Tree. Load Something please :)\n";
        }
        x = menu();
    }
}

int menu() {
    int x;
    cout << "-----------------------\n";
    cout << "\tMenu\n";
    cout << "-----------------------\n";
    cout << "1. Read data to BST	\n";
    cout << "2. Print deepest nodes	\n";
    cout << "3. Display student		\n";
    cout << "4. Clone Subtree		\n";
    cout << "5. Print Level Nodes   \n";
    cout << "6. Print Path		    \n";
    cout << "7. Exit				\n";
    cout << "Please enter your choice: ";
    cin >> x;
    return x;
}

void trim(string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first != string::npos && last != string::npos) {
        str = str.substr(first, (last - first + 1));
    }
    else {
        // Handle the case where the string is empty or contains only spaces
        str.clear();
    }
}

// function (a) 
bool readFile(const char* filename, BST* t1) {
    ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    string line;
    Student student;
    int validStudentCount = 0;
    int duplicateCount = 0;
    int invalidStudentCount = 0;
    string invalidStudentReason;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string fieldName;
        string fieldValue;

        if (getline(iss, fieldName, '=')) {
            trim(fieldName);

            if (getline(iss, fieldValue)) {
                trim(fieldValue);

                if (fieldName == "Student Id" && !fieldValue.empty()) {
                    student.id = stoi(fieldValue);
                }
                else if (fieldName == "Name") {
                    strncpy_s(student.name, fieldValue.c_str(), sizeof(student.name));
                }
                else if (fieldName == "Address") {
                    strncpy_s(student.address, fieldValue.c_str(), sizeof(student.address));
                }
                else if (fieldName == "DOB") {
                    strncpy_s(student.DOB, fieldValue.c_str(), sizeof(student.DOB));
                }
                else if (fieldName == "Phone Number") {
                    strncpy_s(student.phone_no, fieldValue.c_str(), sizeof(student.phone_no));
                }
                else if (fieldName == "Course") {
                    strncpy_s(student.course, fieldValue.c_str(), sizeof(student.course));
                }
                else if (fieldName == "CGPA") {
                    student.cgpa = std::stod(fieldValue);
                }
            }
        }

        if (fieldName == "CGPA") {
            if (student.id == 0) {
                // Student ID is missing or empty, consider this as an invalid student
                invalidStudentCount++;
                cout << "\n" << student.name << " is an invalid student record. (w/o ID)" << endl;
            }
            else {
                BTNode* SNode = nullptr;
                if (t1->searchNode(SNode, student)) {
                    // Found a duplicate ID, do not insert and count duplicates
                    duplicateCount++;
                    cout << "\nDuplicate student ID : " << student.id << " - Name : " << student.name << endl;
                }
                else {
                    // No duplicate ID, insert the student into the binary search tree
                    t1->insert(student);
                    validStudentCount++;
                }
            }

            // Reset the student object for the next student
            student = Student();
        }
    }

    inputFile.close();

    cout << "-----------------------------------------------\n";
    cout << "Total of " << validStudentCount << " students records successfully read." << endl;
    cout << "Total of " << duplicateCount << " duplicate student IDs found." << endl;

    if (invalidStudentCount > 0) 
        cout << "Total of " << invalidStudentCount << " invalid student record(s) found." << endl;
 

    cout << "-----------------------------------------------\n";

    return true;
}

