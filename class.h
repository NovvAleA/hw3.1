#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"


class element {
private:
	int i;
	int j;
	int value;
	element* next_e;
	element* prev_e;
	element* next_s;
	element* prev_s;
public:
	element();
	element& operator=(const element& other);
	element(const element& other);
	int get_j();
	void set_j(int c);
	int get_i();
	void set_i(int c);
	void set_next_e(element* p);
	void set_prev_e(element* p);
	element* get_next_e();
	element* get_prev_e();
	
	void set_value(int v);
	int get_value();
	void set_prev_s(element* p);
	void set_next_s(element* p);
	element* get_next_s();
	element* get_prev_s();
	element(element* p_prev, element* p_next, int t_i, int t_j);
	
	~element();
	friend int such_size_matrix(element* A, int* m, int* n);
};
int such_size_matrix(element* A, int* m, int* n);
