#pragma once

#include "Date.hpp"

namespace Holiday
{
/// @brief Class that determines if a provided date is a known modern-day
///        US Market Holdiday.
/// @note This does not work for all of US Market history.  For examples,
///       Thanksgiving was not always the fourth Thursday in November, and
///       MLK was not observed by markets until 1998.
class USMarketHolidays
{
public:
    /// @brief Determines if the provided date is a modern US Market Holiday
    static bool IsMarketHoliday(const Date& date)
    {
        int year = date.Year();
        int month = date.Month();
        switch (month)
        {
            case Month::Janurary:
                return date == GetNewYears(year)
                    || date == GetMlkDay(year);
            case Month::Feburary:
                return date == GetPresidentsDay(year);
            case Month::March:
            case Month::April:
                return date == GetGoodFriday(year);
            case Month::May:
                return date == GetMemorialDay(year);
            case Month::July:
                return date == GetIndependenceDay(year);
            case Month::September:
                return date == GetLaborDay(year);
            case Month::November:
                return date == GetThanksgiving(year);
            case Month::December:
                return date == GetChristmas(year);
        }
        return false;
    }
private:
    /// @brief Observed New Year's Day is the first Monday of Janurary unless
    ///        New Year's Day proper falls on a Saturday then there is no
    ///        observed holiday for that year.
    static Date GetNewYears(int year)
    {
        int day = 1;
        DayOfWeek_t dayofweek = Date(year,Month::Janurary,day).GetDayOfWeek();
        if (dayofweek == DayOfWeek::Saturday) return Date(); // no holiday
        if (dayofweek == DayOfWeek::Sunday) ++day;
        return Date(year,Month::Janurary,day);
    }
    /// @brief Martin Luther King Day is the third Monday in Janurary.
    ///        It can be between the 15th and 21st.
    static Date GetMlkDay(int year)
    {
        int day = 15;
        DayOfWeek_t dayofweek = Date(year,Month::Janurary,day).GetDayOfWeek();
        day += (8 - dayofweek) % 7;
        return Date(year,Month::Janurary,day);
    }
    /// @brief President's Day is the third Monday in Feburary.
    ///        It can be between the 15th and 21st.
    static Date GetPresidentsDay(int year)
    {
        int day = 15;
        DayOfWeek_t dayofweek = Date(year,Month::Feburary,day).GetDayOfWeek();
        day += (8 - dayofweek) % 7;
        return Date(year,Month::Feburary,day);
    }
    /// @brief Observed Easter is the Friday before Easter Sunday.
    ///        Really the only difficult one to calculate as it is
    ///        based on a Lunar calendar.
    ///        The Easter calculation is known as Computus and this
    ///        specific alrogithm was copied from a post on stackexchange.
    static Date GetGoodFriday(int year)
    {
        int month, day;
        int a = year % 19;
        int b = year / 100;
        int c = year % 100;
        int d = b / 4;
        int e = b % 4;
        int i = c / 4;
        int k = c % 4;
        int g = (8 * b + 13) / 25;
        int h = ((19 * a) + b - d - g + 15) % 30;
        int l = ((2 * e) + (2 * i) - k + 32 - h) % 7;
        int m = (a + (11*h) + (19*l)) / 433;
        int days_to_good_friday = h + l - (7*m) - 2;
        month = (days_to_good_friday + 90) / 25;
        day = (days_to_good_friday + (33 * month) + 19) % 32;
        return Date(year,month,day);
    }
    /// @brief Memorial Day is the first Monday of May.
    static Date GetMemorialDay(int year)
    {
        int day = 25;
        DayOfWeek_t dayofweek = Date(year,Month::May,day).GetDayOfWeek();
        day += (8 - dayofweek) % 7;
        return Date(year,Month::May,day);
    }
    /// @brief Independence Day is the 4th of July unless it falls
    ///        on a weekend.  It would be observed on Friday if falling
    ///        on a Saturday or observed on a Monday if falling on a
    ///        Sunday.
    static Date GetIndependenceDay(int year)
    {
        int day = 4;
        DayOfWeek_t dayofweek = Date(year,Month::July,day).GetDayOfWeek();
        if (dayofweek == DayOfWeek::Saturday) --day;
        else if (dayofweek == DayOfWeek::Sunday) ++day;
        return Date(year,Month::July,day);
    }
    /// @brief Labor Day is the first Monday of September.
    static Date GetLaborDay(int year)
    {
        int day = 1;
        DayOfWeek_t dayofweek = Date(year,Month::September,day).GetDayOfWeek();
        day += (8 - dayofweek) % 7;
        return Date(year,Month::September,day);
    }
    /// @brief Thanksgiving is the fourth Thursday of November.
    ///        It can be between the 22nd and 28th.
    static Date GetThanksgiving(int year)
    {
        int day = 22;
        DayOfWeek_t dayofweek = Date(year,Month::November,day).GetDayOfWeek();
        day += (11 - dayofweek) % 7;
        return Date(year,Month::November,day);
    }
    /// @brief Chirstmas Day is the 25th of July unless it falls
    ///        on a weekend.  It would be observed on Friday if falling
    ///        on a Saturday or observed on a Monday if falling on a
    ///        Sunday.
    static Date GetChristmas(int year)
    {
        int day = 25;
        DayOfWeek_t dayofweek = Date(year,Month::December,day).GetDayOfWeek();
        if (dayofweek == DayOfWeek::Saturday) --day;
        else if (dayofweek == DayOfWeek::Sunday) ++day;
        return Date(year,Month::December,day);
    }
};

}
