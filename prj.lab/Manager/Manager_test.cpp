#include<iostream>
#include<Manager/Manager.h>

int main()
{	
	uint64_t d = EmptyHandler;
	uint64_t* p = &d;
	std::cout << p<< " "<<*p << " "<<d;
	ErrorCode a = Man.CreateQueueMan(p);
	std::cout << std::endl;
	std::cout <<*p;

}