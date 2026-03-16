#include <iostream>

struct Point{
    double x, y;
};

struct Student{
    char name[30];// 30 bytes
    int age;      // 4 bytes
    double grade; // 8 bytes
    // 42 B, но заради подравняването ще излезе 48 B
    // Полетта в записите се подравняват до размер кратен на големината на най-голямото поле
    // В този случай най-голямото поле е double, което е 8 B
    // Така че Student ще заема 48 B
};

struct Array{
    int arr[10] = {0, 1, 2, 3 ,4, 5, 6, 7, 8, 9};
};

void testSizes()
{
    int a[10]; // масив от 10 елемента
    std::cout << sizeof(int) << ' ' << sizeof(a) << std::endl;
    std::cout<< sizeof(double) << ' ' << sizeof(Point) << std::endl;
    std::cout << sizeof(Student) << std::endl;

}

int main()
{
    testSizes();
    Array arr1;
    Array arrCopy = arr1; // копиране на масив
    int* firstElementPointer;
    firstElementPointer = &arrCopy.arr[0]; // указател към първия елемент на масива
    std::cout<< &arrCopy.arr[0] << std::endl; // печат на адреса на масива, тоест на адреса на първия му елемент
    std::cout<< firstElementPointer << std::endl; // печат на адреса на първия елемент
    

    return 0;
}