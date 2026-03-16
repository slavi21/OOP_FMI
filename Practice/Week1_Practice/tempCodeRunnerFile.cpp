#include <iostream>

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
    OperaingSystem os;
};

void readName(char name[], int size) {

    int i = 0;
    char ch;

    while (i < size - 1) {
        std::cin.get(ch);  // Read character

        if (ch == '\n') {   // Stop at newline
            break;
        }

        name[i++] = ch;  // Store character
    }

    name[i] = '\0';  // Null terminate the string
}

// Функция за четене на операционната система
void readOperatingSystem(OperatingSystem &os) {
    int osChoice;
    std::cout << "Choose the operating system:\n";
    std::cout << "1. MAC\n";
    std::cout << "2. MICROSOFT_WINDOWS\n";
    std::cout << "3. LINUX\n";
    std::cout << "4. SOLARIS\n";
    std::cout << "Enter your choice (1-4): ";
    std::cin >> osChoice;

    // Присвояване на операционната система
    switch (osChoice) {
        case 1:
            os = OperatingSystem::MAC;
            break;
        case 2:
            os = OperatingSystem::MICROSOFT_WINDOWS;
            break;
        case 3:
            os = OperatingSystem::LINUX;
            break;
        case 4:
            os = OperatingSystem::SOLARIS;
            break;
        default:
            std::cout << "Invalid choice! Defaulting to MICROSOFT_WINDOWS.\n";
            os = OperatingSystem::MICROSOFT_WINDOWS;
            break;
    }
}

void clearBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void inputLaptop(Laptop& laptop) {
    std::cout << "Enter price: ";
    std::cin >> laptop.price;
    clearBuffer(); // ЗАДЪЛЖИТЕЛНО след cin >>

    std::cout << "Enter brand: ";
    // Чете до 99 символа или до нов ред и поставя \0
    std::cin.getline(laptop.brand, NAME_SIZE);

    std::cout << "Enter screen size: ";
    std::cin >> laptop.screenSize;

    std::cout << "Enter HDD capacity: ";
    std::cin >> laptop.hddCapacity;
    
    std::cout << "Has SSD (1/0): ";
    std::cin >> laptop.hasSSD;
    clearBuffer(); // ЗАДЪЛЖИТЕЛНО преди следващия getline

    std::cout << "Enter GPU model: ";
    std::cin.getline(laptop.gpuModel, NAME_SIZE);

    // Тук извикваш твоята функция за OS (вече поправена)
    // readOperatingSystem(laptop.os);
}

void printLaptopInfo(const Laptop &laptop) {
    std::cout << "\nLaptop details:\n";
    std::cout << "Brand: " << laptop.brand << std::endl;
    std::cout << "Price: " << laptop.price << std::endl;
    std::cout << "Screen size: " << laptop.screenSize << std::endl;
    std::cout << "HDD capacity: " << laptop.hddCapacity << " GB\n";
    std::cout << "GPU model: " << laptop.gpuModel << std::endl;
    std::cout << "Has SSD: " << (laptop.hasSSD ? "Yes" : "No") << std::endl;

    // Извеждаме операционната система
    std::cout << "Operating system: ";
    switch (laptop.os) {
        case OperatingSystem::MAC:
            std::cout << "MAC\n";
            break;
        case OperatingSystem::MICROSOFT_WINDOWS:
            std::cout << "Microsoft Windows\n";
            break;
        case OperatingSystem::LINUX:
            std::cout << "Linux\n";
            break;
        case OperatingSystem::SOLARIS:
            std::cout << "Solaris\n";
            break;
    }
}

int main() 
{
    Laptop myLaptop;

    

    // Отпечатваме информацията за лаптопа
    printLaptopInfo(myLaptop);

    return 0;
}