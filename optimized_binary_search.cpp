#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// --------- Subject and Student structures ---------
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

// --------- Helper: safely read an integer ---------
int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
            return value;
        } else {
            cout << "Wrong input, please enter another input (integer).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// --------- Helper: safely read a double ---------
double readDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
            return value;
        } else {
            cout << "Wrong input, please enter another input (number).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// --------- Binary search by ID (sorted by id) ---------
int binarySearchById(const vector<Student> &students, int targetId, int &steps) {
    int left = 0;
    int right = static_cast<int>(students.size()) - 1;
    steps = 0;

    while (left <= right) {
        steps++;  // Increment steps on each check
        int mid = left + (right - left) / 2;
        if (students[mid].id == targetId) {
            return mid;
        } else if (targetId < students[mid].id) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1; // not found
}

// --------- Insert student sorted by ID ---------
void insertStudentSorted(vector<Student> &students, const Student &newStudent) {
    int idx = binarySearchById(students, newStudent.id, idx);  // Not used, just for demonstration
    if (idx != -1) {
        cout << "ID " << newStudent.id << " already exists in the system.\n";
        return;
    }

    auto pos = lower_bound(
        students.begin(),
        students.end(),
        newStudent.id,
        [](const Student &s, int value) {
            return s.id < value;
        }
    );

    students.insert(pos, newStudent);
    cout << "Student with ID " << newStudent.id << " has been added successfully.\n";
}

// --------- Show a single student's info ---------
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
            if (s.subjects[i].hasMark) {
                cout << s.subjects[i].mark;
            } else {
                cout << "(no mark yet)";
            }
            cout << "\n";
        }
    }

    cout << "===========================\n";
}

// --------- Menu display ---------
void showMenu() {
    cout << "\n==============================\n";
    cout << "  Student ID Search System\n";
    cout << "  (Sorted Array + Binary Search)\n";
    cout << "==============================\n";
    cout << "1. Enter new student\n";
    cout << "2. Search student by ID\n";
    cout << "3. Insert marks\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// --------- Option 1: Enter new student (with many subjects) ---------
void menuEnterNewStudent(vector<Student> &students) {
    while (true) {
        Student s;

        cout << "\n--- Enter New Student ---\n";
        s.id = readInt("Enter student ID (integer): ");

        cout << "Enter name   : ";
        getline(cin, s.name);

        cout << "Enter course : ";
        getline(cin, s.course);

        // Enter multiple subjects
        cout << "\nNow enter subjects for this student.\n";
        cout << "Press \"Enter\" to add new subject or press \"0\" when you are done.\n";

        while (true) {
            SubjectRecord sub;
            cout << "Enter subject name (or 0 to finish): ";
            getline(cin, sub.name);

            if (sub.name == "0") {
                if (s.subjects.empty()) {
                    cout << "Student must have at least one subject.\n";
                    continue;
                } else {
                    break;
                }
            }

            sub.hasMark = false;
            sub.mark = 0.0;
            s.subjects.push_back(sub);
        }

        insertStudentSorted(students, s);

        // Ask user what next
        while (true) {
            int choice = readInt(
                "\nWhat do you want to do next?\n"
                "1. Enter another student\n"
                "2. Return to main menu\n"
                "Enter your choice: "
            );

            if (choice == 1) {
                // loop again to add another student
                break;
            } else if (choice == 2) {
                return; // back to main menu
            } else {
                cout << "Wrong input, please enter another input (1 or 2).\n";
            }
        }
    }
}

// --------- Option 2: Search student by ID ---------
void menuSearchStudent(const vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo students in the system yet. Please add some first.\n";
        return;
    }

    while (true) {
        cout << "\n--- Search Student by ID ---\n";
        int targetId = readInt("Enter student ID to search: ");
        int steps = 0; // Initialize steps counter

        int index = binarySearchById(students, targetId, steps);
        if (index != -1) {
            showStudent(students[index]);
            cout << "Steps taken to find the student: " << steps << "\n";
        } else {
            cout << "ID " << targetId << " not found in the system.\n";
        }

        // Ask user what next
        while (true) {
            int choice = readInt(
                "\nWhat do you want to do next?\n"
                "1. Search another ID\n"
                "2. Return to main menu\n"
                "Enter your choice: "
            );

            if (choice == 1) {
                // loop again to search another ID
                break;
            } else if (choice == 2) {
                return; // back to main menu
            } else {
                cout << "Wrong input, please enter another input (1 or 2).\n";
            }
        }
    }
}

// --------- Option 3: Insert marks for subjects ---------
void menuInsertMarks(vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo students in the system yet. Please add some first.\n";
        return;
    }

    while (true) {
        cout << "\n--- Insert Marks ---\n";
        int targetId = readInt("Enter student ID to insert marks: ");

        int index = binarySearchById(students, targetId, index); // Not used, just for demo
        if (index == -1) {
            cout << "ID " << targetId << " not found in the system.\n";
        } else {
            Student &s = students[index];
            if (s.subjects.empty()) {
                cout << "This student has no subjects registered.\n";
            } else {
                cout << "\nInserting marks for student:\n";
                showStudent(s);
                cout << "\nEnter marks for each subject.\n";
                cout << "(If you do not want to change a subject's mark, you can enter the same value again.)\n";

                for (size_t i = 0; i < s.subjects.size(); ++i) {
                    cout << "\nSubject " << (i + 1) << ": " << s.subjects[i].name << "\n";
                    double mark = readDouble("Enter mark: ");
                    s.subjects[i].mark = mark;
                    s.subjects[i].hasMark = true;
                }

                cout << "\nAll marks updated for this student.\n";
                showStudent(s);
            }
        }

        // Ask user what next
        while (true) {
            int choice = readInt(
                "\nWhat do you want to do next?\n"
                "1. Insert marks for another ID\n"
                "2. Return to main menu\n"
                "Enter your choice: "
            );

            if (choice == 1) {
                // loop again
                break;
            } else if (choice == 2) {
                return;
            } else {
                cout << "Wrong input, please enter another input (1 or 2).\n";
            }
        }
    }
}

// --------- main ---------
int main() {
    vector<Student> students;
    int choice;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Wrong input, please enter another input (1–4).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        switch (choice) {
            case 1:
                menuEnterNewStudent(students);
                break;
            case 2:
                menuSearchStudent(students);
                break;
            case 3:
                menuInsertMarks(students);
                break;
            case 4:
                cout << "\nExiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Wrong input, please enter another input (1–4).\n";
                break;
        }
    }

    return 0;
}
