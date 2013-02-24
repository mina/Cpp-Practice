#include <string>

class Histogram {
  public:
    Histogram(int, int);
    Histogram& increment(int);
    std::string string_rep();
    ~Histogram();

    class Bad_Range { };
    class Out_Of_Range { };

  private:
    int *numbers, lowerbound, upperbound;
};
