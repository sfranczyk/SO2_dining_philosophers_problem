#include "stick.hpp"  
	
int stick::id_counter = 0;

stick::stick() {
    this->id = id_counter++;
    philosopher_id = -1;
}

int stick::get_id() {
    return id;
}

int stick::get_philosophers_id() {
    return philosopher_id;
}

void stick::set_philosopher(int philosophers_id) {
    this->philosopher_id = philosophers_id;
}

void stick::release_fork() {
    philosopher_id = -1;
}
