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
	explicit List(Node const* items) : _head(items) {}
	bool isEmpty() const { return !_head; }
	//O(1) operations: 
	List<T> insertFront(T v) const{return new List(v, this); }//prepending
	List<T> removeFront() const { return new List(_head->_next); }//removing the first element
	T front() const { return _head->_value; }//getting the first element

	//O(n) operations:
	List<T>& insertEnd(T v) const;
	List<T>& removeEnd() const;






};

template<class T>
 List<T>& List<T>::insertEnd(T v) const
{	//set up the base case to be when reaching the end of the list
	 if (!this.isEmpty()) {
		 //insert the node to the new list
		 return new List()->insertFront(v);
	 }
	 //recursion call
	 List<T> list = _head->_next.insertEnd(v);
	 //when going backward, copy the list into the new list
	 list.insertFront(_head->_value);
	 //return the new list
	 return list;


}

 template<class T>
List<T>& List<T>::removeEnd() const
 {
	if (!this.isEmpty()) {
		//create a new empty list
		return new List();
	}
	//recursion call
	List<T> list = _head->_next.removeEnd(v);
	//when going backward, copy the list into the new list
	list.insertFront(_head->_value);
	//return the new list
	return list;
 }



#endif//List_H


