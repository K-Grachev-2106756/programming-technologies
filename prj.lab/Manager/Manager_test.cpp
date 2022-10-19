#include<Manager/Manager.h>

#include<iostream>

int main()
{	
	uint64_t d = EmptyHandler;
	uint64_t* p = &d;
	std::cout << p;
	int a = Man.CreateQueueMan(p);
	std::cout << std::endl;
	std::cout <<*p;

}