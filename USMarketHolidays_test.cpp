#include "gtest/gtest.h"
#include "USMarketHolidays.hpp"
#include "KnownUSMarketHolidays.hpp"
#include <algorithm>

using namespace Holiday;

TEST(USMarketHolidays, FromFile)
{
    for(Date date(2000,1,1); date.Year() <= 2040; date = date.GetNextDay())
    {
        int yyyymmdd = date;
        bool isKnownHoliday = std::find(std::begin(KnownUSMarketHolidays),
                                        std::end(KnownUSMarketHolidays),
                                        yyyymmdd) != std::end(KnownUSMarketHolidays);
        EXPECT_EQ(isKnownHoliday, USMarketHolidays::IsMarketHoliday(date)) << yyyymmdd;
    }
}
