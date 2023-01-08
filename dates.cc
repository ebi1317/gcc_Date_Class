// class date
// created by ebrahim zeinali

#include <iomanip>
#include <iostream>

using namespace std;

class Date
{
private:
  int day;
  int month;
  int year;
  static inline const int daysPerMonth[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30,
      31, 30, 31 };
  static const int stdYear{1970};
  static bool isLeapYear(int year)
  { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }
  void checkDate();
public:

  // *******************************************
  // *******************************************
  // *******************************************

  // ADDED FUCTIONS:

  int dayInYear() const;
  int operator-(const Date& d2);


  // *******************************************
  // *******************************************
  // *******************************************

  explicit Date(int d = 1, int m = 1, int y = stdYear) : day{d}, month{m},
                                                         year{y}
  {
    checkDate();
  }
  Date(const Date& d2) : day{d2.day}, month{d2.month}, year{d2.year} {}
  int getDay() const { return day; }
  int getMonth() const { return month; }
  int getYear() const { return year; }
  void setDate(int d, int m, int y)
  {
    day = d;
    month = m;
    year = y;
    checkDate();
  }
  Date& incDay();
  Date& operator++();
  Date operator++(int);
  void print() const { cout << day << '.' << month << '.' << year << endl; }
};

 // *******************************************
  // *******************************************
  // *******************************************

  // ADDED FUCTIONS:
int Date::dayInYear() const
{
    int dayInYear = day;
    int Month     = month;

    // store days considering the leap year
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Check if the year is leap year or not
    if (month > 2 && isLeapYear(year))
    {
        ++dayInYear;
    }

    //calculating the number of  days in the year
    while (Month > 0)
    {
        dayInYear = dayInYear + days[Month - 1];
        Month = Month - 1;
    }
    return dayInYear;
}


int Date::operator-(const Date& d2)
{

    return  abs(dayInYear() - d2.dayInYear());

}


  // *******************************************
  // *******************************************
  // *******************************************








void Date::checkDate()
{
  if (year < 1 || month < 1 || month > 12 || day < 1
      || (day > daysPerMonth[month - 1]
          && !(day == 29 && month == 2 && isLeapYear(year))))
    {
      day = month = 1;
      year = stdYear;
    }
}

Date& Date::incDay()
{
  ++day;
  if (day > daysPerMonth[month - 1]
      && !(day == 29 && month == 2 && isLeapYear(year)))
    {
      day = 1;
      if (++month == 13)
        {
          month = 1;
          ++year;
        }
    }
  return *this;
}

Date& Date::operator++()
{
  incDay();
  return *this;
}

Date Date::operator++(int)
{
  Date temp{*this};
  incDay();
  return temp;
}

ostream& operator<<(ostream& os, const Date& d)
{
  os << setw(2) << setfill('0') << d.getDay() << '.'
     << setw(2) << d.getMonth() << '.'
     << d.getYear() << setfill(' ');
  return os;
}

istream& operator>>(istream& is, Date& d)
{
  int dd, mm, yy;
  is >> dd;
  is.ignore(1, '.');
  is >> mm;
  is.ignore(1, '.');
  is >> yy;
  d.setDate(dd, mm, yy);
  return is;
}

int main()
{
Date d;
  Date d2;

  d2.setDate(21, 6, 2012);
  d2.print();
  d.setDate(10, 12, 2004);
  d.print();


  //d.day = 77;
  //d.print();


  cout << "Number of day in year is for d1 " << d.dayInYear() << endl;
  cout << "Number of day in year is for d2 " << d2.dayInYear() << endl;

  cout << "difference of date: " << d - d2 << endl;
}
