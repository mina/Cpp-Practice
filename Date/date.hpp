namespace Chrono {
#include <string>

  class Date {
    public:
      enum Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
      class Bad_date { };
      Date(int dd = 0, Month mm = Month(0), int yy = 0);

      int day() const { return d; }
      Month month() const { return m; }
      int year() const {return y; }
      std::string string_rep() const;
      void char_rep(char *s) const;

      static void set_default(int, Month, int);

      Date& add_year(int n);
      Date& add_month(int n);
      Date& add_day(int n);

    private:
      int d, y;
      Month m;
      static Date default_date;
  };

  int diff(Date a, Date b);
  int days_in_month(Date::Month m, int yy);
  bool leapyear(int y);
  Date next_weekday(Date d);
  Date next_saturday(Date d);
}
