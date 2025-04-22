#ifndef __EXCHANGE_RATES_H__
#define __EXCHANGE_RATES_H__
#endif

constexpr unsigned short MAX_CURRENCY_LENGTH = 4;
constexpr unsigned short INITIAL_CAPACITY = 8;

class ExchangeRates {
public:
    ExchangeRates(const char*);
    ExchangeRates(const ExchangeRates&);
    ExchangeRates& operator=(const ExchangeRates&);
    ~ExchangeRates();

    double convert(double, const char*, const char*) const;
    void print() const;

private:
    struct Rate {
        char from[MAX_CURRENCY_LENGTH];
        char to[MAX_CURRENCY_LENGTH];
        double rate;
    };

    Rate* rates;
    unsigned count;
    unsigned capacity;

    void resize();
    void copyFrom(const ExchangeRates&);
    void free();
};