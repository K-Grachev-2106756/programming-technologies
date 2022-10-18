#include <QueueP/QueueP.h>
#include <iostream>
int main()
{
	//uint64_t p = (uint64_t)std::make_unique<QueueP>().get();
	//uint64_t* d(&p);
	//std::cout << p << std::endl;
	//std::cout << d << std::endl;
	//d = (uint64_t*)std::make_unique<QueueP>().get();
	//std::cout << d;

	QueueP* L = new QueueP;

	uint64_t* p = (uint64_t*)L;

	uint64_t b;
	QueueP f;
	b = (uint64_t)&f;	

	std::cout << b;
}