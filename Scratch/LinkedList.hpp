/*	libscratch - Multipurpose C++ core library.

		Copyright (c) 2013 - 2016 Angelo Geels <spansjh@gmail.com>

		Permission is hereby granted, free of charge, to any person
		obtaining a copy of this software and associated documentation
		files (the "Software"), to deal in the Software without
		restriction, including without limitation the rights to use,
		copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the
		Software is furnished to do so, subject to the following
		conditions:

		The above copyright notice and this permission notice shall be
		included in all copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
		EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
		OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
		NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
		HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
		WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
		FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
		OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

SCRATCH_NAMESPACE_BEGIN;

template<typename T>
class LinkedList
{
private:
	T* m_head;
	T* m_tail;

public:
	LinkedList();
	~LinkedList();

	T* Head();
	T* Tail();

	T &Add();
	void Add(T* ptr);

	void Unlink(T &obj);
	void Unlink(T* ptr);
};

template<typename T>
class LinkedListNode
{
friend LinkedList<T>;

protected:
	LinkedList<T>* m_listBase;
	T* m_listNext;
	T* m_listPrev;
	bool m_listManaged;

public:
	LinkedListNode();
	virtual ~LinkedListNode();

	inline T* ListNext() { return m_listNext; }
	inline T* ListPrev() { return m_listPrev; }
};

template<typename T>
LinkedList<T>::LinkedList()
{
	m_head = nullptr;
	m_tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	T* node = m_head;
	while (node != nullptr) {
		T* next = node->ListNext();
		if (node->m_listManaged) {
			delete (T*)node;
		}
		node = next;
	}
}

template<typename T>
T* LinkedList<T>::Head()
{
	return m_head;
}

template<typename T>
T* LinkedList<T>::Tail()
{
	return m_tail;
}

template<typename T>
T &LinkedList<T>::Add()
{
	T* ptr = new T;
	ptr->m_listManaged = true;
	Add(ptr);
	return *ptr;
}

template<typename T>
void LinkedList<T>::Add(T* ptr)
{
	ptr->m_listBase = this;
	ptr->m_listPrev = m_tail;
	if (m_head == nullptr) {
		m_head = ptr;
	}
	if (m_tail != nullptr) {
		m_tail->m_listNext = ptr;
	}
	m_tail = ptr;
}

template<typename T>
void LinkedList<T>::Unlink(T &obj)
{
	Unlink(&obj);
	if (obj.m_listManaged) {
		delete &obj;
	}
}

template<typename T>
void LinkedList<T>::Unlink(T* ptr)
{
	if (ptr->m_listPrev != nullptr) {
		ptr->m_listPrev->m_listNext = ptr->m_listNext;
	}
	if (ptr->m_listNext != nullptr) {
		ptr->m_listNext->m_listPrev = ptr->m_listPrev;
	}
	if (ptr == m_tail) {
		m_tail = ptr->m_listPrev;
	}
	if (ptr == m_head) {
		m_head = ptr->m_listNext;
	}
	ptr->m_listPrev = nullptr;
	ptr->m_listNext = nullptr;
}

template<typename T>
LinkedListNode<T>::LinkedListNode()
{
	m_listBase = nullptr;
	m_listNext = nullptr;
	m_listPrev = nullptr;
	m_listManaged = false;
}

template<typename T>
LinkedListNode<T>::~LinkedListNode()
{
	if (m_listBase == nullptr) {
		return;
	}
	if (m_listNext != nullptr || m_listPrev != nullptr) {
		m_listBase->Unlink((T*)this);
	}
}

SCRATCH_NAMESPACE_END;
