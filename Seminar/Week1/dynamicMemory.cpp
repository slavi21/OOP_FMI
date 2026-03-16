#include <iostream>
#include <new>

int main() {
    int** allocations = new int*[100000]; // array of pointers to track allocations
    // променливата allocations съхранява адреса на началото на масив от 100 000 пойнтъра, 
    // това е указател към указатели
    // масив от пойнтъри и всеки пойнтър сочи към масив от числа  
    int count = 0;


    // while(true == true) винаги истина, безкраен цикъл
    while (true) {
        allocations[count] = new(std::nothrow) int[1'000'000'000];
        // на позияция count в масива от пойнтъри запиши динамичен масив от 1 000 000 000 цели числа,
        // ако се препълни върни nullptr 
        if (allocations[count] == nullptr) {
            std::cout << "Failed to allocate memory for index " << count << std::endl;
            break;
        }
        count++;
    }

    // Cleanup
    for (int i = 0; i < count; i++) {
        delete[] allocations[i];
        // трябва да минем през всеки блок от памет и да го изтрием
    }
    delete[] allocations;
    // накрая трябва да изтрием и адресите, които са сочели към тези блокове памет, които вече изтрихме

    return 0;
}