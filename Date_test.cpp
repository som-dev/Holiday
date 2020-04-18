#include "USMarketHolidays.hpp"
#include "gtest/gtest.h"

using namespace Holiday;

TEST(Date, Constructor_Default)
{
    Date date;
    EXPECT_FALSE(date.Valid());
}
TEST(Date, Constructor_YMD_Good)
{
    Date date(2020,2,20);
    EXPECT_TRUE(date.Valid());
    EXPECT_EQ(date.Year(), 2020);
    EXPECT_EQ(date.Month(), 2);
    EXPECT_EQ(date.Day(), 20);
}
TEST(Date, Constructor_YMD_BadMonth)
{
    Date date(2020,14,1);
    EXPECT_FALSE(date.Valid());
}
TEST(Date, Constructor_YMD_BadDay)
{
    Date date(2020,1,32);
    EXPECT_FALSE(date.Valid());
}
TEST(Date, ConstructorYYYYMMDD_Good)
{
    Date date(20200220);
    EXPECT_TRUE(date.Valid());
    EXPECT_EQ(date.Year(), 2020);
    EXPECT_EQ(date.Month(), 2);
    EXPECT_EQ(date.Day(), 20);
}
TEST(Date, ConstructorYYYYMMDD_BadMonth)
{
    Date date(20201401);
    EXPECT_FALSE(date.Valid());
}
TEST(Date, ConstructorYYYYMMDD_BadDay)
{
    Date date(20200132);
    EXPECT_FALSE(date.Valid());
}
TEST(Date, DayOfWeek)
{
    EXPECT_EQ(Date(20200216).GetDayOfWeek(), DayOfWeek::Sunday);
    EXPECT_EQ(Date(20200217).GetDayOfWeek(), DayOfWeek::Monday);
    EXPECT_EQ(Date(20200218).GetDayOfWeek(), DayOfWeek::Tuesday);
    EXPECT_EQ(Date(20200219).GetDayOfWeek(), DayOfWeek::Wednesday);
    EXPECT_EQ(Date(20200220).GetDayOfWeek(), DayOfWeek::Thursday);
    EXPECT_EQ(Date(20200221).GetDayOfWeek(), DayOfWeek::Friday);
    EXPECT_EQ(Date(20200222).GetDayOfWeek(), DayOfWeek::Saturday);
    EXPECT_EQ(Date(20200223).GetDayOfWeek(), DayOfWeek::Sunday);
}
TEST(Date, YYYYMMDD_Conversion_Good)
{
    Date date(20200220);
    EXPECT_EQ(date, 20200220);
}
TEST(Date, YYYYMMDD_Conversion_Bad)
{
    Date date(20209999);
    EXPECT_EQ(date, -1);
}
TEST(Date, EqualityOperator)
{
    Date date1;
    Date date2(20209999);
    Date date3(20200101);
    Date date4(20200101);
    EXPECT_TRUE(date1 == date1);
    EXPECT_FALSE(date1 == date2);
    EXPECT_FALSE(date1 == date3);
    EXPECT_FALSE(date1 == date4);
    EXPECT_FALSE(date2 == date1);
    EXPECT_TRUE(date2 == date2);
    EXPECT_FALSE(date2 == date3);
    EXPECT_FALSE(date2 == date4);
    EXPECT_FALSE(date3 == date1);
    EXPECT_FALSE(date3 == date2);
    EXPECT_TRUE(date3 == date3);
    EXPECT_TRUE(date3 == date4);
    EXPECT_FALSE(date4 == date1);
    EXPECT_FALSE(date4 == date2);
    EXPECT_TRUE(date4 == date3);
    EXPECT_TRUE(date4 == date4);
}
TEST(Date, EqualityOperatorWithInt)
{
    Date date1;
    Date date2(20209999);
    Date date3(20200101);
    EXPECT_TRUE(date1 == -1);
    EXPECT_FALSE(date2 == 20209999);
    EXPECT_TRUE(date3 == 20200101);
    EXPECT_FALSE(date3 == 20200102);
}
TEST(Date, GetNextDay)
{
    Date date(20191230);
    EXPECT_EQ(20191231, date.GetNextDay());
    EXPECT_EQ(20200101, date.GetNextDay().GetNextDay());
}
TEST(Date, IsWeekday)
{
    EXPECT_FALSE(Date().IsWeekday());
    EXPECT_TRUE(Date(20200406).IsWeekday());
    EXPECT_TRUE(Date(20200407).IsWeekday());
    EXPECT_TRUE(Date(20200408).IsWeekday());
    EXPECT_TRUE(Date(20200409).IsWeekday());
    EXPECT_TRUE(Date(20200410).IsWeekday());
    EXPECT_FALSE(Date(20200411).IsWeekday());
    EXPECT_FALSE(Date(20200412).IsWeekday());
}
TEST(Date, IsWeekend)
{
    EXPECT_FALSE(Date().IsWeekend());
    EXPECT_FALSE(Date(20200406).IsWeekend());
    EXPECT_FALSE(Date(20200407).IsWeekend());
    EXPECT_FALSE(Date(20200408).IsWeekend());
    EXPECT_FALSE(Date(20200409).IsWeekend());
    EXPECT_FALSE(Date(20200410).IsWeekend());
    EXPECT_TRUE(Date(20200411).IsWeekend());
    EXPECT_TRUE(Date(20200412).IsWeekend());
}
