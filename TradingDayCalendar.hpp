#pragma once

#include "Date.hpp"
#include <unordered_set>

namespace Holiday
{

/// @brief A class that can cache trading days using a provided template
/// parameter to query if the date is a Holiday.  Skips weekends as well.
template <class Holidays>
class TradingDayCalendar
{
public:
    /// @brief  Creates a calendar with no cache
    TradingDayCalendar();
    /// @brief Create a calendar caching all TradingDays between the given years
    TradingDayCalendar(int startYear, int endYear);
    /// @brief Caches all TradingDays between the provided years
    void Cache(int startYear, int endYear);
    /// @brief Returns true if the provided date is a Trading Day
    bool IsTradingDay(int year, int month, int day) const;
    /// @brief Returns true if the provided date is a Trading Day
    bool IsTradingDay(int yyyymmdd) const;
    /// @brief Returns true if the provided date is a Trading Day
    bool IsTradingDay(const Date& date) const;
private:
    bool IsCached(const Date& date) const;
    bool IsTradingDayNoCache(const Date& date) const;
    std::unordered_set<int> m_CachedTradingDays;
    int m_StartYear;
    int m_EndYear;
};

template <class Holidays>
TradingDayCalendar<Holidays>::TradingDayCalendar()
{
    // no cache
    m_StartYear = 0;
    m_EndYear = -1;
}
template <class Holidays>
TradingDayCalendar<Holidays>::TradingDayCalendar(int startYear, int endYear)
{
    Cache(startYear, endYear);
}
template <class Holidays>
bool TradingDayCalendar<Holidays>::IsTradingDayNoCache(const Date& date) const
{
    return !(Holidays::IsMarketHoliday(date) || date.IsWeekend());
}
template <class Holidays>
void TradingDayCalendar<Holidays>::Cache(int startYear, int endYear)
{
    m_StartYear = startYear;
    m_EndYear = endYear;
    for(Date date(startYear,1,1); date.Year() <= endYear; date = date.GetNextDay())
    {
        if (IsTradingDayNoCache(date))
        {
            m_CachedTradingDays.insert(date);
        }
    }
}
template <class Holidays>
bool TradingDayCalendar<Holidays>::IsCached(const Date& date) const
{
    return date.Year() >= m_StartYear && date.Year() <= m_EndYear;
}
template<class Holidays>
bool TradingDayCalendar<Holidays>::IsTradingDay(int year, int month, int day) const
{
    Date date(year, month, day);
    int yyyymmdd = date;
    return IsCached(date)
        ? m_CachedTradingDays.count(yyyymmdd) != 0
        : IsTradingDayNoCache(date);
}
template<class Holidays>
bool TradingDayCalendar<Holidays>::IsTradingDay(int yyyymmdd) const
{
    Date date(yyyymmdd);
    return IsCached(date)
        ? m_CachedTradingDays.count(yyyymmdd) != 0
        : IsTradingDayNoCache(date);
}
template<class Holidays>
bool TradingDayCalendar<Holidays>::IsTradingDay(const Date& date) const
{
    int yyyymmdd = date;
    return IsCached(date)
        ? m_CachedTradingDays.count(yyyymmdd) != 0
        : IsTradingDayNoCache(date);
}

} // namespace Holiday
