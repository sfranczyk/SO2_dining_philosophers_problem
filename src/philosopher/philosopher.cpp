#include "philosopher.hpp"

using namespace std;

int philosopher::id_counter = 0;
bool philosopher::the_feast_continues = true;

philosopher::philosopher(stick &left, stick &right){
    id = id_counter++;
    filling_points = 0;
    sleeping_points = max_sleeping_points;
    this->forks = left.get_id() < right.get_id() ? make_pair(&left, &right) : make_pair(&right, &left);
    std::thread t(&philosopher::run, this); 
    this->exist = std::move(t);
    sleep_time = std::chrono::milliseconds(50);
    stt = MEDITATION;
}
	
philosopher::~philosopher(){
    the_feast_continues = false;
    forks.first->release();
    forks.second->release();
    exist.join();
}

void philosopher::run(){
    while(the_feast_continues)
    {
        std::this_thread::sleep_for( sleep_time );
        switch(stt)
        {
            case MEDITATION:
                if( !phase(sleeping_points, max_sleeping_points) )
                {
                    forks.first->use(id);
                    forks.second->use(id);
                    stt = EATING;
                }
                break;
            case EATING:
                if( !phase(filling_points, max_filling_points) )
                {
                    forks.first->release();
                    forks.second->release();
                    stt = MEDITATION;
                }
                break;
        }
    }
}

bool philosopher::phase(unsigned short& up_points, const unsigned short max_up_points){
    if(up_points++ < max_up_points)
        return true;
    up_points = 0;
    sleep_time = get_waiting_time(max_up_points);
    return false;           
}

state philosopher::get_state(){
    return stt;
}

int philosopher::get_id(){
    return id;
}

unsigned short philosopher::get_filling_points(){
    return filling_points;
}

std::chrono::milliseconds philosopher::get_waiting_time(const int & divider ){
    return std::chrono::milliseconds((rand() % 2000 + 2500) / divider);
}
