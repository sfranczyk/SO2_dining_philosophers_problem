#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#pragma once

#include <thread>
#include <utility>
#include <unistd.h>
#include <chrono>

#include "../stick/stick.hpp"

enum state {THINKING, EATING};

class philosopher 
{
	public:
		static const unsigned short max_filling_points = 100;
		static std::chrono::milliseconds get_waiting_time(const int &divider);

		philosopher(stick &left, stick &right);
		~philosopher();

		int get_id();
		state get_state();
		unsigned short get_filling_points();

	private:
		static int id_counter;
		static bool the_feast_continues;
		static const unsigned short max_sleeping_points = 100;

		int id;
		state stt;
		std::thread exist;
		std::pair <stick*, stick*> forks;
		std::chrono::milliseconds sleep_time;
		unsigned short sleeping_points;
		unsigned short filling_points;

		void run();
		bool phase(unsigned short &up_points, const unsigned short max_up_points);
};
#endif