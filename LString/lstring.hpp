#include <cstring>
#include <iostream>


class LString {
  struct LSrep {
    LSrep *next;
    char *s;
    int sz;
    int n;

    public:

    LSrep(int nsz, const char*p, LSrep* nnext = 0)
    : next(nnext), sz(nsz)
    {
      n = 1;
      s = new char [sz+1];
      strcpy(s,p);
    }

    ~LSrep() { delete[] s; }

    LSrep* get_own_copy()
    {
      if (n == 1) return this;
      n--;
      return new LSrep(sz,s);
    }

    void assign(int nsz, const char *p)
    {
      if (sz != nsz)
      {
        delete[] s;
        sz = nsz;
        s = new char[sz+1];
      }
      strcpy(s,p);
    }

    private:

    LSrep(const LSrep&);
    LSrep& operator=(const LSrep&);
  };
  LSrep *rep;
  int length;

  public:

  class Cref {
    friend class LString;

    LString& s;
    int i;
    Cref (LString& ss, int ii) : s(ss), i (ii) { }

    public:

    operator char() { return s.read(i); }
    void operator=(char c) {s.write(i, c); }
  };

  class Range { };
  LString();
  LString(const char *);
  LString(const LString&);
  LString& operator=(const char*);
  LString& operator=(const LString&);
  ~LString();

  int get_length() const { return this->length; }
  void check(int i) const { if (i<0 || rep->sz <= i) throw Range(); }
  char read(int i) const { return rep->s[i]; }
  void write(int i, char c) { rep=rep->get_own_copy(); rep->s[i] = c; }

  Cref operator[](int i) { check(i); return Cref(*this, i); }
  char operator[](int i) const { check(i); return rep->s[i]; }

  int size() const { return rep->sz; }

  LString& operator+=(const LString&);
  LString& operator+=(const char *);

  friend std::ostream& operator<<(std::ostream&, const LString&);
  friend std::istream& operator>>(std::istream&, LString&);

  friend bool operator==(const LString& x, const char *s);
  friend bool operator==(const LString& x, const LString& y);

  friend bool operator!=(const LString& x, const char *s);
  friend bool operator!=(const LString& x, const LString& y);

  friend LString operator+ (const LString&, const LString&);
  friend LString operator+ (const LString&, const char *);
};
