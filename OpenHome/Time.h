#ifndef HEADER_TIME
#define HEADER_TIME

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>

namespace OpenHome {

class Environment;

class Time
{
public:
    static const TUint kUnixEpochYear;

    // String constants for days in the week, Sun -> Saturday
    static const TChar* kDaysInWeek[7];

    // Number of days in each month with the months indexed Jan = 0
    // NOTE: Feb/1 will return 0, as this is depends on if the year is a leap year. You can use appropriate helpers to work this out
    static const TByte kDaysInMonth[12];

    // String constants for the months in the year with months indexed Jan = 0
    static const TChar* kMonthsInYear[12];

    static const TUint kSecondsPerMinute;
    static const TUint kSecondsPerHour;
    static const TUint kSecondsPerDay;

    static const TUint kSecondsPerYear;
    static const TUint kSecondsPerLeapYear;

    static const TUint kSecondsIn28DayMonth;
    static const TUint kSecondsIn29DayMonth;
    static const TUint kSecondsIn30DayMonth;
    static const TUint kSecondsIn31DayMonth;

    // Quick lookup for the number of days in a month. Access using (<days in month> - 28)
    static const TUint kSecondsInMonth[4];

public:
    static TUint Now(Environment& aEnv);
    static TBool IsBeforeOrAt(TUint aQuestionableTime, TUint aTime);
    static TBool IsAfter(TUint aQuestionableTime, TUint aTime);
    static TBool IsInPastOrNow(Environment& aEnv, TUint aTime);
    static TBool IsInFuture(Environment& aEnv, TUint aTime);
    static TInt TimeToWaitFor(Environment& aEnv, TUint aTime);


    static TBool IsYearALeapYear(TUint aYear);

    // Returns total number of seconds in the given year, accounting for leap years
    static TUint SecondsInYear(TUint aYear);
    // Returns the total number of seconds in the given month of the given year, accounting for leap years
    static TUint SecondsInMonth(TUint aMonth, TUint aYear);

    // Returns the total number of days in the given month of the given year, accounting for leap years
    static TUint DaysInMonth(TUint aMonth, TUint aYear);

    static TUint GetDayOfWeekIndex(TUint aDay, TUint aMonth, TUint aYear);
    static const Brn GetDayOfWeek(TUint aDay, TUint aMonth, TUint aYear);
};



// Class representing a single point in time. 
// ---
// Time is represented as 24hr time
// Month is in the range 1-12, with Janurary = 1 & December = 12
// Default constructor will set everything to 0, assuming you'll use a helper method to parse 
// something or already know  the components to make this class up.
//
// NOTE: The internal representation of this is stored as a single 64bit numerical value. The
//       various components are restricted to a certain number of bits and subsequently masked
//       & shifted to fit into a single value
//
//       TIME = Seconds: 0 - 59, Mins: 0 - 59, Hours: 0 - 23
//       DATE = Days: 0 - 31, Month: 1 - 12
//        
// 0.......8.......16.......24.......32.......40.......48.......56.......64
//           Year           | Month  |   Day  |  Hours | Minutes| Seconds|
//          3 bytes         | 1 byte | 1 byte | 1 byte | 1 byte | 1 byte |

class PointInTime
{
public:
    PointInTime();
    PointInTime(TByte aDay, TByte aMonth, TUint aYear, TByte aHour, TByte aMinute, TByte aSecond);

public:
    TByte Day() const;
    TByte Month() const;
    TUint Year() const;

    TByte Hours() const;
    TByte Minutes() const;
    TByte Seconds() const;

    // Returns true if all the components match the desired ranges 
    // and that the given day falls during the given month during the given year
    TBool IsValid() const;    

    // Converts the internal components into a UnixTimestamp
    // NOTE: Returns 0 if invalid OR the Year < Unix Epoch (1970)
    TUint ConvertToUnixTimestamp() const;

    TBool TryParseFromUnixTimestamp(TUint aTimestamp);

private:
    void Set(TByte aDay, TByte aMonth, TUint aYear, TByte aHour, TByte aMinute, TByte aSecond);

private:
    TUint64 iValue;
};


} // namespace OpenHome

#endif // HEADER_TIME

