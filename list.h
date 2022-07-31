#pragma once


template <typename T>
class List
{
public:
	List() :head{} {}
	List(const List&);
	List(List&&);
	List(std::initializer_list<T>);
	List& operator=(const List&);
	List& operator=(List&&);
	~List();
public:
	void push(const T&);
	void insert_after(size_t, const T&);
	void push_front(const T&);
	void pop_front();
	void erase_after(size_t);
	void swap(List&);
	void resize(size_t);
	void printList();
	bool empty() const noexcept;
	void clear();
public:
	void splice_after(T,List&);
	void reverse() noexcept;
	void sort();
	void merge(List&);
	void merge(List&&);
	void unique();
	void remove(const T&);
private:
	struct Node
	{
	public:
		Node() :val{}, next{} {}
		Node(T t) :next{}, val(t){}
		T val;
		Node* next;
	};
private:
	Node* head;
};

#include "list.hpp"