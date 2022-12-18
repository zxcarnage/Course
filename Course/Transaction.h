#pragma once
#include<iostream>
#include"SmartPointer.h"
using namespace std;

template<typename T>
class Transaction
{
	SmartPointer<T> _previousState;
	SmartPointer<T> _currentState;

public:
	Transaction();
	Transaction(Transaction<T>& other);

	Transaction<T>& operator=(Transaction const& other);
	T* operator->();

	void Write();
	void Show();
	bool Begin(T newState);
	void Commit();
	bool Undo();

	T* GetObj();
	void SetPreviousState(SmartPointer<T>* data);
	void SetCurrentState(SmartPointer<T>* data);
};

template<typename T>
inline Transaction<T>::Transaction()
{
	_previousState = SmartPointer<T>();
	_currentState = SmartPointer<T>();
}

template<typename T>
Transaction<T>::Transaction(Transaction<T>& other)
{
	*(other._previousState) = *_previousState;
	*(other._currentState) = *_currentState;
}

template<typename T>
inline T* Transaction<T>::operator->()
{
	return _currentState.GetPointer();
}

template<typename T>
T* Transaction<T>::GetObj()
{
	return _currentState.GetPointer();
}


template<typename T>
Transaction<T>& Transaction<T>:: operator=(Transaction<T> const& other)
{
	*(other._previousState) = *_previousState;
	*(other._currentState) = *_currentState;
	return this;
}

template<typename T>
void Transaction<T>::Write()
{
	(*_previousState).WriteInfo("Previous State");
	(*_currentState).WriteInfo("Current State");
}

template<typename T>
void Transaction<T>::Show()
{
	if (_previousState.GetPointer())
	{
		cout << "Previous state: " << endl;
		(*_previousState).Show();
	}
	else
		cout << "Have no previous state" << endl;
	cout << endl;
	cout << "Current state :" << endl;
	(*_currentState).Show();
	cout << endl;
}


template<typename T>
bool Transaction<T>::Begin(T newState)
{
	_previousState = _currentState;
	*_currentState.GetPointer() = newState;
	if (_currentState.GetPointer() == nullptr)
		return false;
	return true;
}

template<typename T>
void Transaction<T>::Commit()
{
	_previousState.SetPointer(nullptr);
}

template<typename T>
bool Transaction<T>::Undo()
{
	if (_previousState.GetPointer() == nullptr)
		return false;
	_currentState = _previousState;
	_previousState.SetPointer(nullptr);
	return true;
}

template<typename T>
void Transaction<T>::SetPreviousState(SmartPointer<T>* previousState)
{
	*_previousState = *previousState;
}

template<typename T>
void Transaction<T>::SetCurrentState(SmartPointer<T>* currentState)
{
	*_currentState = *currentState;
}
