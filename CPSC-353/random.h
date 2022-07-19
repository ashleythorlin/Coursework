#ifndef random_h
#define random_h

#include <random>
#include <vector>


template <typename T>
static void check(T low, T high) { 
      if (low > high) { throw new std::invalid_argument("in random.h, a > b\n"); }
}


template <typename T>
class std_random {
    typedef std::default_random_engine        engine;
    typedef std::uniform_int_distribution<T>  uniform_between;
  
public:
    static T generate_uniform_value(T low, T high) {   
        check(low, high);
  
        engine            gen = get_gen();
        uniform_between   distro(low, high);
        return distro(gen);
    }

  static void generate_uniform_values(std::vector<T>& v, size_t n, T low, T high) {
      check(low, high);
  
      engine gen = get_gen();
      uniform_between distro(low, high);
      for (size_t i = 0; i < n; ++i) {
          v.push_back(distro(gen));
      }
  }

private:
    static engine get_gen() {
        std::random_device           rd;          // Will be used to obtain a seed for the random number engine
        std::default_random_engine   gen(rd());   //    Standard mersenne_twister_engine seeded with rd()
        return gen;
    }
};


template <typename T>
T rand_between(T low, T high) { 
    check(low, high);
  
    return std_random<T>::generate_uniform_value(low, high);
}

template <typename T>
void rand_between(std::vector<T>& values, unsigned int n, T low, T high) {
    for (unsigned int i = 0; i < n; ++i) { values.push_back(rand_between(low, high)); }
}

template <typename T>
void append_value(std::vector<T>& values, unsigned int n, T value) {
    for (unsigned int i = 0; i < n; ++i) { values.push_back(value); }
}

template <typename T>
T rand_upto(T high) { return rand_between(0, high); }


#endif /* random_h */

