#include "philosoph.hpp" 

#include <stdio.h>
#include <unistd.h> 
	
int philosoph::id_counter = 0;
bool philosoph::the_feast_continues = true;

philosoph::philosoph()
{
    std::thread t(&philosoph::run, this);
    this->exist = std::move(t);
    stt = WAITING_FOR_THE_FORKS;
    filling_points = 0;

    id = id_counter++;
}
	
philosoph::~philosoph()
{
    the_feast_continues = false;
    exist.join();
}

void philosoph::run()
{
    while(the_feast_continues)
    {
        printf("Hello there: %d\n", id);
    }
}

int philosoph::get_id(){
    return id;
}
