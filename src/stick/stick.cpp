#include "stick.hpp"  
	
int stick::id_counter = 0;

stick::stick() {
    this->id = id_counter++;
    philosopher_id = -1;
}

stick::~stick() {
    mtx.unlock();
}

void stick::use(const int &philosophers_id) {
    mtx.lock();
    this->philosopher_id = philosophers_id;
}

void stick::release() {
    mtx.unlock();
    philosopher_id = -1;
}

int stick::get_id() {
    return id;
}

int stick::get_philosophers_id() {
    return philosopher_id;
}

