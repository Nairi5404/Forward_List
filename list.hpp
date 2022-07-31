#pragma once

template <typename T>
List<T>::List(const List<T>& ob)
{
	if (ob.head == nullptr) {
		head = nullptr;
	}
	else
	{
		head = new Node(ob.head->val);
		Node* tmp1 = head;
		Node* tmp2 = ob.head->next;
		while (tmp2 != nullptr)
		{
			tmp1->next = new Node(tmp2->val);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}
}

template <typename T>
List<T>::List(List&& ob)
{
	head = ob.head;
	ob.head = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rgs)
{
	if (this == &rgs) {
		return *this;
	}
	if (rgs.head != nullptr)
	{
		clear();
		head = new Node(rgs.head->val);
		Node* tmp1 = head;
		Node* tmp2 = rgs.head->next;
		while (tmp2 != nullptr)
		{
			tmp1->next = new Node(tmp2->val);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		tmp1->next = nullptr;
	}
	else {
		clear();
	}
	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& rgs)
{
	clear();
	head = rgs.head;
	rgs.head = nullptr;
	return *this;
}

template <typename T>
List<T>::List(std::initializer_list<T> ob)
{
	for (auto it = ob.begin(); it != ob.end();++it)
	{
		push(*it);
	} 
}

template <typename T>
void List<T>::push(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		return;
	}
	auto curr = head;
	while (curr->next != nullptr)
	{
		curr = curr->next;
	}
	curr->next = new Node(value);
}

template <typename T>
List<T>::~List()
{
	clear();
}

template <typename T>
void List<T>::insert_after(size_t pos, const T& value)
{
	auto curr = head;
	int index = 1;
	if (index == pos)
	{
		push_front(value);
		return;
	}
	while (curr->next != nullptr)
	{
		++index;
		if (index == pos)
		{
			curr = curr->next;
			Node* tmp = curr->next;
			curr->next = new Node(value);
			curr->next->next = tmp;
		}
		else {
			curr = curr->next;
		}
	}
}

template <typename T>
void List<T>::push_front(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		return;
	}
	else
	{
		Node* tmp = new Node(value);
		tmp->next = head;
		head = tmp;
	}
}

template <typename T>
void List<T>::pop_front()
{
	if (head != nullptr)
	{
		if (head->next != nullptr)
		{
			Node* tmp = head->next;
			delete head;
			head = tmp;
		}
		else
		{
			delete head;
			head = nullptr;
		}
	}
	else {
		return;
	}
}

template <typename T>
void List<T>::erase_after(size_t pos)
{
	auto curr = head;
	int index = 1;
	if (index == pos) {
		pop_front();
		return;
	}
	while (curr->next != nullptr)
	{
		++index;
		if (index == pos)
		{
			Node* tmp = curr->next->next;
			delete curr->next;
			curr->next = tmp;
		}
		else {
			curr = curr->next;
		}
	}
}

template <typename T>
void List<T>::printList() 
{
	for (Node* curr = head; curr != nullptr; curr = curr->next)
	{
		std::cout << curr->val << "  ";
	}
	std::cout << std::endl;
}

template<typename T>
bool List<T>::empty() const noexcept
{
	return (head == nullptr) ? true : false;
}

template <typename T>
void List<T>::clear()
{
	if (!empty())
	{
		Node* tmp = head->next;
		while (tmp != nullptr)
		{
			delete head;
			head = tmp;
			tmp = tmp->next;
		}
		head = nullptr;
	}
}

template <typename T>
void List<T>::resize(size_t quantity)
{
	int size = 0;
	auto curr = head;
	if (curr == nullptr)
	{
		curr = new Node;
		head = curr;
		++size;
	}
	while (curr->next != nullptr) 
	{
		curr = curr->next;
		++size;
	}
	
	while (size < quantity)
	{
		curr->next = new Node;
		curr = curr->next;
		++size;
	}
}

template <typename T>
void List<T>::swap(List& obj)
{
	Node* tmp = head;
	head = obj.head;
	obj.head = tmp;
}

template <typename T>
void List<T>::splice_after(T pos,List& ob)
{
	if (this != &ob && ob.head != nullptr)
	{
		Node* tmp1 = head;
		Node* tmp2 = ob.head;
		Node* prev{};
		Node* Next{};
		int size = 1;
		while (tmp2 != nullptr)
		{
			tmp2 = tmp2->next;
			++size;
			if (size == pos)
			{
				Node* temp = tmp2;

				while (tmp1 != nullptr)
				{
					if (tmp1->next == nullptr)
					{
						tmp1->next = tmp2->next;
						break;
					}
					tmp1 = tmp1->next;
				}

				while (tmp1 == nullptr)
				{
					head = tmp2->next;
					break;
				}

				while (tmp2->next != nullptr)
				{
					Next = tmp2->next;
					tmp2->next = prev;
					prev = tmp2;
					if (tmp2->next == nullptr)
					{
						while (temp != tmp2)
						{
							tmp2 = tmp2->next;
							delete tmp2;
						}
						break;
					}
					tmp2 = Next;
				}
			}
		}
	}
}

template <typename T>
void List<T>::reverse() noexcept
{
	if (head != nullptr)
	{
		Node* curr = head;
		Node* prev{};
		Node* Next{};
		while (curr != nullptr)
		{
			Next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = Next;
		}
		head = prev;
	}
}

template <typename T>
void List<T>::sort()
{
	if (head != nullptr)
	{
		Node* temp = head;
		while (temp != nullptr) 
		{
			Node* min = temp;
			Node* Next = temp->next;

			while (Next != nullptr)
			{
				if (min->val > Next->val) {
					min = Next;
				}
				Next = Next->next;
			}
			T value = temp->val;
			temp->val = min->val;
			min->val = value;
			temp = temp->next;
		}
	}
}

template <typename T>
void List<T>::merge(List& obj)
{
	if (this != &obj && obj.head != nullptr)
	{
		auto curr1 = head;
		auto curr2 = obj.head;
		while (curr1 != nullptr)
		{
			if (curr1->next == nullptr)
			{
				curr1->next = obj.head;
				obj.head = nullptr;
				break;
			}
			curr1 = curr1->next;
		}

		if (curr1 == nullptr)
		{
			head = obj.head;
			obj.head = nullptr;
		}

		while (curr1->next != nullptr)
		{
			curr1 = curr1->next;
			if (curr1->next == nullptr)
			{
				curr1->next = obj.head;
				obj.head = nullptr;
			}
		}
		sort();
	}
}

template <typename T>
void List<T>::merge(List&& obj) {
	merge(obj);
}

template <typename T>
void List<T>::unique()
{
	if (head != nullptr)
	{
		auto curr = head;
		while (curr != nullptr)
		{
			Node* tmp = curr->next->next;
			if (curr->val == curr->next->val)
			{
				delete curr->next;
				curr->next = tmp;
			}
			curr = curr->next;
		}
	}
}

template <typename T>
void List<T>::remove(const T& value)
{
	if (head != nullptr)
	{
		auto curr = head;
		while (curr != nullptr)
		{
			if (curr->val == value)
			{
				if (curr->next != nullptr)
				{
					Node* tmp = curr->next;
					delete curr;
					head = tmp;
				}
				else {
					delete curr;
					head = nullptr;
				}
			}
			else {
				break;
			}
			curr = head;
		}
		
		Node* prev{};
		while (curr != nullptr)
		{
			if (curr->val == value)
			{
				if (curr->next != nullptr)
				{
					Node* tmp = curr->next;
					delete curr;
					prev->next = tmp;
					curr = prev->next;
				}
				else 
				{
					delete curr;
					prev->next = nullptr;
					curr = nullptr;
					break;
				}
			}
			else 
			{
				prev = curr;
				curr = curr->next;
			}
		}
	}
}

