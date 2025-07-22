#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <iomanip>
#include <string>

constexpr size_t NUM_GRADES = 5;
constexpr size_t TOTAL_FIELDS = 7;

using StudentRecord = std::array<std::string, TOTAL_FIELDS>;
std::vector<StudentRecord> studentData;

// 🔍 Check if file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// 🧮 Calculate average from five grades
double computeAverage(const std::array<std::string, NUM_GRADES>& grades) {
    double sum = 0;
    for (const auto& gradeStr : grades) {
        sum += std::stod(gradeStr);
    }
    return sum / NUM_GRADES;
}

// 📚 Load file into memory
void loadFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        StudentRecord record;
        for (size_t i = 0; i < TOTAL_FIELDS; ++i) {
            ss >> record[i];
        }
        studentData.push_back(record);
    }
    file.close();
}

// 📝 Write memory contents back to file
void saveFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& record : studentData) {
        for (const auto& field : record) {
            file << field << " ";
        }
        file << "\n";
    }
    file.close();
}

// 🔄 Update student grades
void updateGradesById(const std::string& studentId) {
    for (auto& record : studentData) {
        if (record[0] == studentId) {
            std::array<std::string, NUM_GRADES> newGrades;
            std::cout << "Enter 5 new grades:\n";
            for (size_t i = 0; i < NUM_GRADES; ++i) {
                std::cin >> newGrades[i];
                record[2 + i] = newGrades[i]; // overwrite grade fields
            }
            record[7] = std::to_string(computeAverage(newGrades)); // update average
            std::cout << "Grades updated.\n";
            return;
        }
    }
    std::cout << "Student ID not found.\n";
}

// ➕ Add new student record
void appendNewRecord() {
    StudentRecord record;
    std::cout << "Enter student ID and name:\n";
    std::cin >> record[0] >> record[1];

    std::array<std::string, NUM_GRADES> grades;
    std::cout << "Enter 5 grades:\n";
    for (size_t i = 0; i < NUM_GRADES; ++i) {
        std::cin >> grades[i];
        record[2 + i] = grades[i];
    }

    record[7] = std::to_string(computeAverage(grades));
    studentData.push_back(record);
    std::cout << "Record added.\n";
}

int main() {
    const std::string filename = "grades.txt";

    // Create file if it doesn't exist
    if (!fileExists(filename)) {
        std::ofstream file(filename); // Creates empty file
        file.close();
        std::cout << "File created.\n";
    }

    // Load existing records
    loadFile(filename);
    std::cout << "Records loaded: " << studentData.size() << "\n";

    // ✏️ Menu
    char choice;
    do {
        std::cout << "\n(A)dd new record, (U)pdate grades, (S)ave and exit: ";
        std::cin >> choice;

        switch (toupper(choice)) {
            case 'A': appendNewRecord(); break;
            case 'U': {
                std::string id;
                std::cout << "Enter Student ID to update: ";
                std::cin >> id;
                updateGradesById(id);
                break;
            }
            case 'S': saveFile(filename); std::cout << "File saved.\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (toupper(choice) != 'S');

    return 0;
}
