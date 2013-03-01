#include "string.hpp"
#include <cstring>

String::String()
{
  rep = new Srep(0, "");
}

String::String(const String& x)
{
  x.rep->n++;
  rep = x.rep;
}

String::~String()
{
  if (--rep->n == 0) delete rep;
}

String& String::operator=(const String&x)
{
  x.rep->n++;
  if (--rep->n == 0) delete rep;
  rep = x.rep;
  return *this;
}

String::String(const char *s)
{
  rep = new Srep(strlen(s), s);
}

String& String::operator=(const char* s)
{
  if (rep->n == 1) rep->assign(strlen(s), s);
  else
  {
    rep->n--;
    rep = new Srep(strlen(s), s);
  }
  return *this;
}

bool operator==(const String& x, const char *s)
{
  return strcmp(x.rep->s, s) == 0;
}
bool operator==(const String& x, const String& y)
{
  return strcmp(x.rep->s, y.rep->s) == 0;
}

bool operator!=(const String& x, const char *s)
{
  return strcmp(x.rep->s, s) != 0;
}
bool operator!=(const String& x, const String& y)
{
  return strcmp(x.rep->s, y.rep->s) != 0;
}

std::istream& operator>>(std::istream& in, String& s)
{
  static char buf[1024];
  int i = 0;

  if (--(s.rep->n) == 0) delete s.rep;
  s.rep = new String::Srep(0, "");
  while (in && in.peek() != '\n')
  {
    in.get(buf[i]);
    if (++i == 1023)
    {
      buf[i] = '\0';
      s = s + buf;
      i = 0;
    }
  }

  buf[i] = '\0';
  s = s + buf;

  return in;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
  out << s.rep->s;
  return out;
}

String operator+ (const String& s1, const String& s2)
{
  char c[strlen(s1.rep->s) + strlen(s2.rep->s) + 2];
  strcpy(c, s1.rep->s);
  strcat(c, s2.rep->s);
  return String(c);
}

String operator+ (const String& s, const char *cp)
{
  char c[strlen(s.rep->s) + strlen(cp) + 2];
  strcpy(c, s.rep->s);
  strcat(c, cp);
  return String(c);
}

String& append(char *s, int n);

String f(String a, String b)
{
  a[2] = 'x';
  //char c = b[3];
  std::cerr << "started f\n";
  //std::cout << "in f: " << a << ' ' << b << ' ' << c << '\n' ;
  return b;
}

int main()
{
  using std::cerr;
  String x, y;
  std::cout << "Please enter two strings\n";
  std::cin >> x >> y;
  std::cout << "input: " << x << ' ' << y << '\n';
  String z = x;
  cerr << z;
  y = f(x, y);
  cerr << "reached here\n";
  if (x != z) std::cout << "x corrupted!\n";
  x[0] = '!';
  if (x == z) std::cout << "write failed!\n";
  std::cout << "exit: " << x << ' ' << y << ' ' << z << '\n';
}
