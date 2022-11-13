#include <Manager/Manager.h>

extern "C" ErrorCode Manager::CreateQueueMan(QueueHandler* queue){
	if (*queue != EmptyHandler) return ErrorCode::kHandlerError;
	*queue = Handle;
	this->MainData[Handle] = QueueP(); 
	Handle += 1;
	return ErrorCode::kGood;
}

extern "C" ErrorCode Manager::CloneQueueMan(QueueHandler source, QueueHandler* queue){
	if(this->MainData.find(source) == this->MainData.end() || *queue != EmptyHandler) return ErrorCode::kHandlerError;
	*queue = Handle;
	this->MainData[Handle] = QueueP(this->MainData[source]);
	Handle += 1;
	return ErrorCode::kGood;
}

extern "C" ErrorCode Manager::DestroyQueueMan(QueueHandler queue){
	if (this->MainData.find(queue) == this->MainData.end()) return ErrorCode::kHandlerError;
	this->MainData.erase(queue);
	return ErrorCode::kGood;
}

extern "C" ErrorCode Manager::PopMan(QueueHandler queue){
	if (this->MainData.find(queue) == this->MainData.end()) return ErrorCode::kHandlerError;
	if (this->MainData[queue].is_Empty()) return ErrorCode::kOutOfRange;
	this->MainData[queue].pop();
	return ErrorCode::kGood;
}

extern "C" ErrorCode Manager::PushMan(QueueHandler queue, int32_t value){
	if (this->MainData.find(queue) == this->MainData.end()) return ErrorCode::kHandlerError;
	this->MainData[queue].push(value);
	return ErrorCode::kGood;
}

extern "C" ErrorCode Manager::IsEmptyMan(QueueHandler queue, int32_t* result){
	if (this->MainData.find(queue) == this->MainData.end()) return ErrorCode::kHandlerError;
	*result = this->MainData[queue].is_Empty();
	return ErrorCode::kGood;
}

extern "C" ErrorCode Manager::TopMan(QueueHandler queue, int32_t* result){
	if (this->MainData.find(queue) == this->MainData.end()) return ErrorCode::kHandlerError;
	if (this->MainData[queue].is_Empty()) return ErrorCode::kOutOfRange;
	*result = this->MainData[queue].top();
	return ErrorCode::kGood;
}


//extern "C" ErrorCode CreateQueueC(QueueHandler* queue)
//{
//	return Man.CreateQueueMan(queue);
//}
//extern "C" ErrorCode CloneQueueC(QueueHandler source, QueueHandler* queue)
//{
//	return Man.CloneQueueMan(source, queue);
//}
//extern "C" ErrorCode DestroyQueueC(QueueHandler queue)
//{
//	return Man.DestroyQueueMan(queue);
//}
//extern "C" ErrorCode PopC(QueueHandler queue)
//{
//	return Man.PopMan(queue);
//}
//extern "C" ErrorCode PushC(QueueHandler queue, int32_t value)
//{
//	return Man.PushMan(queue, value);
//}
//extern "C" ErrorCode IsEmptyC(QueueHandler queue, int32_t* result)
//{
//	return Man.IsEmptyMan(queue, result);
//}
//extern "C" ErrorCode TopC(QueueHandler queue, int32_t* result)
//{
//	return Man.TopMan(queue, result);
//}