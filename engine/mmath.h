#pragma once
#include <cmath>

#ifndef MMATH_STD
#define MMATH_STD
#endif // !MMATH_STD

//////////////////////////////////////////////////////////
//	Murena2D Standart maths header
//	Developed by Einhorn32
//	2018
//
//	Module One
//////////////////////////////////////////////////////////

struct _vector2d {
	long double x;
	long double y;
};
typedef _vector2d vector2d;

struct _complexvector2d {
	long double r;
	long double i;
};
typedef _complexvector2d complexvector2d;

// Ortogonal computings: Logic
template <class Tx, class Ty>
long double __fastcall mmax(Tx, Ty) {
	return(Tx > Ty ? Tx : Ty);
}
template <class Tx, class Ty>
long double __fastcall mmin(Tx, Ty) {
	return(Tx < Ty ? Tx : Ty);
}

// Ortogonal computing: Trigonometry
template <class Tx, class Ty>
long double __fastcall side_fromsin(Tx, Ty) {
	// Tx is sinus and Ty is opposite side for corner alpha
	// function returns a opposite side of corner
	return sin(Tx) * Ty;
}
template <class Tx, class Ty>
long double __fastcall sin_fromside(Tx, Ty) {
	// Tx is opposite side for corner alpha and Ty is diagonal side of triangle
	// function returns a proportional equality of sin(alpha)
	return(Tx / Ty);
}

template <class Tx, class Ty>
long double __fastcall side_fromcos(Tx, Ty) {
	// Tx is cosinus and Ty is adjacent side for corner alpha
	// function returns a adjacent side of corner
	return cos(Tx) * Ty;
}
template <class Tx, class Ty>
long double __fastcall cos_fromside(Tx, Ty) {
	// Tx is adjacent side for corner alpha and Ty is diagonal side of triangle
	// function returns a proportional equality of cos(alpha)
	return(Tx / Ty);
}

template <class Tx, class Ty>
long double __fastcall side_fromtan(Tx, Ty) {
	// Tx is tangens and Ty is opposite side for corner alpha
	// function returns an adjacent side for corner
	return tan(Tx) * Ty;
}
template <class Tx, class Ty>
long double __fastcall tan_fromside(Tx, Ty) {
	// Tx is opposite side for corner alpha and Ty is adjacent side of corner
	// function returns a proportional equality of tan(alpha)
	return(Tx/Ty);
}

template <class Tx, class Ty>
long double __fastcall side_fromctan(Tx, Ty) {
	// Tx is cotangens and Ty is adjacent side for corner alpha
	// function returns an opposite side for corner
	return ctan(Tx) * Ty;
}
template <class Tx, class Ty>
long double __fastcall ctan_fromside(Tx, Ty) {
	// Tx is adjacent side for corner alpha and Ty is opposite side of corner
	// function returns a proportional equality of tan(alpha)
	return(Tx / Ty);
}

// Ortogonal computing: Vectors
vector2d __fastcall add(vector2d Vx, vector2d Vy) {
	vector2d out;
	out.x = Vx.x + Vy.x;
	out.y = Vx.y + Vy.y;
	return out;
}

complexvector2d __fastcall add(complexvector2d Vx, complexvector2d Vy) {
	complexvector2d out;
	out.r = Vx.r + Vy.r;
	out.i = Vx.i + Vy.i;
	return out;
}

#undef MMATH_STD
