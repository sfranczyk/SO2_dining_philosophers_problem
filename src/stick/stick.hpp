#ifndef FORK_H
#define FORK_H
#pragma once
	
#include <mutex>

class stick  
{
	public:
		explicit stick();
		~stick();
		
		void use(const int &philosophers_id);
		void release();
		int get_id();
		int get_philosophers_id();

	private:
		static int id_counter;

		int id;
		int philosopher_id;
		std::mutex mtx;
};
#endif