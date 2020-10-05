#ifndef POINT_H
#define POINT_H
#include<iostream>

// Points on 2d grid
class Point {
	friend std::ostream & operator<<(std::ostream &os, const Point& p);
	friend Point operator+ (const Point &lhs, const Point &rhs);
	friend Point operator- (const Point &lhs, const Point &rhs);
	friend double sqrDist(const Point &p1, const Point &p2);

public:
	Point();

	Point(int x, int y);
	
	int getX() const;
	int getY() const;
	void set(int x, int y);

	// overloaded comparison operator, two points are equal
	// if both their elements are equal
	bool operator==(const Point &other);
	bool operator==(const Point &other) const;
	bool operator!=(const Point &other);
	bool operator!=(const Point &other) const;
private:
	int m_x, m_y;
};

#endif//POINT_H
