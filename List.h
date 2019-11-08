#ifndef List_H
#define List_H

#include<iostream>
using namespace std;


template<class T>
class List {
	struct Node
	{
		Node(T v, shared_ptr<Node> list) : _value(v), _next(list) {}
		~Node() {
			auto next_node = move(_next);
			while (next_node) {
				if (!next_node.unique())break;

				shared_ptr<Node> tail;
				swap(tail, next_node->_next);
				next_node.reset();

				next_node = move(_next);
			}
		}
		T _value;
		shared_ptr<Node> _next;
	};

private:
	shared_ptr<Node> _head;
public:
	List() : _head(nullptr) {}
	List(T v, List tail) : _head(new Node(v, tail._head)) {}
	explicit List(Node* items) : _head(items) {}
	bool isEmpty() const { return !_head; }
	//O(1) operations: 
	List<T> insertFront(T v){return *new List(v, *this);}//prepending
	List<T> removeFront() { if (!_head->_next) {return *new List();}return *new List(_head->_next.get()); }//removing the first element
	T front() const { return _head->_value; }//getting the first element
	//O(n) operations:
	List<T> insertEnd(T v) const;
	List<T> removeEnd() const;
	T getTail() const;
	List<T> InsertAt(int position, T v) const;
	List<T> RemoveAt(int position, T v) const;
};



template<class T>
 List<T> List<T>::insertEnd(T v) const
{	//set up the base case to be when reaching the end of the list
	 if (isEmpty()) { return *new List(v, *this);}
	 List<T> list = *new List(_head->_next.get());
	 return list.insertEnd(v).insertFront(_head->_value);
}

 template<class T>
List<T> List<T>::removeEnd() const
 {
	if (_head->_next == nullptr) {return *new List();}
	List<T> list = *new List(_head->_next.get());
	return list.removeEnd().insertFront(_head->_value);
 }



template<class T>
inline T List<T>::getTail() const
{
	if (!_head->_next) {return _head->_value;}
	List<T> list = *new List(_head->_next.get());
	return list.getTail();
}

template<class T>
inline List<T> List<T>::InsertAt(int position, T v) const
{
	if (position == 0) {return this->insertFront(v);}
	//return the new list
	List<T> list = *new List(_head->_next.get());
	return list.InsertAt(position - 1, v).insertFront(_head.get()._value);
}

template<class T>
inline List<T> List<T>::RemoveAt(int position, T v) const
{
	if (position == 0) {return this->removeFront(v);}
	List<T> list = *new List(_head->_next.get());
	return list.RemoveAt(position - 1, v).insertFront(_head.get()._value);
}


#endif//List_H


