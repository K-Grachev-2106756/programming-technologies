#include<Manager/Manager.h>

#include<iostream>

int main()
{
	uint64_t* p = (uint64_t*)nullptr;
	int a = Man.CreateQueueMan(p);
	std::cout << std::endl;
	std::cout << a<<p;

}