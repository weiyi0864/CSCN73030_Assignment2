#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Define a struct to store student data
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
    std::string email;
};

int main() {
    // Vector to store student data
    std::vector<STUDENT_DATA> students;


    // Open the student data file
    std::ifstream file("StudentData.txt");

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open the StudentData.txt file!" << std::endl;
        return -1;
    }

    // Read each line from the file
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstName, lastName;

        // Parse the comma-separated name pair
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName)) {
            // Create a student object with names and add to vector
            STUDENT_DATA student = { firstName, lastName, "" }; // Email will be added in pre-release mode
            students.push_back(student);
        }
    }

    // Close the student data file
    file.close();

#ifdef PRE_RELEASE
    // Pre-release mode: print a message indicating pre-release version
    std::cout << "PRE-RELEASE Version" << std::endl;

    // Open the email data file
    std::ifstream emailFile("StudentData_Emails.txt");
    if (!emailFile.is_open()) {
        std::cerr << "Failed to open the StudentData_Emails.txt file!" << std::endl;
        return -1;
    }

    int index = 0;
    // Read the name and email data from the file
    while (std::getline(emailFile, line)) {
        std::stringstream ss(line);
        std::string firstName, lastName, email;

        // Parse the name and email (comma-separated)
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName, ',') && std::getline(ss, email)) {
            if (index < students.size()) {
                // Match the email to the corresponding student
                students[index].email = email;
            }
        }
        ++index;
    }

    // Close the email data file
    emailFile.close();

#else
    // Standard mode: print a message indicating standard version
    std::cout << "STANDARD version" << std::endl;
#endif

#ifdef _DEBUG
    // Debug mode: print all student information
    for (const auto& student : students) {
        std::cout << "Name: " << student.firstName << " " << student.lastName;

#ifdef PRE_RELEASE
        std::cout << " Email: " << student.email;
#endif

        std::cout << std::endl;
    }
#endif

    return 0;
}
