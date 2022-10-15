#include <QueueP/QueueP.h>
#include <algorithm>

QueueP::QueueP()
{
	this->head = nullptr;
}
bool QueueP::is_Empty() const
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
			Node* nxt = this->head->next.get();
			while (nxt->next!=nullptr && key>nxt->data)
			{
				std::swap(th, nxt);
				nxt = th->next.get();
			}
			Node* tmp = NEWEST.get();

			if (this->head.get() == th)
				{
				if (th->data <= key)
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
					NEWEST->next = std::move(head);
					this->head = std::move(NEWEST);
				}
			}
			else
			{
				if (nxt->next == nullptr)
				{
					if (nxt->data >= key)
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
						tmp->next = std::move(th->next);
						th->next = std::move(NEWEST);
				}
			}
		}
	}
	std::cout << *this << std::endl;
}

QueueP::QueueP(const QueueP& copy)
{
	if (copy.is_Empty()) return;
	head = std::make_unique<Node>(copy.head->data);

	Node* th = head.get();
	Node* _copy = copy.head->next.get();
	while (_copy != nullptr) {
		th->next = std::make_unique<Node>();
		th = th->next.get();
		th->data = _copy->data;
		_copy = _copy->next.get();
	}
	return;
}

QueueP& QueueP::operator=(const QueueP& rhs) 
{
	QueueP copy(rhs);
	std::swap(*this, copy);
	return *this;
}
void QueueP::pop()
{
	head = std::move(head->next);
}
int QueueP::top()
{
	return head->data;
}
std::ostream& operator<<(std::ostream& os, const QueueP& a)
{
	QueueP::Node* b = a.head.get();
	if (b != nullptr)
	{
		os << b->data<<" ";
		while (b->next != nullptr)
		{
			b = b->next.get();
			os << b->data<<" ";

		}
	}
	return os;
}
std::istream& operator>>(std::istream& istream, QueueP& temp)
{
	int data;
	while (istream>>data)
	{
		temp.push(data);
	}
	return istream;

}
