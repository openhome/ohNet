#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Time.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/TestFramework.h>

using namespace OpenHome;
using namespace OpenHome::TestFramework;

class SuiteTimeHelpers : public Suite
{
public:
    SuiteTimeHelpers();

public: // Suite
    void Test();

private:
    void TestIsLeapYear() const;
    void TestSecondsInYear() const;
    void TestSecondsInMonth() const;
    void TestDaysInMonth() const;
    void TestGetDayOfWeek() const;
};

class SuitePointInTime : public Suite
{
public:
    SuitePointInTime();

public: // Suite
    void Test();

private:
    void TestConstruction() const;
    void TestTryParseFromUnixTimestamp() const;
    void TestConvertToUnixTimestamp() const;
    void TestIsValid() const;
    void TestIOS8601() const;
};

class SuiteHttpHeaderDate : public Suite
{
public:
    SuiteHttpHeaderDate();

public: // Suite
    void Test();

private:
    void TestParse() const;
    void TestWrite() const;
};



// SuiteTimeHelpers
SuiteTimeHelpers::SuiteTimeHelpers()
    : Suite("SuiteTimeHelpers")
{ }

void SuiteTimeHelpers::Test()
{
    TestIsLeapYear();
    TestSecondsInYear();
    TestSecondsInMonth();
    TestDaysInMonth();
}

void SuiteTimeHelpers::TestIsLeapYear() const 
{
    const TInt kTestSize = 21;

    TUint years[kTestSize] = {
        1984,
        1985,
        1986,
        1990,
        1991,
        1992,
        1995,
        1998,
        1999,
        2000,
        2001,
        2002,
        2020,
        2021,
        2022,
        2023,
        2024,
        2025,
        2026,
        2222,
        2224,
    };

    TBool expected[kTestSize] = {
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false,
        true,
        false,
        false,
        true,
        false,
        false,
        false,
        true,
        false,
        false,
        false,
        true,
    };

    for(TInt i = 0; i < kTestSize; ++i) {
        TEST(Time::IsYearALeapYear(years[i]) == expected[i]);
    }
}

void SuiteTimeHelpers::TestSecondsInYear() const
{
    const TUint secondsPerDay     = 60 * 60 * 24;
    const TUint secondsInYear     = secondsPerDay * 365;
    const TUint secondsInLeapYear = secondsPerDay * 366;

    TEST(Time::kSecondsPerDay      == secondsPerDay);
    TEST(Time::kSecondsPerYear     == secondsInYear);
    TEST(Time::kSecondsPerLeapYear == secondsInLeapYear);

    TEST(Time::SecondsInYear(1999) == secondsInYear);
    TEST(Time::SecondsInYear(2000) == secondsInLeapYear);
}

void SuiteTimeHelpers::TestSecondsInMonth() const
{
    const TUint secondsInDay        = 60 * 60 * 24;
    const TUint secondsIn28DayMonth = 28 * secondsInDay;
    const TUint secondsIn29DayMonth = 29 * secondsInDay;
    const TUint secondsIn30DayMonth = 30 * secondsInDay;
    const TUint secondsIn31DayMonth = 31 * secondsInDay;

    TEST(secondsInDay        == Time::kSecondsPerDay);
    TEST(secondsIn28DayMonth == Time::kSecondsIn28DayMonth);
    TEST(secondsIn29DayMonth == Time::kSecondsIn29DayMonth);
    TEST(secondsIn30DayMonth == Time::kSecondsIn30DayMonth);
    TEST(secondsIn31DayMonth == Time::kSecondsIn31DayMonth);

    TEST(Time::kSecondsInMonth[0] == Time::kSecondsIn28DayMonth);
    TEST(Time::kSecondsInMonth[1] == Time::kSecondsIn29DayMonth);
    TEST(Time::kSecondsInMonth[2] == Time::kSecondsIn30DayMonth);
    TEST(Time::kSecondsInMonth[3] == Time::kSecondsIn31DayMonth);

    // 31 Day Months (Jan, March, May, July, August, October, December)
    TEST(Time::SecondsInMonth(1,  2000) == Time::kSecondsIn31DayMonth);
    TEST(Time::SecondsInMonth(3,  1989) == Time::kSecondsIn31DayMonth);
    TEST(Time::SecondsInMonth(5,  1943) == Time::kSecondsIn31DayMonth);
    TEST(Time::SecondsInMonth(7,  2134) == Time::kSecondsIn31DayMonth);
    TEST(Time::SecondsInMonth(8,  3000) == Time::kSecondsIn31DayMonth);
    TEST(Time::SecondsInMonth(10, 1985) == Time::kSecondsIn31DayMonth);
    TEST(Time::SecondsInMonth(12, 2025) == Time::kSecondsIn31DayMonth);

    // 30 Day Months (April, June, September, November)
    TEST(Time::SecondsInMonth(4,  2156) == Time::kSecondsIn30DayMonth);
    TEST(Time::SecondsInMonth(6,  1870) == Time::kSecondsIn30DayMonth);
    TEST(Time::SecondsInMonth(9,  1999) == Time::kSecondsIn30DayMonth);
    TEST(Time::SecondsInMonth(11, 2000) == Time::kSecondsIn30DayMonth);

    // Feb
    const TUint leapYear = 2000;
    const TBool isLeap = Time::IsYearALeapYear(leapYear);
    TEST(isLeap);

    TEST(Time::SecondsInMonth(2, leapYear)     == Time::kSecondsIn29DayMonth);
    TEST(Time::SecondsInMonth(2, leapYear + 1) == Time::kSecondsIn28DayMonth);
    TEST(Time::SecondsInMonth(2, leapYear - 1) == Time::kSecondsIn28DayMonth);
}

void SuiteTimeHelpers::TestDaysInMonth() const
{
    const TUint leapYear = 2000;
    TEST(Time::IsYearALeapYear(leapYear));

    const TUint MonthsWith31Days[7] = { 1, 3, 5, 7, 8, 10, 12 };
    const TUint MonthsWith30Days[4] = { 4, 6, 9, 11 };

    for(TUint i = 0; i < 7; ++i) {
        // Doesn't matter if we're a leap year or not, the value is always the same
        TEST(Time::DaysInMonth(MonthsWith31Days[i], leapYear - 1) == 31);
        TEST(Time::DaysInMonth(MonthsWith31Days[i], leapYear    ) == 31);
        TEST(Time::DaysInMonth(MonthsWith31Days[i], leapYear + 1) == 31);
    }

    for(TUint i = 0; i < 4; ++i) {
        TEST(Time::DaysInMonth(MonthsWith30Days[i], leapYear - 1) == 30);
        TEST(Time::DaysInMonth(MonthsWith30Days[i], leapYear    ) == 30);
        TEST(Time::DaysInMonth(MonthsWith30Days[i], leapYear + 1) == 30);
    }


    // Feb
    TEST(Time::DaysInMonth(2, leapYear - 1) == 28);
    TEST(Time::DaysInMonth(2, leapYear    ) == 29);
    TEST(Time::DaysInMonth(2, leapYear + 1) == 28);
}

void SuiteTimeHelpers::TestGetDayOfWeek() const
{
    // A time point starting on a Sunday
    const TUint year  = 2023;
    const TUint month = 11;   // Novemeber
    const TUint day   = 19;

    for(int i = 0; i < 7; ++i) {
        TEST(Time::GetDayOfWeek(day + i, month, year) == Brn(Time::kDaysInWeek[i]));
    }
}


// SuitePointInTime
SuitePointInTime::SuitePointInTime()
    : Suite("SuitePointInTime")
{ }

void SuitePointInTime::Test()
{
    TestConstruction();
    TestTryParseFromUnixTimestamp();
    TestConvertToUnixTimestamp();
    TestIsValid();
    TestIOS8601();
}

void SuitePointInTime::TestConstruction() const
{
    PointInTime p1;
    PointInTime p2(1, 2, 3, 4, 5, 6);

    TEST(p1.Day()     == 0);
    TEST(p1.Month()   == 0);
    TEST(p1.Year()    == 0);
    TEST(p1.Hours()   == 0);
    TEST(p1.Minutes() == 0);
    TEST(p1.Seconds() == 0);

    TEST(p2.Day()     == 1);
    TEST(p2.Month()   == 2);
    TEST(p2.Year()    == 3);
    TEST(p2.Hours()   == 4);
    TEST(p2.Minutes() == 5);
    TEST(p2.Seconds() == 6);
}

void SuitePointInTime::TestTryParseFromUnixTimestamp() const
{
    PointInTime p;

    // Tue May 06 2025 06:36:07
    TEST(p.TryParseFromUnixTimestamp(1746513367));
    TEST(p.Year()    == 2025);
    TEST(p.Month()   == 5);
    TEST(p.Day()     == 6);
    TEST(p.Hours()   == 6);
    TEST(p.Minutes() == 36);
    TEST(p.Seconds() == 7);

    // Mon Nov 30 2009 12:43:13
    TEST(p.TryParseFromUnixTimestamp(1259584993));
    TEST(p.Year()    == 2009);
    TEST(p.Month()   == 11);
    TEST(p.Day()     == 30);
    TEST(p.Hours()   == 12);
    TEST(p.Minutes() == 43);
    TEST(p.Seconds() == 13);

    // Mon Nov 30 2009 12:43:13 (+ 1 day)
    // Takes us to 31st November which doesn't exist, so we should report 1st December instead
    TEST(p.TryParseFromUnixTimestamp((1259584993 + Time::kSecondsPerDay )));
    TEST(p.Year()    == 2009);
    TEST(p.Month()   == 12);
    TEST(p.Day()     == 1);
    TEST(p.Hours()   == 12);
    TEST(p.Minutes() == 43);
    TEST(p.Seconds() == 13);


    // 1st Jan 1970 00:00:00
    TEST(p.TryParseFromUnixTimestamp(0));
    TEST(p.Year()    == Time::kUnixEpochYear);
    TEST(p.Month()   == 1);
    TEST(p.Day()     == 1);
    TEST(p.Hours()   == 0);
    TEST(p.Minutes() == 0);
    TEST(p.Seconds() == 0);

    // 31st December 1969, 23:59:44
    TEST(p.TryParseFromUnixTimestamp(-16));
    TEST(p.Year()    == 1969);
    TEST(p.Month()   == 12);
    TEST(p.Day()     == 31);
    TEST(p.Hours()   == 23);
    TEST(p.Minutes() == 59);
    TEST(p.Seconds() == 44);

    // 23rd April 1931, 05:45:30
    TEST(p.TryParseFromUnixTimestamp(-1221070470));
    TEST(p.Year()    == 1931);
    TEST(p.Month()   == 4);
    TEST(p.Day()     == 23);
    TEST(p.Hours()   == 5);
    TEST(p.Minutes() == 45);
    TEST(p.Seconds() == 30);
}

void SuitePointInTime::TestConvertToUnixTimestamp() const
{
    // Tue May 06 2025 06:36:07
    {
        PointInTime subject(6, 5, 2025, 6, 36, 7);
        TEST(subject.ConvertToUnixTimestamp() == 1746513367);
    }

    // Mon Nov 30 2009 12:43:13
    {
        PointInTime subject(30, 11, 2009, 12, 43, 13);
        TEST(subject.ConvertToUnixTimestamp() == 1259584993);
    }

    // Thu Jan 01 1970 00:00:00
    {
        PointInTime subject(1, 1, 1970, 0, 0, 0);
        TEST(subject.ConvertToUnixTimestamp() == 0);
    }

    // 31st December 1969, 23:59:44
    {
        PointInTime subject(31, 12, 1969, 23, 59, 44);
        TEST(subject.ConvertToUnixTimestamp() == -16);
    }

    // 1st Feb 1945, 11:23:07
    {
        PointInTime subject(1, 2, 1945, 11, 23, 07);
        TEST(subject.ConvertToUnixTimestamp() == -786199013);
    }
}

void SuitePointInTime::TestIsValid() const
{
    PointInTime p1(2, 2, 1996, 1, 2, 3);
    TEST(p1.IsValid());

    PointInTime p2(2, 2, 1996, 30, 2, 3);
    TEST(p2.IsValid() == false); // Hour out of range

    PointInTime p3(2, 2, 1996, 1, 60, 3);
    TEST(p3.IsValid() == false); // Minute out of range

    PointInTime p4(2, 2, 1996, 1, 2, 75);
    TEST(p4.IsValid() == false); // Seconds out of range


    // Lear Year handling
    PointInTime p5(29, 2, 2000, 1, 1, 1);
    TEST(p5.IsValid());

    PointInTime p6(29, 2, 1999, 1, 1, 1);
    TEST(p6.IsValid() == false);


    // Month day capping
    PointInTime p7(31, 11, 2300, 1, 1, 1);
    TEST(p7.IsValid() == false); // There's no 31st of November
}

void SuitePointInTime::TestIOS8601() const
{
    PointInTime subject;
    Brn kTime1("");                          // Nothing
    Brn kTime2("Jibberish");                 // As stated
    Brn kTime3("2001-02-01");                // Year only
    Brn kTime4("11:12:13");                  // Time only
    Brn kTime5("2010-09-12 04:11:19Z");      // Space in middle
    Brn kTime6("1985-01-01T00:00:05");       // No timezone at the end
    Brn kTime7("1999-10-10T10:10:10+01:00"); // Timezone, but not UTC
    Brn kTime8("1969-12-31T23:59:44Z");      // Valid #1
    Brn kTime9("2002-05-23T07:30:27Z");      // Valid #2

    TEST(subject.TryParseFromISO8601Time(kTime1) == false);
    TEST(subject.TryParseFromISO8601Time(kTime2) == false);
    TEST(subject.TryParseFromISO8601Time(kTime3) == false);
    TEST(subject.TryParseFromISO8601Time(kTime4) == false);
    TEST(subject.TryParseFromISO8601Time(kTime5) == false);
    TEST(subject.TryParseFromISO8601Time(kTime6) == false);
    TEST(subject.TryParseFromISO8601Time(kTime7) == false);

    TEST(subject.TryParseFromISO8601Time(kTime8));
    TEST(subject.Year()    == 1969);
    TEST(subject.Month()   == 12);
    TEST(subject.Day()     == 31);
    TEST(subject.Hours()   == 23);
    TEST(subject.Minutes() == 59);
    TEST(subject.Seconds() == 44);

    TEST(subject.TryParseFromISO8601Time(kTime9));
    TEST(subject.Year()    == 2002);
    TEST(subject.Month()   == 5);
    TEST(subject.Day()     == 23);
    TEST(subject.Hours()   == 7);
    TEST(subject.Minutes() == 30);
    TEST(subject.Seconds() == 27);
}


// SuiteHttpheaderDate
SuiteHttpHeaderDate::SuiteHttpHeaderDate()
    : Suite("SuiteHttpHeaderDate")
{ }

void SuiteHttpHeaderDate::Test()
{
    TestParse();
    TestWrite();
}

void SuiteHttpHeaderDate::TestParse() const
{
    HttpHeaderDate subject;

    {
        const TChar* value = "Mon, 28 Dec 2009 13:41:15 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        PointInTime p = subject.ValueAsPointInTime();
        TEST(p.Year()    == 2009);
        TEST(p.Month()   == 12);
        TEST(p.Day()     == 28);
        TEST(p.Hours()   == 13);
        TEST(p.Minutes() == 41);
        TEST(p.Seconds() == 15);
    }

    {
        const TChar* value = "Thu, 02 Nov 2023 14:54:11 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        PointInTime p = subject.ValueAsPointInTime();
        TEST(p.Year()    == 2023);
        TEST(p.Month()   == 11);
        TEST(p.Day()     == 2);
        TEST(p.Hours()   == 14);
        TEST(p.Minutes() == 54);
        TEST(p.Seconds() == 11);
    }

    {
        // Checks we ignore everything before the first , value
        const TChar* value = "Rubbish, 02 Nov 2023 01:12:23 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        PointInTime p = subject.ValueAsPointInTime();
        TEST(p.Year()    == 2023);
        TEST(p.Month()   == 11);
        TEST(p.Day()     == 2);
        TEST(p.Hours()   == 1);
        TEST(p.Minutes() == 12);
        TEST(p.Seconds() == 23);
    }

    {
        // Checks we handle unknown month values
        const TChar* value = "Nov, 02 ALongMonthName 2023 01:12:23 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        TEST_THROWS(subject.ValueAsPointInTime(), ReaderError);
    }

    // Check we can handle unknown day, year & time values
    {
        const TChar* value = "Nov, InvalidDay Nov 2023 01:12:23 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        TEST_THROWS(subject.ValueAsPointInTime(), AsciiError);
    }

    {
        const TChar* value = "Nov, 02 Nov InvalidYear 01:12:23 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        TEST_THROWS(subject.ValueAsPointInTime(), AsciiError);
    }

    {
        const TChar* value = "Nov, 02 Nov 2023 InvalidHour:12:23 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        TEST_THROWS(subject.ValueAsPointInTime(), AsciiError);
    }

    {
        const TChar* value = "Nov, 02 Nov 2023 01:12:InvalidSeconds GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        TEST_THROWS(subject.ValueAsPointInTime(), AsciiError);
    }

    {
        // Check we can handle an invalid / missing time value
        const TChar* value = "Nov, 02 Nov 2023 022345 GMT";
        static_cast<IHttpHeader&>(subject).Process(Brn(value));

        TEST_THROWS(subject.ValueAsPointInTime(), AsciiError);
    }
}

void SuiteHttpHeaderDate::TestWrite() const
{
    Bwh buf(1024);
    WriterBuffer w(buf);

    PointInTime p1(2, 2, 1996, 1, 10, 9);
    HttpHeaderDate::WriteDateTimeValue(w, p1);

    buf.SetBytes(0);

    HttpHeaderDate::WriteDateTimeValue(w, 23, 12, 2032, 12, 34, 56);
    TEST(buf == Brn("Thu, 23 Dec 2032 12:34:56 GMT"));
    buf.SetBytes(0);

    HttpHeaderDate::WriteDateTimeValue(w, 1699280475);
    TEST(buf == Brn("Mon, 06 Nov 2023 14:21:15 GMT"));
}


void TestTime(Environment& aEnv)
{
    (void)aEnv;

    Runner runner("File testing.");
    runner.Add(new SuiteTimeHelpers);
    runner.Add(new SuitePointInTime);
    runner.Add(new SuiteHttpHeaderDate);
    runner.Run();
}