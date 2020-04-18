/// @file
/// @brief Defines constants for day-of-the-week, month,
///        and the Holiday::Date class
#pragma once

#include <ctime>
#include <cstring>

namespace Holiday
{

typedef int DayOfWeek_t;
namespace DayOfWeek
{
    static const DayOfWeek_t NotApplicable = -1;
    static const DayOfWeek_t Sunday = 0;
    static const DayOfWeek_t Monday = 1;
    static const DayOfWeek_t Tuesday = 2;
    static const DayOfWeek_t Wednesday = 3;
    static const DayOfWeek_t Thursday = 4;
    static const DayOfWeek_t Friday = 5;
    static const DayOfWeek_t Saturday = 6;
}

typedef int Month_t;
namespace Month
{
    static const Month_t NotApplicable = -1;
    static const Month_t Janurary = 1;
    static const Month_t Feburary = 2;
    static const Month_t March = 3;
    static const Month_t April = 4;
    static const Month_t May = 5;
    static const Month_t June = 6;
    static const Month_t July = 7;
    static const Month_t August = 8;
    static const Month_t September = 9;
    static const Month_t October = 10;
    static const Month_t November = 11;
    static const Month_t December = 12;
}

/// @brief Helper class to extract useful date features
///        required when determining if a date is a holiday
class Date
{
public:
    inline Date();
    inline Date(const std::tm& date);
    inline Date(int y, int m, int d);
    inline Date(int yyyymmdd);
    inline bool Matches(const std::tm& date) const;
    inline int Year() const;
    inline int Month() const;
    inline int Day() const;
    inline bool Valid() const;
    inline operator int() const;
    inline bool operator==(const Date& rhs) const;
    inline bool operator==(int rhs) const;
    inline DayOfWeek_t GetDayOfWeek() const;
    inline Date GetNextDay() const;
    inline bool IsWeekday() const;
    inline bool IsWeekend() const;
private:
    std::tm m_Date;
    bool m_Valid;
};

Date::Date()
{
    memset(&m_Date, 0, sizeof(m_Date));
    m_Valid = false;
}
Date::Date(const std::tm& date)
{
    m_Date = date;
    std::mktime(&m_Date);
    m_Valid = Matches(date);
}
Date::Date(int y, int m, int d)
{
    memset(&m_Date, 0, sizeof(m_Date));
    m_Date.tm_isdst = -1;
    m_Date.tm_year = y - 1900;
    m_Date.tm_mon = m - 1;
    m_Date.tm_mday = d;
    std::tm date = m_Date;
    std::mktime(&m_Date);
    m_Valid = Matches(date);
}
Date::Date(int yyyymmdd)
{
    memset(&m_Date, 0, sizeof(m_Date));
    m_Date.tm_isdst = -1;
    m_Date.tm_year = yyyymmdd / 10000 - 1900;
    m_Date.tm_mon = yyyymmdd / 100 % 100 - 1;
    m_Date.tm_mday = yyyymmdd % 100;
    std::tm date = m_Date;
    std::mktime(&m_Date);
    m_Valid = Matches(date);
}
bool Date::Matches(const std::tm& date) const
{
    return m_Date.tm_year == date.tm_year
        && m_Date.tm_mon  == date.tm_mon
        && m_Date.tm_mday == date.tm_mday;
}
int Date::Year() const
{
    return m_Date.tm_year + 1900;
}
int Date::Month() const
{
    return m_Date.tm_mon + 1;
}
int Date::Day() const
{
    return m_Date.tm_mday;
}
bool Date::Valid() const
{
    return m_Valid;
}
Date::operator int() const
{
    return m_Valid ? (Year() * 10000 + Month() * 100 + Day()) : -1;
}
bool Date::operator==(const Date& rhs) const
{
    return m_Valid == rhs.m_Valid && Matches(rhs.m_Date);
}
bool Date::operator==(int rhs) const
{
    return static_cast<int>(*this)==rhs;
}
DayOfWeek_t Date::GetDayOfWeek() const
{
    return m_Valid ? m_Date.tm_wday : DayOfWeek::NotApplicable;
}
Date Date::GetNextDay() const
{
    if (!m_Valid) return Date();
    std::tm date = m_Date;
    time_t time = std::mktime(&date);
    time += 24 * 60 * 60; // jump one day
    localtime_r(&time, &date);
    return Date(date);
}
bool Date::IsWeekday() const
{
    return GetDayOfWeek() == DayOfWeek::Monday
        || GetDayOfWeek() == DayOfWeek::Tuesday
        || GetDayOfWeek() == DayOfWeek::Wednesday
        || GetDayOfWeek() == DayOfWeek::Thursday
        || GetDayOfWeek() == DayOfWeek::Friday;
}
bool Date::IsWeekend() const
{
    return GetDayOfWeek() == DayOfWeek::Saturday
        || GetDayOfWeek() == DayOfWeek::Sunday;
}
} // namespace Holiday
