#include "Portfolio.hpp"

#include <iostream>

int main()
{
    Portfolio p("rates.txt");
    p.add(17, "BGN");
    p.add(20, "EUR");
    p.add(17, "USD");
    p.add(1000, "JPY");

    p.print();

    double sumInBGN = p.getAmount("BGN"); // 17 + 39.12 + 30.07 = 86.12

    std::cout << sumInBGN << std::endl;
    
    // Its possible that the data in the file
    // is not up to date and it might produce different 
    // results.
}