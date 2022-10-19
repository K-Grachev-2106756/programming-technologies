#include <Manager/Manager.h>

ErrorCode Manager::CreateQueueMan(QueueHandler* queue)
{
	//try
	//{
	//	std::shared_ptr<QueueP> ptr = std::make_shared<QueueP>();
	//	queue = (uint64_t*)ptr.get();
	//	return ErrorCode::kGood;
	//	//как сделать так чтобы в мы могли изменить указатель в функции, а еще что не так с cdecl. ”ничтожаетс€ ли экзепл€р, который € здесь создаю и что делать, чтобы он осталс€? 
	//}
	//catch (const std::exception&)
	//{
	//	return ErrorCode::kHandlerError;
	//}
	if (*queue != EmptyHandler)
	{
		return ErrorCode::kHandlerError;
	}
	else
	{

		Handle+=1;
		*queue = Handle;
		MainData[Handle] = QueueP();
		return ErrorCode::kGood;
	}
}
ErrorCode CloneQueueMan(QueueHandler source, QueueHandler* queue)
{
	

}
//ErrorCode DestroyQueueMan(QueueHandler queue);
//ErrorCode PopMan(QueueHandler queue);
//ErrorCode PushMan(QueueHandler queue, int32_t value);
//ErrorCode IsEmptyMan(QueueHandler queue, int32_t* result);
//ErrorCode TopMan(QueueHandler queue, int32_t* result);


extern "C" ErrorCode CreateQueueC(QueueHandler * queue);
extern "C" ErrorCode CreateQueueC(QueueHandler* queue);
extern "C" ErrorCode CloneQueueC(QueueHandler source, QueueHandler* queue);
extern "C" ErrorCode DestroyQueueC(QueueHandler queue);
extern "C" ErrorCode PopC(QueueHandler queue);
extern "C" ErrorCode PushC(QueueHandler queue, int32_t value);
extern "C" ErrorCode IsEmptyC(QueueHandler queue, int32_t* result);
extern "C" ErrorCode TopC(QueueHandler queue, int32_t* result);