#pragma once
#define LOCSTR(token) hash(#token)

#include <iostream>
#include <random>

class Utils
{
    public :
        template<typename Iter, typename RandomGenerator>
        static Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
            std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
            std::advance(start, dis(g));
            return start;
        }

        template<typename Iter>
        static Iter select_randomly(Iter start, Iter end) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return select_randomly(start, end, gen);
        }

        static constexpr int hash(const char* string) {
            unsigned long hash = 5381;
            int c;

            while (c = *string++)
                hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

            return hash;
        }
};

