/*
 * Ensemble.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

//#include "Set.h"


template <class T>
Set<T>::Set ( int _size/*= 4*/)
{
	if ( _size < 0 )
		_size = 1;
	sz = _size;
	data = new T[sz];
	used = 0;
}

template <class T>
Set<T>::~Set()
{
	used = 0;
	delete[] data;
}

template <class T>
bool Set<T>::add ( T item ) // always added to the end
{
	if ( used >= sz )
	{
		size *= 2;
		T* temp = data;
		if ( !(data = new T[sz]) )
			return false;
		for ( int i = 0; i < used; ++i )
			data[i] = temp[i];
		delete[] temp;
	}
	data[used++] = item;
	return true;
}

template <class T>
bool Set<T>::truncate () // make size = used
{
	if ( used != sz )
	{
		T* temp = data;
		size = used;
		if ( !(data = new T[sz]))
			return false;
		for ( int i = 0; i < used; ++i )
			data[i] = temp[i];
		delete[] temp;
	}
	return true;
}

template <class T>
void Set<T>::clear ()
{
	used = 0;
}

template <class T>
int Set<T>::length ()
{
	return sz;
}

template <class T>
int Set<T>::size ()
{
	return sz;
}

template <class T>
bool Set<T>::empty ()
{
	return used == 0;
}

template <class T>
const T& Set<T>::operator[] (int i)
{
	/*if ( i < 0 || i >= used )
		return data[0];*/
	return data[i];
}

