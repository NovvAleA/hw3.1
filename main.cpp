#pragma once
#include "class.h"
#include "functions.h"

//int function_call(int mode) {
//    element* A;
//    A = create_empty_matrix();
//}

int AT() {
    element *A, *B;   
    A = create_empty_matrix();
    B = create_empty_matrix();
    scan_matrix_from_file(A, "test.txt");
    scan_matrix_from_file(B, "ans.txt");

    exchange_of_string(&A, 1, 4);
    set_element(A, &A, 2, 5, 0);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (get_value_i_g(A, i, j) != get_value_i_g(B, i, j)) {
                return 1;
            }
        }
    }

    free_list_memory(A);
    free_list_memory(B);

    return 0;
}

int mode_1() {
    element* A;
    A = create_empty_matrix();
    print_matrix_in_file(A); 
    printf("Open file rez.txt\n");
    return 0;
}
int mode_2(element* A) {
    int m, n = 0;
    such_size_matrix(A, &m, &n);
    printf("m = %d\nn = %d\n", m, n);
    return 0;
}
int mode_3(element* A) {
    int i, j, value = 0;
    printf("Enter i and j separated by a space:\n");
    if (scanf("%d%d", &i, &j) == 2) {
        printf("Value is %d\n", get_value_i_g(A, i, j));
        return 0;
    }
    else {
    printf("scanf error!\n");
    }
    return 1;
}
int mode_4(element* A, element** pA) {
    int i, j, value = 0;
    printf("Enter i,j and value separated by a space:\n");
    if (scanf("%d%d%d", &i, &j, &value) == 3) {
        set_element(*pA, pA, i, j, value);
        print_matrix_in_file(*pA);
        printf("Open file rez.txt\n");
        return 0;
    }
    else {
        printf("scanf error!\n");
    }
    return 1;
}
int mode_5(element** pA) {
    int i1, i2 = 0;
    printf("Enter i1 and i2 separated by a space:\n");
    if (scanf("%d%d", &i1, &i2) == 2) {
        exchange_of_string(pA, i1, i2);
        print_matrix_in_file(*pA);
        printf("Open file rez.txt\n");
        return 0;
    }
    else {
        printf("scanf error!\n");
    }
    return 1;
}
int mode_6(element* A) {
    int i, j1, j2 = 0;
    printf("Enter i and j1,j2 separated by a space:\n");
    if (scanf("%d%d%d", &i, &j1, &j2) == 3) {      
        printf("Sum is %d\n", sum_el_in_str(A, i, j1, j2));
        return 0;
    }
    else {
        printf("scanf error!\n");
    }
    return 1;
}
int mode_7(element* A) {
    int i1, i2, j1, j2 = 0;
    printf("Enter i1,i2 and j1,j2 separated by a space:\n");
    if (scanf("%d%d%d%d", &i1, &i2, &j1, &j2) == 4) {
        submatrix(A, i1, i2, j1, j2);
        printf("Open file tmp.txt\n");
        return 0;
    }
    else {
        printf("scanf error!\n");
    }
    return 1;
}


int main()
{  //при заруске считывается матрица из файла data.txt

    if (AT() == 1) {
        printf("Autotest failled!\n\n");
        return 1;
    }
    else {
        printf("Autotest passed!\n\n");
    }
    element* A;
    A = create_empty_matrix();
    scan_matrix_from_file(A);
    int mode = 0;
    printf("Hellow, user!\n\n");
    printf("Select  mode:\n");
    printf("1 - create empty matrix;\n");
    printf("2 - dimensions of the matrix;\n");
    printf("3 - get value of (i,j) element;\n");
    printf("4 - set value of (i,j) element;\n");
    printf("5 - exchange of strings;\n");
    printf("6 - sum for i-string el-s from j1 to j2;\n");
    printf("7 - get submatrix;\n\n");

    if (scanf("%d", &mode) != 1) {
        printf("Error scanf!");
    }

    switch (mode)
    {
    case 1:
        mode_1();
        break;
    case 2:
        mode_2(A);
        break;
    case 3:
        mode_3(A);
        break;
    case 4:
        mode_4(A, &A);
        break;
    case 5:
        mode_5(&A);
        break;
    case 6:
        mode_6(A);
        break;
    case 7:
        mode_7(A);
        break;
    default:
        printf("Uncorrect number!\n");
        break;
    }
 
    free_list_memory(A);
    return 0;
}
