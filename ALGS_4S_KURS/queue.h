#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
private:
	class Node
	{
	public:
		Node(T data)
		{
			this->data = data;
			this->prev = nullptr;
		}

		T data;

		Node* prev;
	};

	Node* head;

	Node* last;

public:
	Queue()
	{
		head = nullptr;
		last = nullptr;
	}

	~Queue()
	{
		while (!empty())
		{
			pop();
		}
	}

	void pop()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty!");
		}
		else
		{
			Node* temp = head;
			head = head->prev;
			delete temp;
		}
	}

	void push(T data)
	{
		Node* newNode = new Node(data);
		if (empty())
		{
			head = newNode;
			last = newNode;
		}
		else
		{
			last->prev = newNode;
			last = newNode;
		}
	}

	bool empty()
	{
		return head == nullptr;
	}

	T front()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty");
		}
		else
		{
			return head->data;
		}
	}

	T back()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty");
		}
		else
		{
			return last->data;
		}
	}
};

#endif
