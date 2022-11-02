#include <Manager/Manager.h>

ErrorCode Manager::CreateQueueMan(QueueHandler* queue)
{
	if (*queue != EmptyHandler)
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		*queue = Handle;
		this->MainData[Handle] = QueueP(); 
		Handle += 1;
		//как в строку карты засунуть экземпл€р класса (без ссылки на экземпл€р выводит ошибку линковщика "неразрешенный внешний символ")
		return ErrorCode::kGood;
	}
}

ErrorCode Manager::CloneQueueMan(QueueHandler source, QueueHandler* queue)
{
	if (*queue != EmptyHandler)
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		*queue = Handle;
		//this->MainData[Handle] = QueueP(this->MainData[source]); //дл€ того чтобы работало нужно сделать нормально CreateQueueMan :)
		Handle += 1;
		return ErrorCode::kGood;
	}
}

ErrorCode Manager::DestroyQueueMan(QueueHandler queue)
{
	if (this->MainData.find(queue) == this->MainData.end())
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		this->MainData.erase(this->MainData.find(queue));
		return ErrorCode::kGood;
	}
}

ErrorCode Manager::PopMan(QueueHandler queue)
{
	if (this->MainData.find(queue) == this->MainData.end())
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		this->MainData[queue].pop();
		return ErrorCode::kGood;
	}
}

ErrorCode Manager::PushMan(QueueHandler queue, int32_t value)
{
	if (this->MainData.find(queue) == this->MainData.end())
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		this->MainData[queue].push(value);
		return ErrorCode::kGood;
	}
}

ErrorCode Manager::IsEmptyMan(QueueHandler queue, int32_t* result)
{
	if (this->MainData.find(queue) == this->MainData.end())
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		*result = this->MainData[queue].is_Empty();
		return ErrorCode::kGood;
	}
}

ErrorCode Manager::TopMan(QueueHandler queue, int32_t* result)
{
	if (this->MainData.find(queue) == this->MainData.end())
	{
		return ErrorCode::kHandlerError;
	}
	else
	{
		*result = this->MainData[queue].top();
		return ErrorCode::kGood;
	}
}

//Manager::~Manager()
//{
//	while (!MainData.empty())
//	{
//		//el.second.~QueueP(); //не будет ли умирать таблица, если будет хранить недействительные удалЄнные данные? 
//		this->DestroyQueueMan(MainData.begin()->first);
//	}
//}

extern "C" ErrorCode CreateQueueC(QueueHandler* queue)
{
	return Man.CreateQueueMan(queue);
}
extern "C" ErrorCode CloneQueueC(QueueHandler source, QueueHandler* queue)
{
	return Man.CloneQueueMan(source, queue);
}
extern "C" ErrorCode DestroyQueueC(QueueHandler queue)
{
	return Man.DestroyQueueMan(queue);
}
extern "C" ErrorCode PopC(QueueHandler queue)
{
	return Man.PopMan(queue);
}
extern "C" ErrorCode PushC(QueueHandler queue, int32_t value)
{
	return Man.PushMan(queue, value);
}
extern "C" ErrorCode IsEmptyC(QueueHandler queue, int32_t* result)
{
	return Man.IsEmptyMan(queue, result);
}
extern "C" ErrorCode TopC(QueueHandler queue, int32_t* result)
{
	return Man.TopMan(queue, result);
}