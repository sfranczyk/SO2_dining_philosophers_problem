#ifndef FORK_H
#define FORK_H
#pragma once
	
#include <mutex>

class stick  
{
	private:
		static int id_counter;

		int id;
		int philosopher_id;
		std::mutex mtx;

	public:
		explicit stick();
		
		void use(int philosophers_id);
		void release();

		int get_id();
		int get_philosophers_id();
};
#endif