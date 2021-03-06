#include "philosopher.hpp"

using namespace std;

int philosopher::id_counter = 0;
bool philosopher::the_feast_continues = true;

philosopher::philosopher(stick &left, stick &right)
{
    id = id_counter++;
    filling_points = 0;

    this->forks = left.get_id() < right.get_id() ? make_pair(&left, &right) : make_pair(&right, &left);

    std::thread t(&philosopher::run, this);
    this->exist = std::move(t);
    stt = MEDITATION;
}
	
philosopher::~philosopher()
{
    the_feast_continues = false;
    forks.first->release();
    forks.second->release();
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
                std::this_thread::sleep_for( meditation_time() );
                filling_points = 0;
                forks.first->use(id);
                forks.second->use(id);
                stt = EATING;
                break;
            }
            case EATING:
            {
           		std::chrono::milliseconds eating_time = get_eating_time();
                while( filling_points < max_filling_points)
                {
                    std::this_thread::sleep_for( eating_time );
                    ++filling_points;
                }
                forks.first->release();
                forks.second->release();
                stt = MEDITATION;
                break;
            }
        }
    }
}

int philosopher::get_id(){
    return id;
}

unsigned short philosopher::get_filling_points()
{
    return filling_points;
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

std::chrono::milliseconds philosopher::meditation_time()
{
    return std::chrono::milliseconds(rand() % 2000 + 2500);
}

std::chrono::milliseconds philosopher::get_eating_time()
{
    return std::chrono::milliseconds((rand() % 2000 + 2500) / max_filling_points);
}
