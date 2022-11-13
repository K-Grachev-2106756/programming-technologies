#include<iostream>
#include<Manager/Manager.h>

int main()
{	

	uint64_t a = EmptyHandler;
	uint64_t* b = &a;

	Man.CreateQueueMan(b);
	
	uint64_t c = EmptyHandler;
	uint64_t* d = &c;

	Man.CloneQueueMan(0, d);

	Man.PushMan(1, 1);
	Man.PushMan(1, 1);

	std::cout<<Man.MainData[1];
}