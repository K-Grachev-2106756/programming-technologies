#include <QueueP/QueueP.h>
#include <iostream>
int main()
{
	QueueP a;
	a.push(7);
	a.push(8);
	a.push(9);
	a.push(8);
	a.push(5);
	a.push(8);


	std::cout << a;
}