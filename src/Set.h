/*
 * Ensemble.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef SET_H_
#define SET_H_

template <class T>
class Set
{
protected:
	int sz;
	T* data;
	int used;
public:
	Set ( int _size= 4 );
	virtual ~Set();

	bool add ( T item ); // always added to the end
	bool truncate (); // make size = used
	void clear ();
	int length ();
	int size ();
	bool empty ();
	const T& operator[] (int i);

};

#endif /* SET_H_ */
