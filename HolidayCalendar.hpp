#pragma once

#include "Date.hpp"
#include <unordered_set>

namespace Holiday
{

/// @brief A class that can cache holdays using a provided template parameter
/// to query if the date is a holiday.
template <class Holidays>
class HolidayCalendar
{
public:
    /// @brief  Creates a calendar with no cache
    HolidayCalendar();
    /// @brief Create a calendar caching all holidays between the given years
    HolidayCalendar(int startYear, int endYear);
    /// @brief Caches all holidays between the provided years
    void Cache(int startYear, int endYear);
    /// @brief Returns true if the provided date is a holiday
    bool IsMarketHoliday(int year, int month, int day) const;
    /// @brief Returns true if the provided date is a holiday
    bool IsMarketHoliday(int yyyymmdd) const;
    /// @brief Returns true if the provided date is a holiday
    bool IsMarketHoliday(const Date& date) const;
private:
    bool IsCached(const Date& date) const;
    std::unordered_set<int> m_CachedHolidays;
    int m_StartYear;
    int m_EndYear;
};

template <class Holidays>
HolidayCalendar<Holidays>::HolidayCalendar()
{
    // no cache
    m_StartYear = 0;
    m_EndYear = -1;
}
template <class Holidays>
HolidayCalendar<Holidays>::HolidayCalendar(int startYear, int endYear)
{
    Cache(startYear, endYear);
}
template <class Holidays>
void HolidayCalendar<Holidays>::Cache(int startYear, int endYear)
{
    m_StartYear = startYear;
    m_EndYear = endYear;
    for(Date date(startYear,1,1); date.Year() <= endYear; date = date.GetNextDay())
    {
        if (Holidays::IsMarketHoliday(date))
        {
            m_CachedHolidays.insert(date);
        }
    }
}
template <class Holidays>
bool HolidayCalendar<Holidays>::IsCached(const Date& date) const
{
    return date.Year() >= m_StartYear && date.Year() <= m_EndYear;
}
template<class Holidays>
bool HolidayCalendar<Holidays>::IsMarketHoliday(int year, int month, int day) const
{
    Date date(year, month, day);
    int yyyymmdd = date;
    return IsCached(date)
        ? m_CachedHolidays.count(yyyymmdd) != 0
        : Holidays::IsMarketHoliday(date);
}
template<class Holidays>
bool HolidayCalendar<Holidays>::IsMarketHoliday(int yyyymmdd) const
{
    Date date(yyyymmdd);
    return IsCached(date)
        ? m_CachedHolidays.count(yyyymmdd) != 0
        : Holidays::IsMarketHoliday(date);
}
template<class Holidays>
bool HolidayCalendar<Holidays>::IsMarketHoliday(const Date& date) const
{
    int yyyymmdd = date;
    return IsCached(date)
        ? m_CachedHolidays.count(yyyymmdd) != 0
        : Holidays::IsMarketHoliday(date);
}

} // namespace Holiday
