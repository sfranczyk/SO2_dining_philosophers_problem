#include <ncurses.h>
#include <string>
#include <thread>
#include <chrono>

#include "philosopher/philosopher.hpp"
#include "stick/stick.hpp"

/// funkcja wątku zamykającego program
void exiter(bool &kill){
    while(getch() != 'q' && getch() != 'Q');
    kill = true;
}

/// funkcja generująca tekst w konsoli we wskazanym miejscu
void printstr_colored(const int &color_id, const int &row, const int &col, const char str[]){
    attron( COLOR_PAIR( color_id ) );
    mvprintw( row, col, str );
    attroff( COLOR_PAIR( color_id ) );
}

/// funkcja generująca tekst w konsoli w miescu położenia kursora
void printstr_colored(const int &color_id, const char str[]){
    attron( COLOR_PAIR( color_id ) );
    addstr(str);
    attroff( COLOR_PAIR( color_id ) );
}

int main(){
    srand (time(NULL));

    // czas częstotliwości odświerzania konsoli
    const std::chrono::milliseconds refresh_freq = std::chrono::milliseconds(50);
    // liczba filozofów
    int number_philosophers;
    // zmienna informująca o zakończeniu działania programu
    bool kill = false;

    initscr();
    // if( has_colors() == TRUE )
    start_color();
    init_pair( 1, COLOR_BLUE, COLOR_BLACK );
    init_pair( 2, COLOR_GREEN, COLOR_BLACK );
    init_pair( 3, COLOR_BLACK, COLOR_RED );

    clear();
    printw( "How many philosophers you want to invite to the feast: ");
    // Zabezpieczenie w razie wpisania błędnego znaku
    while (scanw("%d", &number_philosophers) != 1)  
    {
        printw( "While writing invitations, a large blot flooded the number of invited philosophers. You have to remember how many you wanted to invite them and enter the correct number.\n");
        printw( "How many philosophers you want to invite to the feast: ");
    }
    if( number_philosophers < 5)
    {
        printw( "Too few philosophers have been invited. Fortunately, no one was guarding the entrance. As a result, %d more philosophers could drop in without an invitation to the feast.\n", 5 - number_philosophers);
        number_philosophers = 5;
    }
    flushinp();
    printw( "Press any key... ");
    getch();

    // inicjalizacja widelców
    stick ** sticks = new stick*[number_philosophers];
    for( int i = 0; i < number_philosophers; ++i)
        sticks[i] = new stick();

    // inicjalizacja filozofów
    philosopher ** philosophers = new philosopher*[number_philosophers];
    for( int i = 0; i < number_philosophers; ++i)
        philosophers[i] = new philosopher((*sticks[i]),(*sticks[(i+1)%number_philosophers]));
    
    // początek wątku wyjścia programu
    std::thread exit(exiter, std::ref(kill));
    do{
        clear();
        for( int i = 0; i < number_philosophers; ++i)
        {
            philosopher * _philosopher = philosophers[i];
            // jeśli filozof je
            if(_philosopher->get_state() == EATING)
            {
                printstr_colored(1, i, 0, ( "Philosopher " + std::to_string( _philosopher->get_id() ) + " eating" ).c_str() );
                printstr_colored(2, std::string( " : " + std::string( _philosopher->get_filling_points(), '|' ) ).c_str() );
                addstr(std::string( philosopher::max_filling_points - _philosopher->get_filling_points(), '|' ).c_str() );
                addstr((" [" + std::to_string(_philosopher->get_filling_points()) + " / " + std::to_string(philosopher::max_filling_points) + "]").c_str());
            }
            // jeśli filozof rozmyśla
            else
                printstr_colored(3, i, 0, ("Philosopher " + std::to_string( _philosopher->get_id() ) + " thinking").c_str());
        }
        for( int i = 0; i < number_philosophers; ++i)
        {
            std::string text = "Fork " + std::to_string(sticks[i]->get_id()) + (sticks[i]->get_philosophers_id() > -1 ? ": used by Philosopher " + std::to_string(sticks[i]->get_philosophers_id()) : ": is unused");
            printstr_colored(sticks[i]->get_philosophers_id() == -1 ? 3 : 2, i + 1 + number_philosophers, 0, text.c_str());
        }
        addstr("\n\nPress [Q] to end the program\n\0");

        // odświarzanie wyświetlacza
        refresh();
        std::this_thread::sleep_for(refresh_freq);
    }while(!kill);
    exit.join();
    
    clear();
    printw( "The feast is over.\nPress any key... ");
    refresh();
    flushinp();

    // kasowanie obiektów

    for( int i = 0; i < number_philosophers; ++i)
        delete philosophers[i];
    delete [] philosophers;

    for( int i = 0; i < number_philosophers; ++i)
        delete sticks[i];
    delete [] sticks;

    getch();

    endwin();
}
