#ifndef FORK_H
#define FORK_H
#pragma once
	
class fork  
{
	private:
		static int id_counter;
		int id;
		int philosopher_id;

	public:
		fork();
		~fork();

		int get_id();
		int get_philosophers_id();
		void set_philosopher(const int &philosophers_id);
		void release_fork();
};
#endif