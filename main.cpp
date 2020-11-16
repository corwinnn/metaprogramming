#include <iostream>

#include "Zoo.h"
#include "Typelist.h"
#include "Staff.h"

template <typename T, class TList, int number, int level, bool linear, template <class> class Unit>
struct Level;

template <class TList, int number, int level, template <class> class Unit>
struct Level<Nulltype, TList, number, level, true, Unit> {};

template <class TList, int number, int level, template <class> class Unit>
struct Level<Nulltype, TList, number, level, false, Unit> {};

template <typename T, class TList, int number, int level, template <class> class Unit>
struct Level<T, TList, number, level, true, Unit> :
        public Level<typename TypeAt<LinearStepIndex<level, number>::index,
             TList>::res, TList, LinearStepIndex<level, number>::index, level + 1, false, Unit> {
    Level() {
        printf("Number: %d, Level: %d, Type: %s\n", number, level, typeid(T).name());
    }
    Unit <typename TypeAt<number, TList>::res> x{};
};

template <typename T, class TList, int number, int level, template <class> class Unit>
struct Level<T, TList, number, level, false, Unit> :
        public Level<typename TypeAt<DividingStepStartIndex<level, number>::index + 1, TList>::res,
                TList,
                DividingStepStartIndex<level, number>::index + 1,
                level + 1,
                true,
                Unit>,
        public Level<typename TypeAt<DividingStepStartIndex<level, number>::index + 2, TList>::res,
                TList,
                DividingStepStartIndex<level, number>::index + 2,
                level + 1,
                true,
                Unit>,
        public Level<typename TypeAt<DividingStepStartIndex<level, number>::index + 3, TList>::res,
                TList,
                DividingStepStartIndex<level, number>::index + 3,
                level + 1,
                true,
                Unit> {
    Level() {
        printf("Number: %d, Level: %d, Type: %s\n", number, level, typeid(T).name());
    }
    Unit <typename TypeAt<number, TList>::res> x{};
};


template <class TList, template <class> class Unit>
struct GenCustomHierarchy:
            public Level<typename TypeAt<1, TList>::res, TList, 1, 1, true, Unit>,
            public Level<typename TypeAt<2, TList>::res, TList, 2, 1, true, Unit>,
            public Level<typename TypeAt<3, TList>::res, TList, 3, 1, true, Unit> {
    GenCustomHierarchy() {
        printf("Number: %d, Level: %d, Type: %s\n", 0, 0, typeid(typename TypeAt<0, TList>::res).name());
    }
    Unit <typename TypeAt<0, TList>::res> x{};
};

int main() {
    
    GenCustomHierarchy<
        TypeList<
             Dog, Cat, Zebra, Horse, Lemming, Chicken, Monkey,
             Sheep, Raccoon, Lion, Tiger, Eagle, Squirrel, Cobra,
             Duck, Penguin, Fox, Kangaroo, Alligator, Goat, Goose,
             Deer, Suricate, Wolf, Elephant
        >,
        Holder
    > x;
    
}
