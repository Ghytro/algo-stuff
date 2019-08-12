/**<   This function converts the decimal number to rational fraction */
/**<   Enter the numbers up to 6 decimal places */

#include <iostream>
#include <cmath>
#include <string>

long long GCD(long long a, long long b)
{
    if (a % b == 0)
        return b;
    return GCD(b, a % b);
}

/** @brief Conversion itself
 *
 * \param A decimal number
 * \return A pair of values, first is numerator, second - denominator
 *
 */

std::pair<long long, long long> doubletofraction(long double value) //first value - numerator, second - denominator
{
    std::string svalue = std::to_string(value);

    while (svalue[svalue.length() - 1] == '0')
        svalue.erase(svalue.length() - 1, 1);

    int dotpos = svalue.find(".");
    long long integer = std::atoi(svalue.substr(0, dotpos + 1).c_str());
    long long denominator = std::pow(10, svalue.substr(dotpos + 1, svalue.length() - dotpos).length());
    long long numerator = std::atoi(svalue.substr(dotpos + 1, svalue.length() - dotpos).c_str());

    if (denominator == 99) //10^2 == 99 and IDK why
        denominator++;

    long long gDen = GCD(numerator, denominator);
    numerator /= gDen;
    denominator /= gDen;
    numerator += integer*denominator;
    return std::make_pair(numerator, denominator);
}

int main()
{
    /**< INSERT CODE HERE */
    return 0;
}
