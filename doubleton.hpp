/*
 * doubleton.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: pgd
 */

#ifndef DOUBLETON_HPP_
#define DOUBLETON_HPP_

#include <iterator>
#include <utility>
#include <vector>

//#include <utility>

/// an unordered pair class --- a doubleton
class doubleton: public std::pair<int, int> {

public:
    doubleton(int a, int b) {
        first = a;
        second = b;
    }

    ~doubleton() {

    }

    bool contains(const int a) {
        return first == a || second == a;
    }

    int get_other(const int a) {
        if (!contains(a))
            return -1; //throw new std::domain_error;
        if (first == a)
            return second;
        return first;
    }

    /// being unordered, does not distinguish between (a,b) and (b,a)
    bool operator==(const doubleton &other) {
        bool a = first == other.first && second == other.second;
        bool b = first == other.second && second == other.first;
        return a || b;
    }

    /// returns true if d is member of v
    bool operator%(std::vector<doubleton> v) {
        for (std::vector<doubleton>::iterator it = v.begin(); it != v.end();
                ++it) {
            if (*it == *this) {
                return true;
            }
        }
        return false;
    }
};

#endif /* DOUBLETON_HPP_ */
