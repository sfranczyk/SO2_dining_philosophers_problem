#ifndef PHILOSOPH_H
#define PHILOSOPH_H
#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include <thread>
using namespace std;

enum state { MEDITATION, EATING, WAITING_FOR_THE_FORKS};
	
class philosoph  
{
	private:
		int id;
		state stt;
		unsigned short filling_points;

		void run();

		static int id_counter;
		static bool the_feast_continues;

	public:
		static const unsigned short max_filling_points = 100;
		std::thread exist;
		philosoph();
		~philosoph();

		int get_id();
		int get_filling_points();
		string get_state();
};
#endif