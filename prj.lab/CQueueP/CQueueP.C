#include<Manager/Manager.h>

ErrorCode CreateQueueC(QueueHandler* queue);
ErrorCode CloneQueueC(QueueHandler source, QueueHandler* queue);
ErrorCode DestroyQueueC(QueueHandler queue);
ErrorCode PopC(QueueHandler queue);
ErrorCode PushC(QueueHandler queue, int32_t value);
ErrorCode IsEmptyC(QueueHandler queue, int32_t* result);
ErrorCode TopC(QueueHandler queue, int32_t* result);

//ErrorCode CreateQueue(QueueHandler* queue)
//{
//
//}
//
//ErrorCode CloneQueue(QueueHandler source, QueueHandler* queue)
//{
//
//}
//
//ErrorCode DestroyQueue(QueueHandler queue)
//{
//
//}
//
//ErrorCode Pop(QueueHandler queue)
//{
//
//}
//
//ErrorCode Push(QueueHandler queue, int32_t value)
//{
//
//}
//
//ErrorCode IsEmpty(QueueHandler queue, int32_t* result)
//{
//
//}
//
//ErrorCode Top(QueueHandler queue, int32_t* result)
//{
//
//}