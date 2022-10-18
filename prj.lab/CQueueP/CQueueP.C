#include<CQueueP/CQueueP.h>
#include<Manager/Manager.h>
int CreateQueueC(QueueHandler * queue);
int CreateQueueC(QueueHandler * queue);
int CloneQueueC(QueueHandler source, QueueHandler * queue);
int DestroyQueueC(QueueHandler queue);
int PopC(QueueHandler queue);
int PushC(QueueHandler queue, int32_t value);
int IsEmptyC(QueueHandler queue, int32_t * result);
int TopC(QueueHandler queue, int32_t * result);

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