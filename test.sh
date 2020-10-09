#!/bin/bash

# Test script for c/c++ std compliance
# Tested under ubuntu 20.04 and clang 10.0.0-4ubuntu1 and gcc Ubuntu 9.3.0-10ubuntu2

set -o errexit
set -o nounset
set -o pipefail
set -x

for STD in c89 c90 gnu89 gnu90 c99 gnu99 c11 gnu11 c17 gnu17
do
    clang -std=$STD -Wall -Weverything -Wpedantic -Werror -lm test.c && ./a.out || exit 1
    clang -std=$STD -Wall -Weverything -Wpedantic -Werror -lm example.c && ./a.out || exit 1
done

for STD in c89 c90 gnu89 gnu90 c99 gnu99 c11 gnu11 c17 gnu17
do
    gcc -std=$STD -Wall -Wpedantic -Werror -lm test.c && ./a.out || exit 1
    gcc -std=$STD -Wall -Wpedantic -Werror -lm example.c && ./a.out || exit 1
done

for STD in c++98 c++03 gnu++98 gnu++03 c++11 gnu++11 c++14 gnu++14 c++17 gnu++17 c++2a gnu++2a
do
    clang++ -std=$STD -Wall -Weverything -Wpedantic -Werror test.cpp && ./a.out || exit 1
done

for STD in c++98 c++03 gnu++98 gnu++03 c++11 gnu++11 c++14 gnu++14 c++17 gnu++17 c++2a gnu++2a
do
    g++ -std=$STD -Wall -Wpedantic -Werror test.cpp && ./a.out || exit 1
done
