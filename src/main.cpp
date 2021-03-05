#include <iostream>
#include <ncurses.h>

#include "philosopher/philosopher.hpp"
#include "stick/stick.hpp"

#include <thread>

int main()
{
    srand (time(NULL));
    stick f1, f2, f3;
    philosopher p(f1, f2);
    philosopher c(f2, f3);
    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // getch();
}