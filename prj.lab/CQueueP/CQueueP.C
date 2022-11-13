#include<Manager/Manager.h>

ErrorCode CreateQueue(QueueHandler* queue)
{
	return Man.CreateQueueMan(queue);
}

ErrorCode CreateQueue(QueueHandler * queue)
{
	return Man.CreateQueueMan(queue);
}

ErrorCode CloneQueue(QueueHandler source, QueueHandler * queue)
{
	return Man.CloneQueueMan(source, queue);
}

ErrorCode DestroyQueue(QueueHandler queue)
{
	return Man.DestroyQueueMan(queue);
}

ErrorCode Pop(QueueHandler queue)
{
	return Man.PopMan(queue);
}

ErrorCode Push(QueueHandler queue, int32_t value)
{
	return Man.PushMan(queue, value);
}

ErrorCode IsEmpty(QueueHandler queue, int32_t * result)
{
	return Man.IsEmptyMan(queue, result);
}

ErrorCode Top(QueueHandler queue, int32_t * result)
{
	return Man.TopMan(queue, result);
}

const char* WhatIs(ErrorCode err);
