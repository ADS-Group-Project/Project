#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

// Subject and Student structures
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

// Helper: safely read an integer
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

// Helper: safely read a double
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

// Linear search by ID
int linearSearchById(const vector<Student> &students, int targetId) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].id == targetId) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Show a single student's info
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

// MENU DISPLAY
void showMenu() {
    cout << "\n==============================\n";
    cout << "  Student ID Search System\n";
    cout << "  (Unsorted Array + Linear Search)\n";
    cout << "==============================\n";
    cout << "1. Enter new student\n";
    cout << "2. Search student by ID\n";
    cout << "3. Insert marks\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Option 1: Enter new student
void menuEnterNewStudent(vector<Student> &students) {
    while (true) {
        Student s;

        cout << "\n--- Enter New Student ---\n";
        s.id = readInt("Enter student ID (integer): ");

        if (linearSearchById(students, s.id) != -1) {
            cout << "ID already exists.\n";
            continue;
        }

        cout << "Enter name   : ";
        getline(cin, s.name);

        cout << "Enter course : ";
        getline(cin, s.course);

        cout << "\nEnter subjects (type 0 to finish):\n";

        while (true) {
            SubjectRecord sub;

            cout << "Subject name: ";
            getline(cin, sub.name);

            if (sub.name == "0") {
                if (s.subjects.empty()) {
                    cout << "Student must have at least one subject.\n";
                    continue;
                }
                break;
            }

            sub.hasMark = false;
            sub.mark = 0;
            s.subjects.push_back(sub);
        }

        students.push_back(s);
        cout << "Student added successfully!\n";

        int choice = readInt("\n1. Add another student\n2. Return to main menu\nChoice: ");
        if (choice == 2) return;
    }
}

// Option 2: Search student by ID
void menuSearchStudent(const vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo students added yet.\n";
        return;
    }

    while (true) {
        cout << "\n--- Search Student by ID ---\n";
        int targetId = readInt("Enter student ID: ");

        int index = linearSearchById(students, targetId);
        if (index != -1) showStudent(students[index]);
        else cout << "ID not found.\n";

        int choice = readInt("\n1. Search again\n2. Return to menu\nChoice: ");
        if (choice == 2) return;
    }
}

// Option 3: Insert marks
void menuInsertMarks(vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo students added yet.\n";
        return;
    }

    while (true) {
        cout << "\n--- Insert Marks ---\n";
        int targetId = readInt("Enter student ID: ");

        int index = linearSearchById(students, targetId);
        if (index == -1) {
            cout << "ID not found.\n";
        } else {
            Student &s = students[index];
            showStudent(s);

            cout << "\nEnter marks for each subject below.\n";

            for (size_t i = 0; i < s.subjects.size(); ++i) {
                cout << "\nSubject " << (i + 1) << ": " << s.subjects[i].name << "\n";
                double mark = readDouble("Enter mark: ");
                s.subjects[i].mark = mark;
                s.subjects[i].hasMark = true;
            }

            cout << "\nMarks updated.\n";
            showStudent(s);
        }

        int choice = readInt("\n1. Insert more marks\n2. Return to menu\nChoice: ");
        if (choice == 2) return;
    }
}

// MAIN
int main() {
    vector<Student> students;
    int choice;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Wrong input, enter 1–4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: menuEnterNewStudent(students); break;
            case 2: menuSearchStudent(students); break;
            case 3: menuInsertMarks(students); break;
            case 4: cout << "\nGoodbye!\n"; return 0;
            default: cout << "Wrong input, enter 1–4.\n"; break;
        }
    }
}
