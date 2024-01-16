#pragma once


template<typename T>
class CRect {
public:
	T first;
	T second;
	T third;
	T fourth;
	CRect(T f, T s, T t, T fo);
	~CRect();
};


template<typename T>
inline CRect<T>::CRect(T f, T s, T t, T fo)
	: first(f), second(s), third(t), fourth(fo) {
}

template<typename T>
inline CRect<T>::~CRect() {
}