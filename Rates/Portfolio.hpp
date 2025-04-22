#include "ExchangeRates.hpp"

#ifndef __PORTFOLIO__
#define __PORTFOLIO__
#endif

class Portfolio {
public:
 
    Portfolio(const char* ratesFile);
    Portfolio(const Portfolio&);
    Portfolio& operator=(const Portfolio&);
    ~Portfolio();

    void add(double, const char*);
    double getAmount(const char*) const;
    void print() const;

private:
    struct Entry{
        double amount;
        char currency[MAX_CURRENCY_LENGTH];
    };

    Entry* entries;
    unsigned size;
    unsigned capacity;

    ExchangeRates rates;

    void copyFrom(const Portfolio&);
    void free();
    void resize();
};