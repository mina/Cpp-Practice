#include "lstring.hpp"
#include <cstring>

LString::LString() : length(0)
{
  rep = new LSrep(0, "");
}

LString::LString(const LString& x) : length(x.length)
{
  this->rep = x.rep;
  LSrep* cur_rep = this->rep;
  while (cur_rep)
  {
    cur_rep->n++;
    cur_rep = cur_rep->next;
  }
}

LString::~LString()
{
  LSrep* cur_rep = this->rep;
  LSrep* next_rep = this->rep->next;
  while (cur_rep)
  {
    next_rep = cur_rep->next;
    if (--(cur_rep->n) == 0) delete cur_rep;
    cur_rep = next_rep;
  }
}

LString& LString::operator=(const LString&x)
{
  if ( &x == this )
  {
    return *this;
  }
  rep = x.rep;
  LSrep* cur_rep = rep;
  while (cur_rep)
  {
    (cur_rep->n)++;
    cur_rep = cur_rep->next;
  }
  return *this;
}

LString::LString(const char *s) : length(strlen(s))
{
  rep = new LSrep(strlen(s), s);
}

LString& LString::operator=(const char* s)
{
  LSrep* cur_rep = rep;
  LSrep* next_rep = rep->next;
  while (cur_rep)
  {
    next_rep = cur_rep->next;
    if (--(cur_rep->n) == 0) delete cur_rep;
    cur_rep = next_rep;
  }

  rep = new LSrep(strlen(s), s);
  return *this;
}

bool operator==(const LString& x, const char *s)
{
  if (strlen(s) != x.length) return false;
  else
  {
    bool same = true;
    LString::LSrep* cur_rep = x.rep;
    while (cur_rep)
    {
      if (strncmp(s, cur_rep->s, strlen(cur_rep->s)) != 0)
      {
        same = false;
        break;
      }
      else
      {
        s += strlen(cur_rep->s);
        cur_rep = cur_rep->next;
      }
    }
    return same;
  }
}

//bool operator==(const LString& x, const LString& y)

bool operator!=(const LString& x, const char *s)
{
  return !(x == s);
}

//bool operator!=(const LString& x, const LString& y)

std::istream& operator>>(std::istream& in, LString& s)
{
  LString::LSrep* cur_rep = s.rep;
  LString::LSrep* next_rep = s.rep->next;
  while (cur_rep)
  {
    next_rep = cur_rep->next;
    if (--(cur_rep->n) == 0) delete cur_rep;
    cur_rep = next_rep;
  }

  static char buf[1024];
  int i = 0;

  s.rep = new LString::LSrep(0, "");
  while (in && in.peek() == ' ') in.get(buf[0]);
  while (in && in.peek() != ' ' && in.peek() != '\n')
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

std::ostream& operator<<(std::ostream& out, const LString& s)
{
  out << s.rep->s;
  return out;
}

//LString operator+ (const LString& s1, const LString& s2)

LString operator+ (const LString& s, const char *cp)
{
  LString::LSrep* next_rep = new LString::LSrep(strlen(cp), cp);
  LString::LSrep* cur_rep = s.rep;
  while (cur_rep->next)
  {
    (cur_rep->n)++;
    cur_rep->next
  while (last_rep->next) last_rep = last_rep->next;
  last_rep->next = next_rep;
}

LString f(LString a, LString b)
{
  a[2] = 'x';
  char c = b[3];
  std::cerr << "started f\n";
  std::cout << "in f: " << a << ' ' << b << ' ' << c << '\n' ;
  return b;
}

int main()
{
  using std::cerr;
  LString x, y;
  std::cout << "Please enter two strings\n";
  std::cin >> x >> y;
  std::cout << "input: " << x << ' ' << y << '\n';
  LString z = x;
  cerr << z;
  y = f(x, y);
  cerr << "reached here\n";
//  if (x != z) std::cout << "x corrupted!\n";
//  x[0] = '!';
//  if (x == z) std::cout << "write failed!\n";
  std::cout << "exit: " << x << ' ' << y << ' ' << z << '\n';
}
