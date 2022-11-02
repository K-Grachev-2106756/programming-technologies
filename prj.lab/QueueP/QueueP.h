#include <iostream>
class QueueP
{
public:
	class Node
	{
	public:
		int data;
		std::unique_ptr<Node> next;
		Node(int value = 0, std::unique_ptr<Node> next_ = nullptr)
		{
			this->data = value;
			this->next = std::move(next_);
		}
		~Node() = default;
	};

	std::unique_ptr<Node> head;
	QueueP();
	bool is_Empty() const;
	void push(int key);
	void pop();
	int top();
	QueueP(const QueueP& copy);
	QueueP& operator=(const QueueP& rhs);
	~QueueP();
};
std::ostream& operator<<(std::ostream& os, const QueueP& a);
std::istream& operator>>(std::istream& istream, QueueP& temp);