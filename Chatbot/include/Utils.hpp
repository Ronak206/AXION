// Lemmatizer.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

class Utils {
  public:
    static void handleExit(int signal);
    static void sigmoid(double* x, int size);
};

#endif // UTILS_HPP