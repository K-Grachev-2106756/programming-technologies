#include <Manager/Manager.h>

int Manager::CreateQueueMan(QueueHandler* queue)
{
	try
	{
		std::shared_ptr<QueueP> ptr = std::make_shared<QueueP>();
		queue = (uint64_t*)ptr.get();
		return 0;
		//как сделать так чтобы в мы могли изменить указатель в функции, а еще что не так с cdecl. ”ничтожаетс€ ли экзепл€р, который € здесь создаю и что делать, чтобы он осталс€? 
	}
	catch (const std::exception&)
	{
		return 1;
	}
}
//int Manager::CloneQueueMan(QueueHandler source, QueueHandler* queue)
//{
//	/*QueueP tmp = *((QueueP*)queue);
//	uint64_t b;
//	QueueP f;
//	b = (uint64_t)&f; 
//
//	QueueP L = *(QueueP*)b;*/
//
//	try
//	{
//		*((QueueP*)queue) = *((QueueP*)source);
//		return 0;
//	}
//	catch (const std::exception&)
//	{
//		return 1;
//	}
//}
//int Manager::DestroyQueueMan(QueueHandler queue)
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


extern "C" int CreateQueueC(QueueHandler * queue);
extern "C" int CreateQueueC(QueueHandler* queue);
extern "C" int CloneQueueC(QueueHandler source, QueueHandler* queue);
extern "C" int DestroyQueueC(QueueHandler queue);
extern "C" int PopC(QueueHandler queue);
extern "C" int PushC(QueueHandler queue, int32_t value);
extern "C" int IsEmptyC(QueueHandler queue, int32_t* result);
extern "C" int TopC(QueueHandler queue, int32_t* result);