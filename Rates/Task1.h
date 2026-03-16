#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>

class Student {
    std::string firstName;
    std::string lastName;
    int facultyNumber;
    std::array<double, 32> grades;
    size_t gradeCount;

public:
    Student(const std::string& firstName, const std::string& lastName, int facultyNumber)
        : firstName(firstName), lastName(lastName), facultyNumber(facultyNumber), gradeCount(0) {}

    void addGrade(double grade) {
        if (gradeCount < grades.size()) {
            grades[gradeCount++] = grade;
        }
    }

    void removeGrade() {
        if (gradeCount > 0) {
            grades[--gradeCount] = 0;
        }
    }

    double calculateAverageGrade() const {
        if (gradeCount == 0) return 0;
        double sum = 0;
        for (size_t i = 0; i < gradeCount; ++i) {
            sum += grades[i];
        }
        return sum / gradeCount;
    }

    int getFacultyNumber() const {
        return facultyNumber;
    }

    // Accessor methods to avoid external modification
    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
};

class Teacher {
    std::string firstName;
    std::string lastName;
    std::string department;

public:
    enum Department { Algebra, Geometry, ComputerScience };

    Teacher(const std::string& firstName, const std::string& lastName, Department department)
        : firstName(firstName), lastName(lastName), department(departmentToString(department)) {}

    // Accessor methods to avoid external modification
    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
    const std::string& getDepartment() const { return department; }

private:
    static std::string departmentToString(Department department) {
        switch (department) {
        case Algebra: return "Algebra";
        case Geometry: return "Geometry";
        case ComputerScience: return "Computer Science";
        default: return "Unknown";
        }
    }
};

class Subject {
    std::vector<Student> students;
    Teacher* teacher;
    static const size_t maxStudents = 100;

public:
    Subject() : teacher(nullptr) {}

    void addStudent(const Student& student) {
        if (students.size() < maxStudents) {
            students.push_back(student);
        }
    }

    void assignTeacher(Teacher* teacher) {
        this->teacher = teacher;
    }

    void serialize(const char* destinationFile) const {
        std::ofstream out(destinationFile, std::ios::binary);
        size_t teacherNameLength = teacher->getFirstName().size() + teacher->getLastName().size() + 1;
        out.write(reinterpret_cast<const char*>(&teacherNameLength), sizeof(teacherNameLength));
        out.write(teacher->getFirstName().c_str(), teacher->getFirstName().size());
        out.put(' ');
        out.write(teacher->getLastName().c_str(), teacher->getLastName().size());
        out.put('\n');
        for (const auto& student : students) {
            out.write(student.getFirstName().c_str(), student.getFirstName().size());
            out.put(' ');
            out.write(student.getLastName().c_str(), student.getLastName().size());
            out.put(' ');
            int facultyNumber = student.getFacultyNumber();
            out.write(reinterpret_cast<const char*>(&facultyNumber), sizeof(facultyNumber));
            out.put('\n');
        }
    }

    void deserialize(const char* sourceFile) {
        std::ifstream in(sourceFile, std::ios::binary);
        size_t teacherNameLength;
        in.read(reinterpret_cast<char*>(&teacherNameLength), sizeof(teacherNameLength));
        std::string teacherName(teacherNameLength, ' ');
        in.read(&teacherName[0], teacherNameLength);
        size_t spacePos = teacherName.find(' ');
        std::string teacherFirstName = teacherName.substr(0, spacePos);
        std::string teacherLastName = teacherName.substr(spacePos + 1);
        Teacher::Department dept = Teacher::ComputerScience; // default, needs to be read from file
        teacher = new Teacher(teacherFirstName, teacherLastName, dept);

        std::string firstName, lastName;
        int facultyNumber;
        while (in >> firstName >> lastName >> facultyNumber) {
            students.emplace_back(firstName, lastName, facultyNumber);
        }
    }

    // Accessor methods to avoid external modification
    const std::vector<Student>& getStudents() const { return students; }
    const Teacher* getTeacher() const { return teacher; }
};

int main() {
    Subject subject;
    Teacher teacher("Alice", "Johnson", Teacher::ComputerScience);
    subject.assignTeacher(&teacher);

    Student student1("John", "Doe", 12345);
    student1.addGrade(4.5);
    student1.addGrade(5.0);
    subject.addStudent(student1);

    Student student2("Jane", "Smith", 67890);
    student2.addGrade(3.5);
    student2.addGrade(4.0);
    subject.addStudent(student2);

    subject.serialize("subject.dat");

    Subject newSubject;
    newSubject.deserialize("subject.dat");

    return 0;
}