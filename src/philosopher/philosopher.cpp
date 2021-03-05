#include "philosopher.hpp"

using namespace std;

int philosopher::id_counter = 0;
bool philosopher::the_feast_continues = true;

philosopher::philosopher(stick left, stick right)
{
    id = id_counter++;
    filling_points = 0;

    this->forks = left.get_id() < right.get_id() ? make_pair(left, right) : make_pair(right, left);

    std::thread t(&philosopher::run, this);
    this->exist = std::move(t);
    stt = MEDITATION;
}
	
philosopher::~philosopher()
{
    the_feast_continues = false;
    exist.join();
}

void philosopher::run()
{
    while(the_feast_continues)
    {
        switch(stt)
        {
            case MEDITATION:
            {
                std::this_thread::sleep_for(rand_meditation_time());
                //TODO
                stt = EATING;
                break;
            }
            case EATING:
            {
                //TODO
                stt = MEDITATION;
                break;
            }
        }
    }
}

int philosopher::get_id(){
    return id;
}

std::string philosopher::get_state()
{
    switch(stt)
    {
        case MEDITATION:
            return "meditate";
        case EATING:
            return "eating";
        default:
            return "err";
    }
}

std::chrono::milliseconds philosopher::rand_meditation_time()
{
    return std::chrono::milliseconds(rand() % 2000 + 2500);
}