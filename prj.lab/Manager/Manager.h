#include<iostream>
#include<QueueP/QueueP.h>
typedef enum {
	kGood = 0,   // all right
	kHandlerError, // bad handler
	kOutOfRange    // queue is empty
} ErrorCode;

typedef uint64_t QueueHandler;
static uint64_t Handler = -1;

class Manager {
public:
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

