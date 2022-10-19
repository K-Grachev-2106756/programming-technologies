#include<iostream>
#include<QueueP/QueueP.h>
#include<vector>
#include<CQueueP/CQueueP.h>
#include<map>
//singleton

class Manager {
public:
	//Очистка памяти 
	//подключить сюды C файл 
	std::map<uint64_t, QueueP> MainData;
	Manager() = default;
	~Manager() = default;
	
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

