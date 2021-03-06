#include <ncurses.h>
#include <string>
#include <thread>
#include <chrono>

#include "philosopher/philosopher.hpp"
#include "stick/stick.hpp"


void exiter(bool &kill)
{
    while(getch() != 'q' && getch() != 'Q');
    kill = true;
}

void printstr_colored(const int &color_id, const int &row, const int &col, const char str[])
{
    attron( COLOR_PAIR( color_id ) );
    mvprintw( row, col, str );
    attroff( COLOR_PAIR( color_id ) );
}

int main()
{
    srand (time(NULL));
    std::string eat = "eating";
    int number_philosophers;
    bool kill = false;

    initscr();
    // if( has_colors() == TRUE )
    start_color();
    init_pair( 1, COLOR_BLUE, COLOR_BLACK );
    init_pair( 2, COLOR_GREEN, COLOR_BLACK );
    init_pair( 3, COLOR_BLACK, COLOR_RED );

    clear();
    printw( "How many philosophers you want to invite to the feast: ");
    while (scanw("%d", &number_philosophers) != 1)
    {
        printw( "While writing invitations, a large blot flooded the number of invited philosophers. You have to remember how many you wanted to invite them and enter the correct number.\n");
        printw( "How many philosophers you want to invite to the feast: ");
    }
    if( number_philosophers < 5)
    {
        printw( "Too few philosophers have been invited. Fortunately, no one was guarding the entrance. As a result, %d more philosophers could invite to the feast. ", 5 - number_philosophers);
        number_philosophers = 5;
    }
    flushinp();
    printw( "\nPress any key... ");
    getch();

    stick ** sticks = new stick*[number_philosophers];
    for( int i = 0; i < number_philosophers; ++i)
        sticks[i] = new stick();

    philosopher ** philosophers = new philosopher*[number_philosophers];
    for( int i = 0; i < number_philosophers; ++i)
        philosophers[i] = new philosopher((*sticks[i]),(*sticks[(i+1)%number_philosophers]));
    
    std::thread exit(exiter, std::ref(kill));
    do{
        clear();

        for( int i = 0; i < number_philosophers; ++i)
        {
            philosopher * _philosopher = philosophers[i];
            state stt = _philosopher->get_state();
            std::string text = "Philosopher " + std::to_string(_philosopher->get_id()) + (stt == MEDITATION ? " meditates" : " eating");
            if(stt == EATING)
            {
                printstr_colored(1, i, 0, text.c_str());

                attron( COLOR_PAIR( 2 ) );
                addstr(" : \0");
                for( int j = 0; j < _philosopher->get_filling_points(); ++j)
                    addch('|');
                attroff( COLOR_PAIR( 2 ) );

                for(int j = _philosopher->get_filling_points(); j < philosopher::max_filling_points; ++j)
                    addch('|');

                text = " [" + std::to_string(_philosopher->get_filling_points()) + " / " + std::to_string(philosopher::max_filling_points) + "]";
                addstr(text.c_str());
            }
            else
            {
                printstr_colored(3, i, 0, text.c_str());
            }
        }
        for( int i = 0; i < number_philosophers; ++i)
        {
            std::string text = "Fork " + std::to_string(sticks[i]->get_id());
            text += sticks[i]->get_philosophers_id() > -1 ? ": used by Philosopher " + std::to_string(sticks[i]->get_philosophers_id()) : ": is unused";

            printstr_colored(sticks[i]->get_philosophers_id() == -1 ? 3 : 2, i + 1 + number_philosophers, 0, text.c_str());
        }
        addstr("\n\nPress [Q] to end the program\n\0");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }while(!kill);
    exit.join();
    
    clear();
    printw( "The feast is over.\nPress any key... ");
    refresh();
    flushinp();

    for( int i = 0; i < number_philosophers; ++i)
        delete philosophers[i];
    delete [] philosophers;

    for( int i = 0; i < number_philosophers; ++i)
        delete sticks[i];
    delete [] sticks;

    getch();

    endwin();
}
