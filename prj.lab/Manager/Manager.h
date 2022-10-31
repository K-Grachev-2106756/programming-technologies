#include<QueueP/QueueP.h>
#include<CQueueP/CQueueP.h>
#include<unordered_map>
//singleton

class Manager {
public:
	//Очистка памяти 
	std::unordered_map<QueueHandler, QueueP> MainData;
	Manager() = default;
	~Manager();
	
	ErrorCode CreateQueueMan(QueueHandler* queue);
	ErrorCode CloneQueueMan(QueueHandler source, QueueHandler* queue);
	ErrorCode DestroyQueueMan(QueueHandler queue);
	ErrorCode PopMan(QueueHandler queue);
	ErrorCode PushMan(QueueHandler queue, int32_t value);
	ErrorCode IsEmptyMan(QueueHandler queue, int32_t* result);
	ErrorCode TopMan(QueueHandler queue, int32_t* result);

private:
};

static Manager Man;

