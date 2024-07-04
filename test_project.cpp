#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

class QuestionPaper {
public:
    struct Question {
        string question;
        string options[3];
        int correctOption;
    };

    vector<Question> questions;

    void loadQuestions(int subjectId) {
        switch (subjectId) {
            case 1: // Web Development
                questions = {
                    {"What is a software application for accessing information on the world wide web?",
                     {"1. Browser", "2. Server", "3. Laptop"}, 1},
                    {"What is a computer that runs websites?",
                     {"1. Web Browser", "2. Domain", "3. Server"}, 3},
                    {"Is WWW an electronic communications network that connects computer networks and organization computer facilities around the world?",
                     {"1. True", "2. False", "3. Not known"}, 1},
                    {"Which of the following is used to write C++ programs?",
                     {"1. Compiler", "2. Painter", "3. Text Editor"}, 1},
                    {"What does CPU stand for?",
                     {"1. Central Processing Unit", "2. Computer Personal Unit", "3. Central Processor Unit"}, 1}
                };
                break;
            case 2: // DBMS
                questions = {
                    {"What does SQL stand for?",
                     {"1. Structured Query Language", "2. Simple Query Language", "3. Strong Query Language"}, 1},
                    {"Which of the following is a database management system?",
                     {"1. MySQL", "2. HTML", "3. JSON"}, 1},
                    {"What is a primary key?",
                     {"1. A unique identifier for a record", "2. A foreign key", "3. An index"}, 1},
                    {"Which command is used to update data in a database?",
                     {"1. UPDATE", "2. INSERT", "3. SELECT"}, 1},
                    {"What is normalization?",
                     {"1. Organizing data to reduce redundancy", "2. Creating new databases", "3. Backing up data"}, 1}
                };
                break;
            // Add more cases for other subjects
            default:
                break;
        }
    }
};

class Student {
public:
    string name;
    int marks;
    string grade;
    int certificateNumber;
    int testId;

    Student() : marks(0), certificateNumber(0), testId(0) {}

    ~Student() {}

    void calculateGrade() {
        if (marks >= 80) {
            grade = "A";
        } else if (marks >= 60) {
            grade = "B";
        } else if (marks >= 40) {
            grade = "C";
        } else if (marks >= 20) {
            grade = "D";
        } else {
            grade = "Fail";
        }
    }

    void generateCertificateNumber() {
        certificateNumber = rand() % 90000 + 10000;  // 5 digit random number
    }

    // Overloaded << operator for Student
    friend ostream& operator<<(ostream &os, const Student &student) {
        os << student.name << "\t"
           << student.marks << "\t"
           << student.grade << "\t"
           << student.certificateNumber << "\t"
           << student.testId << endl;
        return os;
    }

    // Overloaded >> operator for Student
    friend istream& operator>>(istream &is, Student &student) {
        is >> student.name >> student.marks >> student.grade >> student.certificateNumber >> student.testId;
        return is;
    }
};

class AVLTree {
public:
    struct Node {
        int key;
        Node *left;
        Node *right;
        int height;
    };

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroy(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    void inOrder() const {
        inOrder(root);
    }

private:
    Node *root;

    Node *createNode(int key) {
        Node *node = new Node();
        node->key = key;
        node->left = node->right = nullptr;
        node->height = 1;
        return node;
    }

    void destroy(Node *node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    int height(Node *N) {
        return N == nullptr ? 0 : N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node *N) {
        return N == nullptr ? 0 : height(N->left) - height(N->right);
    }

    Node *insert(Node *node, int key) {
        if (node == nullptr)
            return createNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *remove(Node *root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node *temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;

                delete temp;
            } else {
                Node *temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = remove(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inOrder(Node *root) const {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }
};

class TestModule {
public:
    vector<string> courses = {
        "Web Development",
        "DBMS",
        "Full Stack Development",
        "Zero to Hero in C programming",
        "Cybersecurity",
        "Bigdata",
        "Datascience"
    };

    TestModule() {
        for (int i = 1; i <= courses.size(); ++i) {
            avlTree.insert(i);
        }
    }

    void takeTest() {
        srand(time(0));

        QuestionPaper qp;

        Student student;
        cout << "Enter your name: ";
        cin >> student.name;

        int subjectId;
        cout << "Select a course" << endl;
        for (int i = 0; i < courses.size(); i++) {
            cout << i + 1 << ". " << courses[i] << endl;
        }
        cout << "Enter an option: ";
        cin >> subjectId;
        student.testId = subjectId;

        qp.loadQuestions(subjectId);

        int ans;
        student.marks = 0;

        cout << "\nStarting the test...\n";
        for (const auto &question : qp.questions) {
            cout << question.question << endl;
            for (const auto &option : question.options) {
                cout << option << endl;
            }
            cout << "Enter the answer (option number only): ";
            cin >> ans;
            if (ans == question.correctOption) {
                student.marks += 20;
            }
        }

        student.calculateGrade();
        student.generateCertificateNumber();
        saveResult(student);
    }

    void saveResult(const Student &student) {
        ofstream file("new_ans.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Unable to open file for writing" << endl;
            return;
        }
        file << student.name << "\t"
             << student.marks << "\t"
             << student.grade << "\t"
             << student.certificateNumber << "\t"
             << student.testId << endl;
        file.close();
        cout << "Results saved successfully!" << endl;
    }

    void viewResults() const {
        ifstream file("new_ans.txt");
        if (!file.is_open()) {
            cerr << "Unable to open file for reading" << endl;
            return;
        }

        Student student;

        cout << left << setw(15) << "Name"
             << setw(10) << "Marks"
             << setw(10) << "Grade"
             << setw(20) << "Certificate Number"
             << setw(10) << "Test ID" << endl;
        cout << "------------------------------------------------------------" << endl;

        bool foundRecords = false;
        while (file >> student) {
            foundRecords = true;
            cout << left << setw(15) << student.name
                 << setw(10) << student.marks
                 << setw(10) << student.grade
                 << setw(20) << student.certificateNumber
                 << setw(10) << student.testId << endl;
        }

        file.close();

        if (!foundRecords) {
            cout << "No records found!" << endl;
        }
    }

    void displayAvailableTests() const {
        ifstream file("new_ans.txt");
        if (!file.is_open()) {
            cerr << "Unable to open file for reading" << endl;
            return;
        }

        vector<bool> testAttended(courses.size(), false);
        Student student;

        while (file >> student) {
            if (student.testId > 0 && student.testId <= courses.size()) {
                testAttended[student.testId - 1] = true;
            }
        }

        file.close();

        cout << left << setw(10) << "Test ID" << setw(25) << "Test Name" << endl;
        cout << "---------------------------" << endl;
        for (int i = 0; i < testAttended.size(); ++i) {
            if (!testAttended[i]) {
                cout << left << setw(10) << i + 1 << setw(25) << courses[i] << endl;
            }
        }
    }

    void retest() const {
        ifstream file("new_ans.txt");
        if (!file.is_open()) {
            cerr << "Unable to open file for reading" << endl;
            return;
        }

        Student student;
        bool foundRecords = false;

        cout << left << setw(15) << "Name"
             << setw(10) << "Marks"
             << setw(10) << "Grade"
             << setw(20) << "Certificate Number"
             << setw(10) << "Test ID" << endl;
        cout << "------------------------------------------------------------" << endl;

        while (file >> student) {
            if (student.grade == "Fail") {
                foundRecords = true;
                cout << left << setw(15) << student.name
                     << setw(10) << student.marks
                     << setw(10) << student.grade
                     << setw(20) << student.certificateNumber
                     << setw(10) << student.testId << endl;
            }
        }

        file.close();

        if (!foundRecords) {
            cout << "No failed tests found!" << endl;
        }
    }

    void rankCard() const {
        ifstream file("new_ans.txt");
        if (!file.is_open()) {
            cerr << "Unable to open file for reading" << endl;
            return;
        }

        unordered_map<int, int> testScores;
        Student student;

        while (file >> student) {
            testScores[student.testId] = max(testScores[student.testId], student.marks);
        }

        file.close();

        vector<pair<int, int>> sortedTests(testScores.begin(), testScores.end());
        sort(sortedTests.begin(), sortedTests.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.second > b.second;
        });

        cout << left << setw(10) << "Test ID" << setw(25) << "Test Name" << setw(10) << "Marks" << endl;
        cout << "---------------------------------------------" << endl;

        for (const auto &test : sortedTests) {
            cout << left << setw(10) << test.first
                 << setw(25) << courses[test.first - 1]
                 << setw(10) << test.second << endl;
        }
    }

    void editTest() {
        int testId;
        cout << "Enter the Test ID to delete: ";
        cin >> testId;
        avlTree.remove(testId);
        cout << "Test " << testId << " deleted. You can reattempt the test." << endl;

        // Update the results file to remove entries with the specified test ID
        ifstream inFile("new_ans.txt");
        if (!inFile.is_open()) {
            cerr << "Unable to open file for reading" << endl;
            return;
        }

        vector<Student> students;
        Student student;
        while (inFile >> student) {
            if (student.testId != testId) {
                students.push_back(student);
            }
        }
        inFile.close();

        ofstream outFile("new_ans.txt");
        if (!outFile.is_open()) {
            cerr << "Unable to open file for writing" << endl;
            return;
        }

        for (const auto &s : students) {
            outFile << s;
        }
        outFile.close();
        cout << "Corresponding results deleted successfully!" << endl;
    }

private:
    AVLTree avlTree;

    struct Graph {
        unordered_map<int, vector<int>> adjList;
        unordered_map<int, int> weights;

        void addEdge(int from, int to, int weight) {
            adjList[from].push_back(to);
            weights[to] = weight;
        }

        void topologicalSortUtil(int v, unordered_map<int, bool> &visited, stack<int> &Stack) const {
            visited[v] = true;

            for (auto i : adjList.at(v)) {
                if (!visited[i])
                    topologicalSortUtil(i, visited, Stack);
            }

            Stack.push(v);
        }

        void topologicalSort() const {
            stack<int> Stack;
            unordered_map<int, bool> visited;

            for (const auto &pair : adjList) {
                if (!visited[pair.first])
                    topologicalSortUtil(pair.first, visited, Stack);
            }

            cout << "\nTopological Sort of Tests based on Scores:\n";
            while (!Stack.empty()) {
                cout << Stack.top() << " ";
                Stack.pop();
            }
            cout << endl;
        }
    };
};

void displayMenu() {
    cout << "\n1. Take Test\n";
    cout << "2. View Results\n";
    cout << "3. Tests to be attended\n";
    cout << "4. Retest\n";
    cout << "5. Rank Card\n";
    cout << "6. Edit Test\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    TestModule tm;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                tm.takeTest();
                break;
            case 2:
                tm.viewResults();
                break;
            case 3:
                tm.displayAvailableTests();
                break;
            case 4:
                tm.retest();
                break;
            case 5:
                tm.rankCard();
                break;
            case 6:
                tm.editTest();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

