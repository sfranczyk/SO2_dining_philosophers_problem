#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#pragma once

#include <thread>
#include <utility>
#include <unistd.h>
#include <chrono>

#include "../stick/stick.hpp"

enum state {MEDITATION, EATING};

class philosopher 
{
	private:
		static int id_counter;
		static bool the_feast_continues;

		int id;
		unsigned short filling_points;
		std::thread exist;
		state stt;
		std::pair <stick*, stick*> forks;

		void run();

	public:
		static const unsigned short max_filling_points = 100;

		philosopher(stick &left, stick &right);
		~philosopher();

		int get_id();
		unsigned short get_filling_points();
		state get_state();

		std::chrono::milliseconds meditation_time();
		std::chrono::milliseconds get_eating_time();
};
#endif