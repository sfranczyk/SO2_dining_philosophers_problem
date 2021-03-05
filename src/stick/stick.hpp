#ifndef FORK_H
#define FORK_H
#pragma once
	
class stick  
{
	private:
		static int id_counter;
		int id;
		int philosopher_id;

	public:
		explicit stick();

		int get_id();
		int get_philosophers_id();
		void set_philosopher(int philosophers_id);
		void release_fork();

};
#endif