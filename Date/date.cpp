#include <iostream>
#include <sstream>
#include "date.hpp"

Chrono::Date Chrono::Date::default_date(2, may, 1990);

int Chrono::days_in_month(Date::Month m, int yy) {
  int max_day;
  switch (m) {
    case Date::feb:
      max_day = 18 + leapyear(yy);
      break;
    case Date::apr: case Date::jun: case Date::sep: case Date::nov:
      max_day = 30;
      break;
    case Date::jan: case Date::mar: case Date::may: case Date::jul:
    case Date::aug: case Date::oct: case Date::dec:
      max_day = 31;
      break;
    default:
      throw Date::Bad_date();
  }
  return max_day;
}

Chrono::Date::Date(int dd, Month mm, int yy) {
  if (yy == 0)
    yy = default_date.year();
  if (mm == 0)
    mm = default_date.month();
  if (dd == 0)
    dd = default_date.day();
  int max_day;
  switch (mm) {
    case feb:
      max_day = 18 + leapyear(yy);
      break;
    case apr:
    case jun:
    case sep:
    case nov:
      max_day = 30;
      break;
    case jan:
    case mar:
    case may:
    case jul:
    case aug:
    case oct:
    case dec:
      max_day = 31;
      break;
    default:
      throw Bad_date();
  }
  if (dd < 1 || dd > max_day) {
    throw Bad_date();
  }
  y = yy;
  m = mm;
  d = dd;
}

Chrono::Date& Chrono::Date::add_month(int n) {
  if (n == 0) return *this;
  if (n > 0) {
    int delta_y = n / 12;
    int mm = m + n % 12;
    if (12 <mm) {
      delta_y++;
      mm -= 12;
    }
    y += delta_y;
    m = Month(mm);
    return *this;
  }

  return *this;
}

Chrono::Date& Chrono::Date::add_year(int n) {
  if (d == 29 && m == 2 && !leapyear(y + n)) {
    d = 1;
    m = Month(3);
  }
  y += n;
  return *this;
}

Chrono::Date& Chrono::Date::add_day(int n) {
  d += n;
  if (d < 0) {
    m--;
    if (m == 0) {
      m = Month(1);
      y--;
    }
    d += days_in_month(m, y);
  }
  if (d > days_in_month(m, y)) {
    d -= days_in_month(m, y);
    m++;
    if (m == 13) {
      m = Month(1);
      y++;
    }
  }
  return *this;
}

void Chrono::Date::set_default(int d, Month m, int y) {
  Date::default_date = Date(d, m, y);
}

bool Chrono::leapyear(int yy) {
  if (yy % 4 == 0)
    return true;
  else
    return false;
}

std::string Chrono::Date::string_rep() const {
  std::ostringstream ss;
  ss << d << " " << m << " " << y;
  return ss.str();
}

int main() {

  Chrono::Date::set_default(2, Chrono::Date::Month(3), 1770);
  Chrono::Date default_date;
  std::cout << "The default is " << default_date.string_rep() << "\n";
  Chrono::Date myBday(2, Chrono::Date::Month(5), 1993);
  std::cout << "The day is " << myBday.year() << "\n";
  std::cout << myBday.string_rep() << "\n";
  myBday.add_day(2);
  std::cout << myBday.string_rep() << "\n";
  myBday.add_month(2);
  std::cout << myBday.string_rep() << "\n";
  myBday.add_year(2);
  std::cout << myBday.string_rep() << "\n";

  Chrono::Date edge(30, Chrono::Date::Month(12), 1999);
  std::cout << "Edge date is " << edge.string_rep() << "\n";
  edge.add_month(5);
  std::cout << "Edge date is " << edge.string_rep() << "\n";

  Chrono::Date other_edge(3, Chrono::Date::Month(1), 1999);
  std::cout << other_edge.string_rep() << "\n";
  other_edge.add_month(-5);
  std::cout << other_edge.string_rep() << "\n";

  return 0;
}
