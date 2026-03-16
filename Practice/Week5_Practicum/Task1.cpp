#include <iostream>

constexpr int MAX_STUDENTS = 100;
constexpr int NAME_SIZE = 100;
constexp int MAX_GRADES = 32;
constexp int FacultyNumber_SIZE = 11;

struct Subject{

};

struct Student{
    char firstName[MAX_SIZE];
    char secondName[MAX_SIZE];
    char facultyNumber[];
    char grades[];

    void addGrade(double grade){
        if(gradeCount < grades.size()){
            grades[gradeCount++] = grade;
        }
    }

    void removeGrade(){
        if(gradeCount > 0){
            grades[--gradeCount] = 0;
        }
    }

    void calculateAverageGrade() const{
        if(gradeCount == 0) return 0;
        double sum = 0;
        for(size_t i = 0; i < gradeCount; ++i){
            sum += grades[i];
        }
        return sum / gradeCount;
    }

    

    struct Teacher{
        char firstName[MAX_SIZE];
        char secondName[MAX_SIZE];
        char department[MAX_SIZE];
    

    };


}
