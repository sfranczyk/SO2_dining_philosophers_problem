#include "fork.hpp"  
	
int fork::id_counter = 0;

fork::fork()
{
	id = id_counter++;
    philosopher_id = -1;
}

int fork::get_id() {
    return id;
}

int fork::get_philosophers_id() {
    return philosopher_id;
}

void fork::set_philosopher(const int &philosophers_id) {
    this->philosopher_id = philosopher_id;
}

void fork::release_fork() {
    philosopher_id = -1;
}
