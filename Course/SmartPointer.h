#pragma once
#include<iostream>
template<class T>
class SmartPointer
{
	T* _pointer;
public:
	SmartPointer();
	SmartPointer(T pointerData);
	SmartPointer(SmartPointer const& other);
	~SmartPointer();
	T* GetPointer();
	void SetPointer(T* pointer);
	SmartPointer<T>& operator=(SmartPointer<T> const& other);
	T& operator*();
};

template<class T>
SmartPointer<T>::SmartPointer()
{
	_pointer = new T();
}

template<class T>
inline SmartPointer<T>::SmartPointer(T pointerData)
{
	*_pointer = pointerData;
}

template<class T>
SmartPointer<T>::SmartPointer(SmartPointer const& other)
{
	*(other->_pointer) = *_pointer;
}

template<class T>
SmartPointer<T>::~SmartPointer()
{
	delete _pointer;
}

template<class T>
T* SmartPointer<T>::GetPointer()
{
	return _pointer;
}

template<class T>
void SmartPointer<T>::SetPointer(T* pointer)
{
	_pointer = pointer;
}

template<class T>
SmartPointer<T>& SmartPointer<T>:: operator=(SmartPointer<T> const& other)
{
	if (_pointer == nullptr)
		_pointer = new T();
	*_pointer = *(other._pointer);
	return *this;
}

template<typename T>
T& SmartPointer<T>::operator*()
{
	return *_pointer;
}
