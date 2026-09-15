#include <iostream>  // used for "cout" and "cin" 
#include <vector>    // used to store multiple students 
#include <fstream>   // used to read the file 
#include <iomanip>   // used for management of words consol (mainly "setw()" 
#include <algorithm>   // used for short() or remove_if() 
#include <limits>      // used for handling of input 

using namespace std;

// ==================== STUDENT CLASS ====================

class Student {
private:
    int id;
    string name;
    float marks;

public:
    Student(int id = 0, string name = "", float marks = 0.0)
        : id(id), name(name), marks(marks) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    float getMarks() const {
        return marks;
    }

    string getGrade() const {
        if (marks >= 80)
            return "A+";
        else if (marks >= 70)
            return "A";
        else if (marks >= 60)
            return "B";
        else if (marks >= 50)
            return "C";
        else if (marks >= 40)
            return "D";
        else
            return "F";
    }

    void display() const {
        cout << left
             << setw(8) << id
             << setw(25) << name
             << setw(12) << marks
             << setw(10) << getGrade()
             << endl;
    }
};

// ==================== STUDENT MANAGER ====================

class StudentManager {
private:
    vector<Student> students;
    const string filename = "students.txt";

public:

    // Add a new student
    void addStudent() {
        int id;
        string name;
        float marks;

        cout << "\nEnter Student ID: ";
        cin >> id;

        // Check duplicate ID
        for (const Student& student : students) {
            if (student.getId() == id) {
                cout << "Student ID already exists!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Marks (0-100): ";
        cin >> marks;

        if (marks < 0 || marks > 100) {
            cout << "Invalid marks!\n";
            return;
        }

        students.push_back(Student(id, name, marks));

        saveToFile();

        cout << "Student added successfully!\n";
    }

    // Display all students
    void displayStudents() const {
        if (students.empty()) {
            cout << "\nNo student records found.\n";
            return;
        }

        cout << "\n================ STUDENT RECORDS ================\n";

        cout << left
             << setw(8) << "ID"
             << setw(25) << "Name"
             << setw(12) << "Marks"
             << setw(10) << "Grade"
             << endl;

        cout << string(55, '-') << endl;

        for (const Student& student : students) {
            student.display();
        }
    }

    // Search student by ID
    void searchStudent() const {
        int id;

        cout << "\nEnter Student ID to search: ";
        cin >> id;

        for (const Student& student : students) {
            if (student.getId() == id) {
                cout << "\nStudent Found:\n";
                cout << string(30, '-') << endl;
                cout << "ID:     " << student.getId() << endl;
                cout << "Name:   " << student.getName() << endl;
                cout << "Marks:  " << student.getMarks() << endl;
                cout << "Grade:  " << student.getGrade() << endl;
                return;
            }
        }

        cout << "Student not found.\n";
    }

    // Update student
    void updateStudent() {
        int id;

        cout << "\nEnter Student ID to update: ";
        cin >> id;

        for (Student& student : students) {
            if (student.getId() == id) {

                string newName;
                float newMarks;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new name: ";
                getline(cin, newName);

                cout << "Enter new marks: ";
                cin >> newMarks;

                if (newMarks < 0 || newMarks > 100) {
                    cout << "Invalid marks!\n";
                    return;
                }

                // Replace the student record
                student = Student(id, newName, newMarks);

                saveToFile();

                cout << "Student updated successfully!\n";
                return;
            }
        }

        cout << "Student not found.\n";
    }

    // Delete student
    void deleteStudent() {
        int id;

        cout << "\nEnter Student ID to delete: ";
        cin >> id;

        auto it = remove_if(
            students.begin(),
            students.end(),
            [id](const Student& student) {
                return student.getId() == id;
            }
        );

        if (it != students.end()) {
            students.erase(it, students.end());

            saveToFile();

            cout << "Student deleted successfully!\n";
        }
        else {
            cout << "Student not found.\n";
        }
    }

    // Sort students by marks
    void sortByMarks() {
        sort(
            students.begin(),
            students.end(),
            [](const Student& a, const Student& b) {
                return a.getMarks() > b.getMarks();
            }
        );

        cout << "\nStudents sorted by marks successfully!\n";
    }

    // Save records to file
    void saveToFile() const {
        ofstream file(filename);

        if (!file) {
            cout << "Error: Could not save data.\n";
            return;
        }

        for (const Student& student : students) {
            file << student.getId() << "|"
                 << student.getName() << "|"
                 << student.getMarks() << endl;
        }

        file.close();
    }

    // Load records from file
    void loadFromFile() {
        ifstream file(filename);

        if (!file)
            return;

        int id;
        float marks;
        string name;

        while (file >> id) {
            file.ignore();

            getline(file, name, '|');
            file >> marks;

            students.push_back(Student(id, name, marks));
        }

        file.close();
    }
};

// ==================== MENU ====================

void showMenu() {
    cout << "\n\n========================================\n";
    cout << "       STUDENT MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Sort Students by Marks\n";
    cout << "7. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

// ==================== MAIN FUNCTION ====================

int main() {

    StudentManager manager;

    // Load existing records
    manager.loadFromFile();

    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {

            case 1:
                manager.addStudent();
                break;

            case 2:
                manager.displayStudents();
                break;

            case 3:
                manager.searchStudent();
                break;

            case 4:
                manager.updateStudent();
                break;

            case 5:
                manager.deleteStudent();
                break;

            case 6:
                manager.sortByMarks();
                break;

            case 7:
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}