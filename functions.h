#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "class.h"

element* create_empty_matrix();
int set_element(element* A, element** pA, int I, int J, int value);
int print_matrix_in_file(element* A);
int scan_matrix_from_file(element* A);
int scan_matrix_from_file(element* A, const char* filename);
int get_value_i_g(element* A, int I, int J);
int max(int a, int b);
int min(int a, int b);
int exchange_of_string(element** pA, int I1, int I2);
element* pointer_on_i_string(element* A, int I);
int lin_comb_of_str(element** pA, int I1, int I2, int a);
int sum_el_in_str(element* A, int I, int J1, int J2);
int submatrix(element* A, int I1, int I2, int J1, int J2);
void free_element_memory(element* a);
void free_list_memory(element* A);