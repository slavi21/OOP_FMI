#include <iostream>
#include <limits>   // ЗАДЪЛЖИТЕЛНО за std::numeric_limits

constexpr int NAME_SIZE = 100;

enum class OperatingSystem {
    NONE = -1,
    MAC,
    MICROSOFT_WINDOWS,
    LINUX,
    SOLARIS
};

struct Laptop {
    double price;
    char brand[NAME_SIZE];
    double screenSize;
    int hddCapacity;
    char gpuModel[NAME_SIZE];
    bool hasSSD;
    OperatingSystem os; // ПОПРАВЕНО: името на типа
};

// Функция за изчистване на буфера
void clearBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Поправена функция за четене на имената (използваме вградената getline)
void readName(char name[], int size) {
    std::cin.getline(name, size);
}

void readOperatingSystem(OperatingSystem &os) {
    int osChoice;
    std::cout << "Choose the operating system:\n";
    std::cout << "1. MAC\n2. MICROSOFT_WINDOWS\n3. LINUX\n4. SOLARIS\n";
    std::cout << "Enter your choice (1-4): ";
    std::cin >> osChoice;
    clearBuffer(); // Винаги чистим след cin >> число

    switch (osChoice) {
        case 1: os = OperatingSystem::MAC; break;
        case 2: os = OperatingSystem::MICROSOFT_WINDOWS; break;
        case 3: os = OperatingSystem::LINUX; break;
        case 4: os = OperatingSystem::SOLARIS; break;
        default:
            std::cout << "Invalid choice! Defaulting to NONE.\n";
            os = OperatingSystem::NONE;
            break;
    }
}

void inputLaptop(Laptop& laptop) {
    std::cout << "Enter price: ";
    std::cin >> laptop.price;
    clearBuffer();

    std::cout << "Enter brand: ";
    readName(laptop.brand, NAME_SIZE);

    std::cout << "Enter screen size: ";
    std::cin >> laptop.screenSize;

    std::cout << "Enter HDD capacity: ";
    std::cin >> laptop.hddCapacity;
    
    std::cout << "Has SSD (1 for Yes, 0 for No): ";
    std::cin >> laptop.hasSSD;
    clearBuffer();

    std::cout << "Enter GPU model: ";
    readName(laptop.gpuModel, NAME_SIZE);

    readOperatingSystem(laptop.os);
}

void printLaptopInfo(const Laptop &laptop) {
    std::cout << "\n--- Laptop Details ---\n";
    std::cout << "Brand: " << laptop.brand << "\n";
    std::cout << "Price: " << laptop.price << "\n";
    std::cout << "Screen size: " << laptop.screenSize << "\"\n";
    std::cout << "HDD: " << laptop.hddCapacity << " GB\n";
    std::cout << "GPU: " << laptop.gpuModel << "\n";
    std::cout << "SSD: " << (laptop.hasSSD ? "Yes" : "No") << "\n";

    std::cout << "Operating system: ";
    switch (laptop.os) {
        case OperatingSystem::MAC: std::cout << "MAC\n"; break;
        case OperatingSystem::MICROSOFT_WINDOWS: std::cout << "Microsoft Windows\n"; break;
        case OperatingSystem::LINUX: std::cout << "Linux\n"; break;
        case OperatingSystem::SOLARIS: std::cout << "Solaris\n"; break;
        default: std::cout << "None\n"; break;
    }
}

int main() {
    Laptop myLaptop;

    // Вече извикваме функцията за въвеждане!
    inputLaptop(myLaptop);

    // Отпечатваме информацията за лаптопа
    printLaptopInfo(myLaptop);

    return 0;
}