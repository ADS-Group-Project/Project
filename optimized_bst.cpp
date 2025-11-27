#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

//DATA STRUCTURES

struct SubjectRecord {
    string name;
    double mark;
    bool hasMark;
};

struct Student {
    int id;
    string name;
    string course;
    vector<SubjectRecord> subjects;
};

// The Tree Node
struct Node {
    Student data;
    Node* left;
    Node* right;

    Node(Student s) : data(s), left(nullptr), right(nullptr) {}
};

//INPUT HELPERS

int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Wrong input, please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double readDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Wrong input, please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

//BST ALGORITHMS

// 1. Search (Recursive)
// Returns a pointer to the STUDENT object if found, or nullptr if not.
Student* searchBST(Node* root, int targetId) {
    if (root == nullptr) {
        return nullptr; // Not found (hit bottom of tree)
    }

    if (targetId == root->data.id) {
        return &(root->data); // Found! Return address of data
    } 
    else if (targetId < root->data.id) {
        return searchBST(root->left, targetId); // Go Left
    } 
    else {
        return searchBST(root->right, targetId); // Go Right
    }
}

// 2. Insert (Recursive)
// Note: We pass the pointer by reference (Node*&) so we can modify the links.
void insertBST(Node*& root, const Student& newStudent) {
    if (root == nullptr) {
        // Found the empty spot! Create the new node here.
        root = new Node(newStudent);
        cout << "Student with ID " << newStudent.id << " added successfully.\n";
        return;
    }

    if (newStudent.id < root->data.id) {
        insertBST(root->left, newStudent); // Insert in left subtree
    } 
    else if (newStudent.id > root->data.id) {
        insertBST(root->right, newStudent); // Insert in right subtree
    } 
    else {
        // ID already exists
        cout << "Error: Student ID " << newStudent.id << " already exists.\n";
    }
}

// Helper to display a student
void showStudent(const Student &s) {
    cout << "\n=== Student Information ===\n";
    cout << "ID     : " << s.id << "\n";
    cout << "Name   : " << s.name << "\n";
    cout << "Course : " << s.course << "\n";
    cout << "Subjects and Marks:\n";

    if (s.subjects.empty()) {
        cout << "  (No subjects registered)\n";
    } else {
        for (size_t i = 0; i < s.subjects.size(); ++i) {
            cout << "  " << (i + 1) << ". " << s.subjects[i].name << " - ";
            if (s.subjects[i].hasMark) cout << s.subjects[i].mark;
            else cout << "(no mark yet)";
            cout << "\n";
        }
    }
    cout << "===========================\n";
}

//MENUS (Adapted for BST)

void menuEnterNewStudent(Node*& root) {
    while (true) {
        Student s;
        cout << "\n--- Enter New Student (BST) ---\n";
        s.id = readInt("Enter student ID (integer): ");

        // Check duplicate BEFORE asking for details (Optimization)
        if (searchBST(root, s.id) != nullptr) {
            cout << "ID already exists.\n";
            continue;
        }

        cout << "Enter name   : "; getline(cin, s.name);
        cout << "Enter course : "; getline(cin, s.course);

        cout << "\nEnter subjects (type 0 to finish):\n";
        while (true) {
            SubjectRecord sub;
            cout << "Subject name: "; getline(cin, sub.name);
            if (sub.name == "0") {
                if (s.subjects.empty()) {
                    cout << "Must have at least one subject.\n"; continue;
                }
                break;
            }
            sub.hasMark = false; sub.mark = 0;
            s.subjects.push_back(sub);
        }

        // INSERT INTO BST
        insertBST(root, s);

        int choice = readInt("\n1. Add another\n2. Return\nChoice: ");
        if (choice == 2) return;
    }
}

void menuSearchStudent(Node* root) {
    if (root == nullptr) { cout << "\nNo students in tree.\n"; return; }

    while (true) {
        cout << "\n--- Search Student (BST Search) ---\n";
        int targetId = readInt("Enter ID to search: ");

        // SEARCH BST
        Student* result = searchBST(root, targetId);

        if (result != nullptr) showStudent(*result);
        else cout << "ID " << targetId << " not found.\n";

        int choice = readInt("\n1. Search again\n2. Return\nChoice: ");
        if (choice == 2) return;
    }
}

void menuInsertMarks(Node* root) {
    if (root == nullptr) { cout << "\nNo students in tree.\n"; return; }

    while (true) {
        cout << "\n--- Insert Marks ---\n";
        int targetId = readInt("Enter ID: ");

        // SEARCH BST
        Student* result = searchBST(root, targetId);

        if (result == nullptr) {
            cout << "ID not found.\n";
        } else {
            showStudent(*result);
            cout << "\nEnter marks:\n";
            for (auto &sub : result->subjects) {
                cout << "Subject: " << sub.name << "\n";
                sub.mark = readDouble("Enter mark: ");
                sub.hasMark = true;
            }
            cout << "Marks updated.\n";
            showStudent(*result);
        }

        int choice = readInt("\n1. Another student\n2. Return\nChoice: ");
        if (choice == 2) return;
    }
}

void showMenu() {
    cout << "\n==============================\n";
    cout << "  Student ID Search System\n";
    cout << "  (Optimized: Binary Search Tree)\n";
    cout << "==============================\n";
    cout << "1. Enter new student\n";
    cout << "2. Search student by ID\n";
    cout << "3. Insert marks\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

//MAIN
int main() {
    Node* root = nullptr;
    int choice;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cout << "Wrong input.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: menuEnterNewStudent(root); break;
            case 2: menuSearchStudent(root); break;
            case 3: menuInsertMarks(root); break;
            case 4: cout << "Goodbye!\n"; return 0;
            default: cout << "Wrong input.\n"; break;
        }
    }
}
