# Holiday
A set of classes to help programmatically determine if a given date is
a market holiday.  Currently only modern US markets are supported.

## Holiday::USMarketHolidays Example
```
#include "USMarketHolidays.hpp"

using namespace Holiday;

int date = 20200217;
if (USMarketHolidays::IsMarketHoliday(date))
{
    std::cout << date << " is a holiday!" << std::endl;
}
```
## Holiday::TradingDayCalendar Example
```
#include "TradingDayCalendar.hpp"

using namespace Holiday;

TradingDayCalendar<USMarketHolidays> calendar(2000,2040);
int date = 20200417;
if (calendar.IsTradingDay(date))
{
    std::cout << date << " is a trading day!" << std::endl;
}
```
## Holiday::HolidayCalendar Example
```
#include "HolidayCalendar.hpp"

using namespace Holiday;

HolidayCalendar<USMarketHolidays> calendar(2010,2020);
int date = 20200217;
if (calendar.IsHoliday(date))
{
    std::cout << date << " is a holiday!" << std::endl;
}
```
