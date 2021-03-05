#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#pragma once

#include <cstdlib>
#include <string>
#include <thread>
#include <utility>
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <mutex>

#include "../stick/stick.hpp"

enum state { MEDITATION, EATING};
	
class philosopher 
{
	stick f;
	private:
		int id;
		state stt;
		unsigned short filling_points;

		void run();

		static int id_counter;
		static bool the_feast_continues;
		std::pair <stick, stick> forks;

	public:
		static const unsigned short max_filling_points = 100;
		std::thread exist;
		philosopher(stick, stick);
		~philosopher();

		int get_id();
		int get_filling_points();
		std::string get_state();

		std::chrono::milliseconds rand_meditation_time();

};
#endif