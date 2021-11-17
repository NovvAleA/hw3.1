#include "class.h"

element::element(const element& other) {
	i = other.i;
	j = other.j;
	value = other.value;
	next_e = other.next_e;
	prev_e = other.prev_e;
	next_s = other.next_s;
	prev_s = other.prev_s;
}
element& element::operator=(const element& other) {
	i = other.i;
	j = other.j;
	value = other.value;
	next_e = other.next_e;
	prev_e = other.prev_e;
	next_s = other.next_s;
	prev_s = other.prev_s;
	return *this;
}
int element::get_j() {
	return j;
}
void element::set_j(int c) {
	j = c;
}
int element::get_i() {
	return i;
}
void element::set_i(int c) {
	i = c;
}
void element::set_next_e(element* p) {
	next_e = p;
}
void element::set_prev_e(element* p) {
	prev_e = p;
}
element* element::get_next_e() {
	return next_e;
}
element* element::get_prev_e() {
	return prev_e;
}
void element::set_value(int v) {
	value = v;
}
int element::get_value() {
	return value;
}

element::element() {
	i = 1;
	j = 1;
	value = 0;
    next_e = nullptr;
    prev_e = nullptr;
    next_s = nullptr;
    prev_s = nullptr;
}
element::element(element* p_prev, element* p_next, int t_i, int t_j) {
	prev_e = p_prev;
	next_e = p_next;
	i = t_i;
	j = t_j;
}
void element::set_next_s(element* p) {
	next_s = p;
}
void element::set_prev_s(element* p) {
	prev_s = p;
}
element* element::get_next_s() {
	return next_s;
}
element* element::get_prev_s() {
	return prev_s;
}

element::~element() {
}

int such_size_matrix(element* A, int* m, int* n) {
	/*if ((*A).get_i() != 1) {
		printf("Error! Uncorrect top!");
		return 1;
	}*/
	int tmp = 1;
	element* str_tmp;
	str_tmp = A;
	element* col_tmp;
	col_tmp = A;

	while (str_tmp != nullptr) {
		col_tmp = str_tmp;
		while ((*col_tmp).get_next_e() != nullptr) {
			col_tmp = (*col_tmp).get_next_e();
		}
		if ((*col_tmp).get_j() > (*n)) {
			*n = (*col_tmp).get_j();
		}
		(*m) = (*str_tmp).get_i();
		str_tmp = (*str_tmp).get_next_s();		
	}
	
	return 0;
}