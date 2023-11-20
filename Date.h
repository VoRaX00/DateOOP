#pragma once
#include <iostream>
using namespace std;

class Date
{
private:
    unsigned year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short min;
    unsigned short sec;
    bool isOurEra;

public:
    Date();
    Date(unsigned _year, unsigned short _month, unsigned short _day,
         unsigned short _hour, unsigned short _min, unsigned short _sec, bool era);

    Date add(unsigned year, unsigned short month, unsigned short day,
             unsigned short hour, unsigned short min, unsigned short sec, bool era);

    Date subtract(unsigned year, unsigned short month, unsigned short day,
                  unsigned short hour, unsigned short min, unsigned short sec, bool era);

    ~Date();

    Date operator+(const Date &date);
    void operator=(const Date &date);
    void operator+=(const Date &date);
    Date operator-(const Date &date);
    void operator-=(const Date &date);
    bool operator==(const Date &date);
    bool operator>(const Date &date);
    bool operator<(const Date &date);

    friend ostream &operator<<(ostream &out, const Date &date);

private:
    unsigned short daysInMonth();
    void adjustOverflow();
    void adjustUnderflow(int &year, int &month, int &day,
                         int &hour, int &min, int &sec, bool &era);
};

// ostream &operator<<(ostream &out, const Date &date)
// {
//     out << "Year: " << date.year << " Month: " << date.month << " Day: " << date.day
//         << " Hour: " << date.hour << " Min: " << date.min << " Sec: " << date.sec << date.isOurEra
//         ? " our era"
//         : " before our era";
//     return out;
// }