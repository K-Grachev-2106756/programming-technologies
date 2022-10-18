#include <Manager/Manager.h>

//ErrorCode Manager::CreateQueueMan(QueueHandler* queue)
//{
//
//}
//ErrorCode Manager::CloneQueueMan(QueueHandler source, QueueHandler* queue)
//{
//
//}
//ErrorCode Manager::DestroyQueueMan(QueueHandler queue)
//{
//
//}
//ErrorCode Manager::PopMan(QueueHandler queue)
//{
//
//}
//ErrorCode Manager::PushMan(QueueHandler queue, int32_t value)
//{
//
//}
//ErrorCode Manager::IsEmptyMan(QueueHandler queue, int32_t* result)
//{
//
//}
//ErrorCode Manager::TopMan(QueueHandler queue, int32_t* result)
//{
//
//}


extern "C" ErrorCode CreateQueueC(QueueHandler * queue);
extern "C" ErrorCode CreateQueueC(QueueHandler* queue);
extern "C" ErrorCode CloneQueueC(QueueHandler source, QueueHandler* queue);
extern "C" ErrorCode DestroyQueueC(QueueHandler queue);
extern "C" ErrorCode PopC(QueueHandler queue);
extern "C" ErrorCode PushC(QueueHandler queue, int32_t value);
extern "C" ErrorCode IsEmptyC(QueueHandler queue, int32_t* result);
extern "C" ErrorCode TopC(QueueHandler queue, int32_t* result);