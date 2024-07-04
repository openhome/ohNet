#include <OpenHome/OsWrapper.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Time.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>

using namespace OpenHome;


// Time
const TUint Time::kUnixEpochYear = 1970;

const TChar* Time::kDaysInWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

const TByte Time::kDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const TChar* Time::kMonthsInYear[12] = { "January", "February", "March", "April", "May", "June", 
                                         "July", "August", "September", "October", "November", "December" };

const TUint Time::kSecondsPerMinute = 60;
const TUint Time::kSecondsPerHour   = 3600;   // 60 * 60
const TUint Time::kSecondsPerDay    = 86400;  // kSecondsPerHour * 24

const TUint Time::kSecondsPerYear     = 31536000; // kSecondsPerDay * 365
const TUint Time::kSecondsPerLeapYear = 31622400; // kSecondsPerDay * 366

const TUint Time::kSecondsIn28DayMonth = 2419200; // kSecondsPerDay * 28
const TUint Time::kSecondsIn29DayMonth = 2505600; // kSecondsPerDay * 29
const TUint Time::kSecondsIn30DayMonth = 2592000; // kSecondsPerDay * 30
const TUint Time::kSecondsIn31DayMonth = 2678400; // kSecondsPerDay * 31

const TUint Time::kSecondsInMonth[4] = {
    kSecondsIn28DayMonth,
    kSecondsIn29DayMonth,
    kSecondsIn30DayMonth,
    kSecondsIn31DayMonth,
};


TUint Time::Now(Environment& aEnv)
{
    return Os::TimeInMs(aEnv.OsCtx());
};

TBool Time::IsBeforeOrAt(TUint aQuestionableTime, TUint aTime)
{
    TInt diff = aTime - aQuestionableTime;
    return (diff >= 0);
}

TBool Time::IsAfter(TUint aQuestionableTime, TUint aTime)
{
    TInt diff = aTime - aQuestionableTime;
    return (diff < 0);
}

TBool Time::IsInPastOrNow(Environment& aEnv, TUint aTime)
{
    return (IsBeforeOrAt(aTime, Now(aEnv)));
}

TBool Time::IsInFuture(Environment& aEnv, TUint aTime)
{
    return (IsAfter(aTime, Now(aEnv)));
}

TInt Time::TimeToWaitFor(Environment& aEnv, TUint aTime)
{
    return (aTime - Os::TimeInMs(aEnv.OsCtx()));
}


TBool Time::IsYearALeapYear(TUint aYear)
{
    /* A leap year:
    The year must be evenly divisible by 4;
    If the year can also be evenly divided by 100, it is not a leap year;
        unless...
    The year is also evenly divisible by 400. Then it is a leap year.
    */
    const TBool divBy4   = aYear % 4 == 0;
    const TBool divBy100 = aYear % 100 == 0;
    return divBy4 && (!divBy100 || aYear % 400 == 0);
}

TUint Time::SecondsInYear(TUint aYear)
{
    return IsYearALeapYear(aYear) ? kSecondsPerLeapYear
                                  : kSecondsPerYear;
}

TUint Time::DaysInMonth(TUint aMonth, TUint aYear)
{
    if (aMonth == 2) {
        return IsYearALeapYear(aYear) ? 29 : 28;
    }
    else {
        return kDaysInMonth[aMonth - 1];
    }
}

TUint Time::SecondsInMonth(TUint aMonth, TUint aYear)
{
    const TUint daysInMonth = DaysInMonth(aMonth, aYear);
    return kSecondsInMonth[daysInMonth - 28];
}

TUint Time::GetDayOfWeekIndex(TUint aDay, TUint aMonth, TUint aYear)
{
    // Zeller's Congruence from RFC3339 - Appendix B
    // More details: https://en.wikipedia.org/wiki/Zeller%27s_congruence
    const TInt day   = aDay;
    const TInt cent  = aYear / 100;

    TInt res   = 0;
    TInt year  = aYear;
    TInt month = aMonth;

    month -= 2;
    if (month < 1) {
     month += 12;
     --year;
    }

    year %= 100;

    res = (26 * month - 2) / 10 + day + year + year / 4 + cent / 4 + 5 * cent;
    return res % 7;
}

const Brn Time::GetDayOfWeek(TUint aDay, TUint aMonth, TUint aYear)
{
    const TUint idx = GetDayOfWeekIndex(aDay, aMonth, aYear);
    return Brn(kDaysInWeek[idx]);
}




// PointInTime

static const TUint kValueMask  = 0xFF;
static const TUint kYearValueMask = 0xFFFF;

static const TUint kSecondShift  = 48;
static const TUint kMinuteShift  = 40;
static const TUint kHourShift    = 32;
static const TUint kDayShift     = 24;
static const TUint kMonthShift   = 16;

PointInTime::PointInTime()
{ 
    Set(0, 0, 0, 0, 0, 0);
}

PointInTime::PointInTime(TByte aDay, TByte aMonth, TUint aYear, TByte aHour, TByte aMinute, TByte aSecond)
{
    Set(aDay, aMonth, aYear, aHour, aMinute, aSecond);
}

TByte PointInTime::Day() const
{
    return (iValue >> kDayShift) & kValueMask;
}

TByte PointInTime::Month() const
{
    return (iValue >> kMonthShift) & kValueMask;
}

TUint PointInTime::Year() const
{
    return iValue & kYearValueMask;
}

TByte PointInTime::Hours() const
{
    return (iValue >> kHourShift) & kValueMask;
}

TByte PointInTime::Minutes() const
{
    return (iValue >> kMinuteShift) & kValueMask;
}

TByte PointInTime::Seconds() const
{
    return (iValue >> kSecondShift) & kValueMask;
}

void PointInTime::Set(TByte aDay, TByte aMonth, TUint aYear, TByte aHour, TByte aMinute, TByte aSecond)
{
    TUint64 storeSec   = static_cast<TUint64>(aSecond) << kSecondShift;
    TUint64 storeMin   = static_cast<TUint64>(aMinute) << kMinuteShift;
    TUint64 storeHour  = static_cast<TUint64>(aHour)   << kHourShift;
    TUint64 storeDay   = static_cast<TUint64>(aDay)    << kDayShift;
    TUint64 storeMonth = static_cast<TUint64>(aMonth)  << kMonthShift;
    TUint64 storeYear  = static_cast<TUint64>(aYear);

    iValue = storeSec | storeMin | storeHour | storeDay | storeMonth | storeYear;
}

TBool PointInTime::IsValid() const
{
    if (Seconds() > 59) {
        return false;
    }

    if (Minutes() > 59) {
        return false;
    }

    if (Hours() > 23) {
        return false;
    }

    if (Month() > 12) {
        return false;
    }

    return Day() <= Time::DaysInMonth(Month(), Year());
}



TBool PointInTime::TryParseFromUnixTimestamp(TUint aTimestamp)
{
    TUint secsRemaining = aTimestamp;
    TUint year = Time::kUnixEpochYear;

    while(true) {
        TUint secsForYear = Time::SecondsInYear(year);
        if (secsForYear > secsRemaining) {
            break;
        }

        ++year;
        secsRemaining -= secsForYear;
    }

    TByte month = 1;
    while (true) {
        TUint secsForMonth = Time::SecondsInMonth(month, year);
        if (secsForMonth > secsRemaining) {
            break;
        }

        ++month;
        secsRemaining -= secsForMonth;
    }

    TByte day = 1;
    while (Time::kSecondsPerDay <= secsRemaining) {
        ++day;
        secsRemaining -= Time::kSecondsPerDay;
    }

    TByte hour = 0;
    while(Time::kSecondsPerHour <= secsRemaining) {
        ++hour;
        secsRemaining -= Time::kSecondsPerHour;
    }

    TByte min = 0;
    while(Time::kSecondsPerMinute <= secsRemaining) {
        ++min;
        secsRemaining -= Time::kSecondsPerMinute;
    }

    Set(day, month, year, hour, min, secsRemaining);
    return IsValid();
}

TUint PointInTime::ConvertToUnixTimestamp() const
{
    if (!IsValid()) {
        return 0;
    }

    TUint timestamp = 0;
    TUint year      = Year();
    TByte month     = Month();

    if (Year() < Time::kUnixEpochYear) {
        return 0;
    }

    for(TUint i = Time::kUnixEpochYear; i < year; ++i) {
        timestamp += Time::SecondsInYear(i);
    }

    for(TByte i = 1; i < month; ++i) {
        timestamp += Time::SecondsInMonth(i, year);
    }

    timestamp += (Day() - 1) * Time::kSecondsPerDay;

    timestamp += Hours()   * Time::kSecondsPerHour;
    timestamp += Minutes() * Time::kSecondsPerMinute;
    timestamp += Seconds();

    return timestamp;
}

// Converts a given ISO8601 time string into a PointInTime value.
// This is very limited support as we currently only parse:
// - Combined Date/Time (UTC only) YYYY-MM-DDThh:mm:ssZ
TBool PointInTime::TryParseFromISO8601Time(const Brx& aTimeString)
{
    if (aTimeString.Bytes() == 0) {
        return false; // Empty string, so nothing to parse
    }

    if (aTimeString.At(aTimeString.Bytes() - 1) != 'Z') {
        return false; // Non-UTC timezone
    }

    try {
        Parser p(aTimeString);
        TUint year   = Ascii::Uint(p.Next('-'));
        TByte month  = Ascii::Uint(p.Next('-'));
        TByte day    = Ascii::Uint(p.Next('T'));
        TByte hour   = Ascii::Uint(p.Next(':'));
        TByte min    = Ascii::Uint(p.Next(':'));
        TByte second = Ascii::Uint(p.Next('Z'));

        Set(day, month, year, hour, min, second);
        return true;
    }
    catch (AsciiError&) {
        return false;
    }
}
