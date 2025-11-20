/*
 * ===================================================================
 * GROUP PROJECT: ALGORITHM & DATA STRUCTURE
 * TOPIC: University Student Record Search (Baseline vs. Optimized)
 *
 * This program simulates and compares two methods for storing and
 * searching student records by their ID.
 *
 * 1. Baseline: Stores students in an unsorted std::vector.
 * - Search is a Linear Search (O(n)).
 * 2. Optimized: Stores students in a Binary Search Tree (BST).
 * - Search is a Binary Search (O(log n)).
 * ===================================================================
 */

#include <iostream>
#include <string>
#include <vector> // For the Baseline solution
#include <chrono> // For timing
#include <memory> // For smart pointers (in BST)

/*
 * -------------------------------------------------------------------
 * DATA STRUCTURE: Student
 * A simple struct to represent a student's record.
 * -------------------------------------------------------------------
 */
struct Student {
    int id;
    std::string name;
    double marks;

    Student(int i, std::string n, double m) : id(i), name(n), marks(m) {}

    // Helper to print student details
    void print() const {
        std::cout << "  ID:    " << id << "\n"
                  << "  Name:  " << name << "\n"
                  << "  Marks: " << marks << std::endl;
    }
};

/*
 * ===================================================================
 * 1. BASELINE SOLUTION (Unsorted Vector)
 * ===================================================================
 */
class BaselineDatabase {
private:
    // Uses a simple vector. New students are added to the end.
    std::vector<Student> m_students;
    int m_comparisons = 0; // Counter for analysis

public:
    int getComparisons() {
        int temp = m_comparisons;
        m_comparisons = 0; // Reset after reading
        return temp;
    }

    // Add a new student.
    // Time Complexity: O(1) (on average)
    void addStudent(const Student& s) {
        m_students.push_back(s);
    }

    // Find a student using Linear Search.
    // Time Complexity: O(n)
    Student* findStudent(int id) {
        m_comparisons = 0; // Reset counter
        for (Student& s : m_students) {
            m_comparisons++; // Increment for every check
            if (s.id == id) {
                return &s; // Found!
            }
        }
        return nullptr; // Not found
    }
};

/*
 * ===================================================================
 * 2. OPTIMIZED SOLUTION (Binary Search Tree)
 * ===================================================================
 */
class OptimizedDatabase {
private:
    // --- BST Node ---
    struct Node {
        Student data;
        std::unique_ptr<Node> left;  // Smart pointer for left child
        std::unique_ptr<Node> right; // Smart pointer for right child

        // Constructor
        Node(const Student& s) : data(s), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> m_root; // The root of the tree
    int m_comparisons = 0; // Counter for analysis

    // --- Recursive Helper Functions ---

    // Recursive function to insert a node
    // Time Complexity: O(log n) on average
    void insert(std::unique_ptr<Node>& node, const Student& s) {
        if (node == nullptr) {
            node = std::make_unique<Node>(s);
            return;
        }

        if (s.id < node->data.id) {
            insert(node->left, s);
        } else {
            insert(node->right, s);
        }
    }

    // Recursive function to search for a node
    // Time Complexity: O(log n) on average
    Student* find(Node* node, int id) {
        if (node == nullptr) {
            return nullptr; // Not found
        }
        
        m_comparisons++; // A comparison is made at this node

        if (id == node->data.id) {
            return &node->data; // Found!
        } else if (id < node->data.id) {
            return find(node->left.get(), id); // Search left
        } else {
            return find(node->right.get(), id); // Search right
        }
    }

public:
    OptimizedDatabase() : m_root(nullptr) {} // Constructor

    int getComparisons() {
        int temp = m_comparisons;
        m_comparisons = 0; // Reset after reading
        return temp;
    }

    // Public addStudent function (calls recursive helper)
    void addStudent(const Student& s) {
        insert(m_root, s);
    }

    // Public findStudent function (calls recursive helper)
    Student* findStudent(int id) {
        m_comparisons = 0; // Reset counter
        return find(m_root.get(), id);
    }
};

/*
 * -------------------------------------------------------------------
 * main()
 * A function to simulate and demonstrate both databases.
 * -------------------------------------------------------------------
 */
int main() {
    std::cout << "===== Student ID Search Simulation =====" << std::endl;

    // --- Define our student data ---
    // We add them in a jumbled order to show the BST works
    std::vector<Student> students = {
        Student(100, "Alice", 85.5),
        Student(50, "Bob", 92.0),
        Student(150, "Charlie", 78.0),
        Student(25, "David", 66.5),
        Student(75, "Eve", 95.0),
        Student(125, "Frank", 81.0),
        Student(175, "Grace", 88.0) // This is the one we will search for
    };

    // --- Setup the databases ---
    BaselineDatabase db_baseline;
    OptimizedDatabase db_optimized;

    for (const auto& s : students) {
        db_baseline.addStudent(s);
        db_optimized.addStudent(s);
    }

    int idToFind = 175; // The ID we want to find (Grace)

    // --- 1. Demonstrate Baseline (Linear Search) ---
    std::cout << "\n--- 1. Baseline (Unsorted Vector) Test ---" << std::endl;
    std::cout << "Searching for ID: " << idToFind << std::endl;

    Student* s_baseline = db_baseline.findStudent(idToFind);
    if (s_baseline != nullptr) {
        std::cout << "Found student (Baseline):" << std::endl;
        s_baseline->print();
    } else {
        std::cout << "Student not found." << std::endl;
    }
    std::cout << "  Comparisons made: " << db_baseline.getComparisons() << std::endl;
    std::cout << "  *** Analysis: This is O(n). It checked 7 items. ***" << std::endl;


    // 2. Demonstrate Optimized (BST) Search
    std::cout << "\n--- 2. Optimized (Binary Search Tree) Test ---" << std::endl;
    std::cout << "Searching for ID: " << idToFind << std::endl;
    
    Student* s_optimized = db_optimized.findStudent(idToFind);
    if (s_optimized != nullptr) {
        std::cout << "Found student (Optimized):" << std::endl;
        s_optimized->print();
    } else {
        std::cout << "Student not found." << std::endl;
    }
    std::cout << "  Comparisons made: " << db_optimized.getComparisons() << std::endl;
    std::cout << "  *** Analysis: This is O(log n). It only checked 3 items. ***" << std::endl;

    std::cout << "\n===== Simulation Complete =====" << std::endl;
    return 0;
}
