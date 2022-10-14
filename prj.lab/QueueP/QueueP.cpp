#include <QueueP/QueueP.h>
//#include <vector>
//#include <string>
QueueP::QueueP()
{
	this->head = nullptr;
}
bool QueueP::is_Empty()
{
	return (this->head == nullptr);
}
void QueueP::push(int key)
{
	if (this->is_Empty())
	{
		this->head = std::make_unique<Node>(key);
	}
	else
	{
		std::unique_ptr<Node> NEWEST = std::make_unique<Node>(key);
		if (this->head->next == nullptr)
		{
			if (this->head->data > key)
			{
				NEWEST->next = std::move(head);
				this->head = std::move(NEWEST);
			}
			else
			{
				this->head->next = std::move(NEWEST);
			}
		}
		else
		{
			Node* th = this->head.get();
			Node* nxt = this->head.get();
			while (nxt->next!=nullptr && th->data < key)
			{
				std::swap(th, nxt);
				nxt = th->next.get();
			}
			Node* tmp = NEWEST.get();

			if (nxt->next==nullptr)
			{
				if (nxt->data>=key)
				{
					tmp->next = std::move(th->next);
					th->next = std::move(NEWEST);
				}
				else
				{
					nxt->next = std::move(NEWEST);
				}
			}
			else
			{
				if (this->head.get() == th)
				{
					NEWEST->next = std::move(head);
					this->head = std::move(NEWEST);
				}
				else
				{
					tmp->next = std::move(th->next);
					th->next = std::move(NEWEST);
				}
				

			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const QueueP& a)
{
	QueueP::Node* b = a.head.get();
	if (b != nullptr)
	{
		os << b->data;
		while (b->next != nullptr)
		{
			b = b->next.get();
			os << b->data;
			
		}
	}
	return os;
}

//std::istream& operator>>(std::istream& istream, QueueP& temp)
//{
//	std::string c;
//	istream >> c;
//	std::vector<int> a = std::vector<int>(c);
//	//int c;
//	//while (istream>>c)
//	//{
//	//	temp.push(c);
//	//}
//}
void QueueP::pop()
{
	head = std::move(head->next);
}
int QueueP::top()
{
	return head->data;
}