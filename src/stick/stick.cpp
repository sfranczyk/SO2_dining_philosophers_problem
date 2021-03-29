#include "stick.hpp"  
	
int stick::id_counter = 0;

stick::stick() {
    // nadanie id/piorytetu widelcowi
    this->id = id_counter++;
    philosopher_id = -1;
}

stick::~stick() {
    // odblokowywanie wątku
    mtx.unlock();
}

// metoda użycia widelca
void stick::use(const int &philosophers_id) {
    // blokowanie wątków
    mtx.lock();
    this->philosopher_id = philosophers_id;
}

// metoda odłożenia widelca
void stick::release() {
    // odblokowywanie wątku
    mtx.unlock();
    philosopher_id = -1;
}

int stick::get_id() {
    return id;
}

int stick::get_philosophers_id() {
    return philosopher_id;
}

