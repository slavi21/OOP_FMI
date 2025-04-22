#include "Portfolio.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

#pragma warning (disable : 4996)

Portfolio::Portfolio(const char* ratesFile) 
    : entries(nullptr), size(0), capacity(0), rates(ratesFile) {}

                                              
Portfolio::Portfolio(const Portfolio& other)
    : entries(nullptr), size(0), capacity(0), rates(other.rates)
{
    copyFrom(other);
}

Portfolio& Portfolio::operator=(const Portfolio& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Portfolio::~Portfolio() {
    free();
}

void Portfolio::copyFrom(const Portfolio& other) {
    size = other.size;
    capacity = other.capacity;

    entries = new Entry[capacity];

    for (size_t i = 0; i < size; ++i)
    {
        entries[i] = other.entries[i];
    }
}

void Portfolio::free() {
    delete[] entries;
    entries = nullptr;
    size = capacity = 0;
    // rates.~ExchangeRates(); Just kidding ;)
}

void Portfolio::resize() {
    capacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;

    Entry* temp = new Entry[capacity];

    for (size_t i = 0; i < size; ++i)
    {
        temp[i] = entries[i];
    }

    delete[] entries;
    entries = temp;
}

void Portfolio::print() const {
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << entries[i].amount << " " << entries[i].currency << std::endl;
    }
    std::cout << "\nFrom rates:\n";
    rates.print();
}

void Portfolio::add(double amount, const char* currency) {
    if (size == capacity) {
        resize();
    }
    entries[size].amount = amount;
    strncpy(entries[size].currency, currency, MAX_CURRENCY_LENGTH - 1);
    entries[size].currency[MAX_CURRENCY_LENGTH - 1] = '\0';
    ++size;
}

double Portfolio::getAmount(const char* targetCurrency) const {
    double toReturn = 0.0;

    for (size_t i = 0; i < size; ++i)
    {
        toReturn += rates.convert(entries[i].amount, entries[i].currency, targetCurrency);
    }
    return toReturn;
}