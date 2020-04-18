#include "gtest/gtest.h"
#include "HolidayCalendar.hpp"
#include "USMarketHolidays.hpp"
#include "KnownUSMarketHolidays.hpp"
#include <algorithm>

using namespace Holiday;

TEST(HolidayCalendar, KnownUSMarketHolidaysWithCache)
{
    HolidayCalendar<USMarketHolidays> calendar(2000,2040);
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        EXPECT_EQ(isKnownHoliday, calendar.IsMarketHoliday(date)) << yyyymmdd;
    }
}

TEST(HolidayCalendar, KnownUSMarketHolidaysPartialCache)
{
    HolidayCalendar<USMarketHolidays> calendar(2010,2020);
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        EXPECT_EQ(isKnownHoliday, calendar.IsMarketHoliday(date)) << yyyymmdd;
    }
}

TEST(HolidayCalendar, KnownUSMarketHolidaysNoCache)
{
    HolidayCalendar<USMarketHolidays> calendar;
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        EXPECT_EQ(isKnownHoliday, calendar.IsMarketHoliday(date)) << yyyymmdd;
    }
}
