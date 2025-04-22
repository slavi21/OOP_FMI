#include "ExchangeRates.hpp"

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>

#pragma warning (disable : 4996)


ExchangeRates::ExchangeRates(const char* filename) : rates(nullptr), count(0), capacity(0) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open exchange rate file.");
    }

    char from[MAX_CURRENCY_LENGTH];
    char to[MAX_CURRENCY_LENGTH];
    double rate;

    while (inFile >> from >> to >> rate) {
        if (count == capacity) {
            resize();
        }

        strncpy(rates[count].from, from, MAX_CURRENCY_LENGTH - 1);
        rates[count].from[MAX_CURRENCY_LENGTH - 1] = '\0';

        strncpy(rates[count].to, to, MAX_CURRENCY_LENGTH - 1);
        rates[count].to[MAX_CURRENCY_LENGTH - 1] = '\0';

        rates[count].rate = rate;

        ++count;
    }

    inFile.close();
}

void ExchangeRates::resize() {
    capacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;

    Rate* temp = new Rate[capacity];

    for (size_t i = 0; i < count; ++i)
    {
        temp[i] = rates[i];
    }

    delete[] rates;
    rates = temp;
}

ExchangeRates::ExchangeRates(const ExchangeRates& other) {
    copyFrom(other);
}

ExchangeRates& ExchangeRates::operator=(const ExchangeRates& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ExchangeRates::~ExchangeRates() {
    free();
}

void ExchangeRates::free() {
    delete[] rates;
    rates = nullptr;
    capacity = count = 0;
}

void ExchangeRates::copyFrom(const ExchangeRates& other) {

    // Armqnka brat, prowerka tuka eiiii 
    count = other.count;
    capacity = other.capacity;

    rates = new Rate[capacity];

    for (size_t i = 0; i < count; ++i)
    {
        rates[i] = other.rates[i];
    }
    
    
}
    
double ExchangeRates::convert(double amount, const char* from, const char* to) const {
    if (strcmp(from, to) == 0) 
        return amount;

    for (size_t i = 0; i < count; ++i)
    {
        if (strcmp(rates[i].from, from) == 0 &&
            strcmp(rates[i].to, to) == 0) {
            return rates[i].rate * amount;
        }
    }

    throw std::runtime_error("No exchange rate found in the file.");
}    

void ExchangeRates::print() const {
    for (size_t i = 0; i < count; ++i)
    {
        std::cout << rates[i].from << " " << rates[i].to << " " << rates[i].rate << std::endl;
    }
}