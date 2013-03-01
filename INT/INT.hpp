class INT {
  int i;

  public:
  INT () { }
  INT (int ii) : i(ii) { }
  operator int() const { return i; }
};
