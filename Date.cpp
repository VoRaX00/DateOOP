#include "Date.h"
#include <vector>
#include <tuple>

Date::Date()
{
    year = 1960;
    month = 1;
    day = 1;
    hour = 0;
    min = 0;
    sec = 0;
    isOurEra = true;
}

Date::Date(unsigned _year, unsigned short _month, unsigned short _day, unsigned short _hour, unsigned short _min, unsigned short _sec, bool era)
{
    year = _year;
    month = _month;
    day = _day;
    hour = _hour;
    min = _min;
    sec = _sec;
    isOurEra = era;
    adjustOverflow();
}

Date Date::add(unsigned year, unsigned short month, unsigned short day,
               unsigned short hour, unsigned short min, unsigned short sec, bool era)
{
    Date sum = *this + Date(year, month, day, hour, min, sec, era);
    return sum;
}

Date Date::subtract(unsigned year, unsigned short month, unsigned short day,
                    unsigned short hour, unsigned short min, unsigned short sec, bool era)
{
    Date diff = *this - Date(year, month, day, hour, min, sec, era);
    return diff;
}

Date::~Date()
{
}

unsigned short Date::daysInMonth()
{
    const vector<unsigned short> days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned short cntDays = days[month];

    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
    {
        cntDays++;
    }

    return cntDays;
}

void Date::adjustOverflow()
{
    while (sec >= 60)
    {
        sec -= 60;
        min++;
    }
    while (min >= 60)
    {
        min -= 60;
        hour++;
    }
    while (hour >= 24)
    {
        hour -= 24;
        day++;
    }

    while (month > 12)
    {
        month -= 12;
        year++;
    }

    while (day > daysInMonth())
    {
        day -= daysInMonth();
        month++;

        if (month > 12)
        {
            month -= 12;
            year++;
        }
    }
}

void Date::adjustUnderflow(int &year, int &month, int &day,
                           int &hour, int &min, int &sec, bool &era)
{
    while (sec < 0)
    {
        sec += 60;
        min--;
    }
    while (min < 0)
    {
        min += 60;
        hour--;
    }
    while (hour < 0)
    {
        hour += 24;
        day--;
    }

    while (month < 1)
    {
        month += 12;
        year--;
    }

    while (day < 1)
    {
        month--;
        if (month < 1)
        {
            month += 12;
            year--;
        }
        day += daysInMonth();
    }
}

Date Date::operator+(const Date &date)
{
    Date sum;
    sum.sec = date.sec + sec;
    sum.min = date.min + min;
    sum.hour = date.hour + hour;
    sum.day = date.day + day;
    sum.month = date.month + month;
    sum.year = date.year + year;
    sum.adjustOverflow();
    return sum;
}

void Date::operator=(const Date &date)
{
    tie(year, month, day, hour, min, sec, isOurEra) = tie(date.year, date.month, date.day, date.hour, date.min, date.sec, date.isOurEra);
}

void Date::operator+=(const Date &date)
{
    *this = *this + date;
}

Date Date::operator-(const Date &date)
{
    int sec = sec - date.sec;
    int min = min - date.min;
    int hour = hour - date.hour;
    int day = day - date.day;
    int month = month - date.month;
    int year = year - date.year;
    bool era = ((year > 0) ? true : false);
    adjustUnderflow(year, month, hour, day, hour, sec, era);
    Date diff(year, month, hour, day, hour, sec, era);
    return diff;
}

void Date::operator-=(const Date &date)
{
    *this = *this - date;
}

bool Date::operator==(const Date &date)
{
    return tie(year, month, day, hour, min, sec, isOurEra) ==
           tie(date.year, date.month, date.day, date.hour, date.min, date.sec, date.isOurEra);
}

bool Date::operator>(const Date &date)
{
    if (isOurEra == date.isOurEra && isOurEra)
        return tie(year, month, day, hour, min, sec) >
               tie(date.year, date.month, date.day, date.hour, date.min, date.sec);
    else if (isOurEra == date.isOurEra)
        return tie(year, month, day, hour, min, sec) <
               tie(date.year, date.month, date.day, date.hour, date.min, date.sec);
    else
        return isOurEra;
}

bool Date::operator<(const Date &date)
{
    if (*this > date || *this == date)
        return false;
    return true;
}

ostream &operator<<(ostream &out, const Date &date)
{
    // TODO: insert return statement here
    out << "Year: " << date.year << " Month: " << date.month << " Day: " << date.day
        << " Hour: " << date.hour << " Min: " << date.min << " Sec: " << date.sec << " " << (date.isOurEra ? " Our era" : " Before our era");
    return out;
}
