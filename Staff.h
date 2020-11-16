template <int p>
struct PowerOfThree {
    static const int value = PowerOfThree<p-1>::value * 3;
};

template<>
struct PowerOfThree<0> {
    static const int value = 1;
};

template <int p>
struct PowerOfThreeSum {
    static const int value = PowerOfThreeSum<p-1>::value + 2 * PowerOfThree<p>::value;
};

template<>
struct PowerOfThreeSum<0> {
    static const int value = 0;
};

template <typename T>
struct Holder {
    T value;
};

template<int level, int number>
struct DividingStepStartIndex {
    static const int base = PowerOfThreeSum<level / 2>::value;
    static const int step = number - (PowerOfThreeSum<level / 2>::value - PowerOfThree<level / 2>::value) - 1;
    static const int index = base + 3 * step;
};

template<int level, int number>
struct LinearStepIndex {
    static const int index = number + PowerOfThree<((level + 1) / 2)>::value;
};
