#include<iostream>
#include<QueueP/QueueP.h>
#include<vector>

typedef uint64_t QueueHandler;

class Manager {
public:
	
	Manager() = default;
	~Manager() = default;
	
	int CreateQueueMan(QueueHandler* queue);
	int CloneQueueMan(QueueHandler source, QueueHandler* queue);
	int DestroyQueueMan(QueueHandler queue);
	int PopMan(QueueHandler queue);
	int PushMan(QueueHandler queue, int32_t value);
	int IsEmptyMan(QueueHandler queue, int32_t* result);
	int TopMan(QueueHandler queue, int32_t* result);

private:
};

static Manager Man;

