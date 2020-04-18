#include "gtest/gtest.h"
#include "TradingDayCalendar.hpp"
#include "USMarketHolidays.hpp"
#include "KnownUSMarketHolidays.hpp"
#include <algorithm>

using namespace Holiday;

TEST(TradingDayCalendar, KnownUSMarketHolidaysWithCache)
{
    TradingDayCalendar<USMarketHolidays> calendar(2000,2040);
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        bool isWeekend = date.IsWeekend();
        bool isTradingDay = !isKnownHoliday && !isWeekend;
        EXPECT_EQ(isTradingDay, calendar.IsTradingDay(date)) << yyyymmdd;
    }
}

TEST(TradingDayCalendar, KnownUSMarketHolidaysPartialCache)
{
    TradingDayCalendar<USMarketHolidays> calendar(2010,2020);
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        bool isWeekend = date.IsWeekend();
        bool isTradingDay = !isKnownHoliday && !isWeekend;
        EXPECT_EQ(isTradingDay, calendar.IsTradingDay(date)) << yyyymmdd;
    }
}

TEST(TradingDayCalendar, KnownUSMarketHolidaysNoCache)
{
    TradingDayCalendar<USMarketHolidays> calendar;
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        bool isWeekend = date.IsWeekend();
        bool isTradingDay = !isKnownHoliday && !isWeekend;
        EXPECT_EQ(isTradingDay, calendar.IsTradingDay(date)) << yyyymmdd;
    }
}
