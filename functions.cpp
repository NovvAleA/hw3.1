#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

element* create_empty_matrix() {
    element* A = new element;
    return A;
}

int set_element(element* A, element** pA, int I, int J, int value) {
    int i = A->get_i();
    int j = 0;
    int m = 0;
    int n = 0;
    such_size_matrix(*pA, &m, &n);
    if (A == nullptr) {
        printf("Error!");
        return 1;
    }
    element* p_str_I;
    //  element str_I;
    element* p_column;
    // element column;

    if (A != nullptr) {

        element* p_column_tmp = A;
        element column_tmp = *A;
        element* p_str_tmp = A;
        element str_tmp = *A;

        while (i < I + 2) {

            if (i == I) {//существует необходимая  строка
                p_column_tmp = p_str_tmp;
                column_tmp = *p_column_tmp;
                
                while (j < n + 1) {
                    if (j == 0) {
                        j = column_tmp.get_j();
                    }
                    if (j == J) {
                        (*p_column_tmp).set_value(value);
                        return 0;
                    }
                    if (j > J) {
                        p_column = new element();
                        //   column = *p_column;
                        (*p_column).set_i(I);
                        (*p_column).set_j(J);
                        (*p_column).set_value(value);

                        (*p_column).set_prev_s(column_tmp.get_prev_s());
                        (*p_column).set_next_s(column_tmp.get_next_s());
                        (*p_column).set_next_e(p_column_tmp);
                        (*p_column).set_prev_e(p_column_tmp->get_prev_e());
                      
                        if (column_tmp.get_prev_e() != nullptr) {
                            (*column_tmp.get_prev_e()).set_next_e(p_column);
                        }                   
                        
                        if (p_column_tmp->get_prev_s() != nullptr) {
                            p_column_tmp->get_prev_s()->set_next_s(p_column);
                        }
                        if (p_column_tmp->get_next_s() != nullptr) {
                            p_column_tmp->get_next_s()->set_prev_s(p_column);
                        }
                        p_column_tmp->set_prev_e(p_column);
                        p_column_tmp->set_prev_s(nullptr);
                        p_column_tmp->set_next_s(nullptr);

                        if (I <= A->get_i()) {
                            if (J < A->get_j()) {
                                *pA = p_column;
                            }
                        }
                        
                        return 0;
                    }

                    if (column_tmp.get_next_e() == nullptr) {
                        p_column = new element();
                        //    column = *p_column;
                        (*p_column).set_i(I);
                        (*p_column).set_j(J);
                        (*p_column).set_value(value);
                        (*p_column).set_prev_e(&column_tmp);
                        (*p_column).set_next_e(nullptr);
                        (*p_column_tmp).set_next_e(p_column);
                        return 0;
                    }
                    p_column_tmp = column_tmp.get_next_e();
                    column_tmp = *p_column_tmp;
                    j = column_tmp.get_j();
                }
            }
            if (i > I) {
                p_str_I = new element;
                //    str_I = *p_str_I;
                (*p_str_I).set_i(I);
                (*p_str_I).set_j(J);
                (*p_str_I).set_value(value);
                (*p_str_I).set_prev_s((*p_str_tmp).get_prev_s());
                (*p_str_I).set_next_s(p_str_tmp);
                (*(*p_str_tmp).get_prev_s()).set_next_s(p_str_I);
                (*p_str_tmp).set_prev_s(p_str_I);
                (*p_str_I).set_next_e(nullptr);
                (*p_str_I).set_prev_e(nullptr);
                return 0;
            }
            if ((*p_str_tmp).get_next_s() == nullptr) {//дописывание новой строки в конец
                p_str_I = new element();
                //             str_I = *p_str_I;
                (*p_str_I).set_i(I);
                (*p_str_I).set_j(J);
                (*p_str_I).set_value(value);
                (*p_str_I).set_prev_s(p_str_tmp);
                (*p_str_I).set_next_s(nullptr);
                (*p_str_tmp).set_next_s(p_str_I);
                (*p_str_I).set_next_e(nullptr);
                (*p_str_I).set_prev_e(nullptr);
                return 0;
            }
            p_str_tmp = (*p_str_tmp).get_next_s();
            //    str_tmp = *p_str_tmp;
            i = (*p_str_tmp).get_i();
        }
    }
    return 1;
}

int scan_matrix_from_file(element* A) {
    FILE* inp;
    int m = 0;
    int n = 0;
    int tmp = 0;
    int flag = 0;

    inp = fopen("data.txt", "r");
    if (!inp) {
        printf("Cannot open file data.txt!");
        return 1;
    }

    if (fscanf(inp, "%d%d", &m, &n) == 0) {
        printf("Error! m & n undefined!\n");
    }
        

    for (int i = 1; i < m + 1; i++) {        
        for (int j = 1; j < n + 1; j++) {
            if (fscanf(inp, "%d", &tmp) != 0) {
                if (tmp != 0) {
                    if (flag == 0) {
                        A->set_i(i);
                        A->set_j(j);
                        A->set_value(tmp);
                        flag = 1;
                    }
                    set_element(A, &A, i, j, tmp);
                }
            }
            else {
                printf("Error! i,j = %d, %d\n", i, j);

                return 1;
            }
        }
    }

    fclose(inp);
    
    return 0;
}

int scan_matrix_from_file(element* A, const char* filename) {
    FILE* inp;
    int m = 0;
    int n = 0;
    int tmp = 0;
    int flag = 0;

    inp = fopen(filename, "r");
    if (!inp) {
        printf("Cannot open file %s!", filename);
        return 1;
    }

    if (fscanf(inp, "%d%d", &m, &n) != 2) {
        printf("Error! m & n undefined!\n");
    }


    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (fscanf(inp, "%d", &tmp) != 0) {
                if (tmp != 0) {
                    if (flag == 0) {
                        A->set_i(i);
                        A->set_j(j);
                        A->set_value(tmp);
                        flag = 1;
                    }
                    set_element(A, &A, i, j, tmp);
                }
            }
            else {
                printf("Error! i,j = %d, %d\n", i, j);

                return 1;
            }
        }
    }

    fclose(inp);

    return 0;
}

int print_matrix_in_file(element* A) {
    FILE* oup;
    int flag = 0;
    int m = 0;
    int n = 0;
    int tmp = 0;
    int i_str = 0;
    element* str_tmp;
    str_tmp = A;
    element* col_tmp;
    col_tmp = A;
    if (A == nullptr) {
        printf("Eroror in print matrix! A is nullptr");
        return 1;
    }
    oup = fopen("rez.txt", "w");
    if (!oup) {
        printf("Cannot open file data.txt!");
        return 1;
    }
    flag = such_size_matrix(A, &m, &n);
    if (flag != 0) {
        printf("Error!");
    }

    fprintf(oup, "%d %d\n\n", m, n);
    /*for (int i = 1; i < (*str_tmp).get_i(); i++) {
        for (int j = 0; j < n; j++) {
            fprintf(oup, "0 ");
        }
       fprintf(oup, "\n");
    }*/

    while (str_tmp != nullptr) {
        
        for (int i = 1; i < (*str_tmp).get_i() - i_str; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(oup, "0 ");
            }
            fprintf(oup, "\n");
        }
        while (col_tmp != nullptr) {
            for (int i = tmp; i < (*col_tmp).get_j() - 1; i++) {
                fprintf(oup, "0 ");
            }
            fprintf(oup, "%d ", (*col_tmp).get_value());
            tmp = (*col_tmp).get_j();            
            col_tmp = (*col_tmp).get_next_e();
        }
        for (int i = tmp; i < n; i++) {
            fprintf(oup, "0 ");
        }
        fprintf(oup, "\n");
        tmp = 0;
        i_str = (*str_tmp).get_i();
        str_tmp = (*str_tmp).get_next_s();
        col_tmp = str_tmp;
       
    }
    fclose(oup);
    return 0;
}

int get_value_i_g(element* A, int I, int J) {
    int i = 1;
    int j = 1;
    int m, n = 0;
    such_size_matrix(A, &m, &n);
    if (I > m || J > n) {
        printf("Matrix is less!\n");
        return 0;
    }
    if (A == nullptr) {
        printf("Error!");
        return 1;
    }
    element* p_str_I;
    //  element str_I;
    element* p_column;
    // element column;

    if (A != nullptr) {

        element* p_column_tmp = A;
        element column_tmp = *A;
        element* p_str_tmp = A;
        element str_tmp = *A;

        while (i < I + 1) {

            if (i == I) {//существует необходимая  строка
                p_column_tmp = p_str_tmp;
                column_tmp = *p_column_tmp;
                while (j < J + 1) {
                    j = column_tmp.get_j();
                    if (j == J) {                     
                        return (*p_column_tmp).get_value();
                    }
                    p_column_tmp = column_tmp.get_next_e();
                    if (p_column_tmp == nullptr) {
                        return 0;
                    }
                    column_tmp = *p_column_tmp;
                    
                }
            }
            p_str_tmp = (*p_str_tmp).get_next_s();
            if (p_str_tmp == nullptr) {
                return 0;
            }
            //    str_tmp = *p_str_tmp;
            i = (*p_str_tmp).get_i();
        }
    }

    return 0;
}

int exchange_of_string(element** pA, int I1, int I2 ) {
    int I = 0;
    int m = 0;
    int n = 0;
    int i = 1;
    int tmp = 0;
    element* A;
 
    if (pA == nullptr) {
        printf("Error! pA == nullptr\n");
        return 1;
    }
    element* p_str_tmp = *pA;
    element* p_str_I1 = nullptr;
    element* p_str_I2 = nullptr;
    element* ptr = nullptr;

    if (such_size_matrix(*pA, &m, &n) == 1) {
        return 1;
    }

    if (I1 > m || I2 > n) {
        printf("Matrix is less\n");
        return 1;
    }
    while (i < max(I1, I2) + 1) {
        if (i == I1) {
            p_str_I1 = p_str_tmp;
        }
        if (i == I2) {
            p_str_I2 = p_str_tmp;
        }
        p_str_tmp = (*p_str_tmp).get_next_s();
        if (p_str_tmp == nullptr) {
            break;;
        }
        i = (*p_str_tmp).get_i();
    }


    if (p_str_I1 != nullptr && p_str_I2 != nullptr) {//если обе строки существуют
        //на место I2 ставим I1
        
        if ((*p_str_I2).get_next_e() != nullptr) {
            (*(*p_str_I2).get_next_e()).set_prev_e(p_str_I1);
        }

        if ((*p_str_I1).get_next_e() != nullptr) {
            (*(*p_str_I1).get_next_e()).set_prev_e(p_str_I2);
        }

        ptr = (*p_str_I1).get_next_e();
        (*p_str_I1).set_next_e((*p_str_I2).get_next_e());
        (*p_str_I2).set_next_e(ptr);

        tmp = (*p_str_I1).get_j();
        (*p_str_I1).set_j((*p_str_I2).get_j());
        (*p_str_I2).set_j(tmp);

        tmp = (*p_str_I1).get_value();
        (*p_str_I1).set_value((*p_str_I2).get_value());
        (*p_str_I2).set_value(tmp);

        return 0;
    }
    if (p_str_I1 != nullptr && p_str_I2 == nullptr) {
              
        set_element(*pA, pA, I2, 1, 1);             //создали строку с номером I2
        p_str_I2 = pointer_on_i_string(*pA, I2);//нашли на неё указатель
        
        if ((*p_str_I1).get_next_e() != nullptr) {
            (*(*p_str_I1).get_next_e()).set_prev_e(p_str_I2);
            (*p_str_I2).set_next_e((*p_str_I1).get_next_e());
        }
        (*p_str_I2).set_j((*p_str_I1).get_j());
        (*p_str_I2).set_value((*p_str_I1).get_value());

        if (p_str_I1 == *pA) {
            ((*p_str_I1).get_next_s())->set_prev_s(nullptr);
            *pA = (*p_str_I1).get_next_s();
            return 0;
        }
        if (p_str_I1->get_next_s() == nullptr) {
            ((*p_str_I1).get_prev_s())->set_next_s((*p_str_I1).get_next_s());
            return 0;
        }
        ((*p_str_I1).get_prev_s())->set_next_s((*p_str_I1).get_next_s());//сшили список на месте I1
        ((*p_str_I1).get_next_s())->set_prev_s((*p_str_I1).get_prev_s());
    }
    if (p_str_I2 != nullptr && p_str_I1 == nullptr) {

        set_element(*pA, pA, I1, 1, 1);             //создали строку с номером I1
        p_str_I1 = pointer_on_i_string(*pA, I1);//нашли на неё указатель

        if ((*p_str_I2).get_next_e() != nullptr) {
            (*(*p_str_I2).get_next_e()).set_prev_e(p_str_I1);
            (*p_str_I1).set_next_e((*p_str_I2).get_next_e());
        }
        (*p_str_I1).set_j((*p_str_I2).get_j());
        (*p_str_I1).set_value((*p_str_I2).get_value());

        if (p_str_I2 == *pA) {
            ((*p_str_I2).get_next_s())->set_prev_s(nullptr);
            *pA = (*p_str_I2).get_next_s();
            return 0;
        }
        if (p_str_I2->get_next_s() == nullptr) {
            ((*p_str_I2).get_prev_s())->set_next_s((*p_str_I2).get_next_s());
            return 0;
        }
        ((*p_str_I2).get_prev_s())->set_next_s((*p_str_I2).get_next_s());//сшили список на месте I1
        ((*p_str_I2).get_next_s())->set_prev_s((*p_str_I2).get_prev_s());
    }

    return 0;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}
int min(int a, int b) {
    if (a > b) {
        return b;
    }
    return a;
}

element* pointer_on_i_string(element* A, int I){
    int i = 1;
    int j = 1;
    if (A == nullptr) {
        printf("Error!");
        return nullptr;
    }
    element* p_str_I;
    if (A != nullptr) {
        element* p_str_tmp = A;
        
        while (i < I + 1) {
            if (i == I) {//существует необходимая  строка
                return p_str_tmp;
            }
            p_str_tmp = (*p_str_tmp).get_next_s();
            if (p_str_tmp == nullptr) {
                return nullptr;
            }
            i = (*p_str_tmp).get_i();
        }
    }

    return nullptr;
}

int lin_comb_of_str(element** pA, int I1, int I2, int a) {//не забыть обработать случай исчезновения строк
    // I1 считается изменяемой строкой
    // I2 - прибавляемая
    int I = 0;
    int m = 0;
    int n = 0;
    int i = 0;
    int tmp = 0;
    int flag = 0;
    element* A;

    if (pA == nullptr) {
        printf("Error! pA == nullptr\n");
        return 1;
    }
    element* col_I1;
    element* col_I2;
    element* p_str_tmp = *pA;
    element* p_str_I1 = nullptr;
    element* p_str_I2 = nullptr;
    element* ptr = nullptr;

    if (such_size_matrix(*pA, &m, &n) == 1) {
        return 1;
    }

    if (I1 > m || I2 > m) {
        printf("Matrix is less\n");
        return 1;
    }
    i = (*pA)->get_i();
    while (i < max(I1, I2) + 1) {
        if (i == I1) {
            p_str_I1 = p_str_tmp;
        }
        if (i == I2) {
            p_str_I2 = p_str_tmp;
        }
        p_str_tmp = (*p_str_tmp).get_next_s();
        if (p_str_tmp == nullptr) {
            break;;
        }
        i = (*p_str_tmp).get_i();
    }


    if (p_str_I1 != nullptr && p_str_I2 != nullptr) {//если обе строки существуют
        col_I1 = p_str_I1;
        col_I2 = p_str_I2;
        int J1 = col_I1->get_j();//бегущие индексы для столбцов слогаемых строк
        int J2 = col_I2->get_j();


        for (int k = 1; k < n + 1; k++) {
            if (J1 == k || J2 == k) {
                if (J1 == k && J2 == k) {
                    tmp = col_I1->get_value() + a * col_I2->get_value();
                    if (tmp != 0) {
                        col_I1->set_value(tmp);
                    }
                    if (tmp == 0) {
                        if ((*col_I1).get_prev_e() == nullptr) {                          
                            if ((*col_I1).get_next_e() == nullptr) {
                                if (col_I1 == *pA) {
                                    *pA = (*p_str_I1).get_next_s();
                                    (*p_str_I1).get_next_s()->set_prev_s(nullptr);
                                    return 0;
                                }
                                else{
                                    if ((*p_str_I1).get_prev_s()!=nullptr) {
                                        ((*p_str_I1).get_prev_s())->set_next_s((*p_str_I1).get_next_s());
                                    }
                                    //сшили список на месте I1
                                    if ((*p_str_I1).get_next_s() != nullptr) {
                                        ((*p_str_I1).get_next_s())->set_prev_s((*p_str_I1).get_prev_s());
                                    }
                                    
                                }
                                
                            }
                            else {
                                if (col_I1 == *pA) {
                                    *pA = (*p_str_I1).get_next_e();
                                }
                                (*(*col_I1).get_next_e()).set_prev_e(nullptr);
                                (*(*col_I1).get_next_e()).set_next_s((*col_I1).get_next_s());                                                              
                                if ((*p_str_I1).get_next_s() != nullptr) {
                                    ((*p_str_I1).get_next_s())->set_prev_s((*col_I1).get_next_e());
                                }
                                //
                                if (col_I1 != *pA && p_str_I1->get_prev_s() != nullptr) {//
                                    ((*p_str_I1).get_prev_s())->set_next_s((*col_I1).get_next_e());
                                }
                                if ((*p_str_I1).get_next_e() == *pA) {
                                    p_str_I1 = (*col_I1).get_next_e();
                                }
                            }
                        }
                        else {
                            ((*col_I1).get_prev_e())->set_next_e((*col_I1).get_next_e());//сшили строку
                            if((*col_I1).get_next_e() != nullptr){
                                ((*col_I1).get_next_e())->set_prev_e((*col_I1).get_prev_e());
                            }
                            
                        }
                        
                    }
                    
                }
             // if (J1 == k && J2 != k) {}         
                if (J1 != k && J2 == k) {                 
                    set_element(*pA, pA, I1, J2, a * col_I2->get_value());
                }             
            }
            
            if (flag == 2) {
                return 0;
            }
            if (J1 <= k && J2 <= k) {
                if (col_I1->get_next_e() != nullptr) {
                    col_I1 = col_I1->get_next_e();
                    J1 = col_I1->get_j();
                }
                else {
                    flag = 1;
                }
                if (col_I2->get_next_e() != nullptr) {
                    col_I2 = col_I2->get_next_e();
                    J2 = col_I2->get_j();
                }
                else {
                    flag++;
                }
            }
            
          
          //  if (flag == 2) { return 0;}
            
             
        }

        return 0;
    }
    
    if (p_str_I1 == nullptr && p_str_I2 != nullptr) {

        set_element(*pA, pA, I1, 1, 0);             //создали строку с номером I1
        p_str_I1 = pointer_on_i_string(*pA, I1);//нашли на неё указатель

        lin_comb_of_str(pA, I1, I2, a);
    }

    return 0;
}

int sum_el_in_str(element* A, int I, int J1, int J2) {
    int i = 1;
    int j = 1;
    int sum = 0;
    if (A == nullptr) {
        printf("Error!");
        return 1;
    }
    element* str_I;
    //  element str_I;
    element* col_j;
    // element column;

    if (A != nullptr) {
        str_I = A;
        
       
        i = str_I->get_i();
        while (i < I + 1) {
            if (i == I) {//существует необходимая  строка
                col_j = str_I;              
                while (j < J2 + 1) {
                    j = col_j->get_j();
                    if (j >= J1 && j <= J2) {                    
                        sum += col_j->get_value();
                    } 
                    col_j = col_j->get_next_e();
                    if (col_j == nullptr) {
                        break;
                    }
                }
                break;
            }
            str_I = str_I->get_next_s();
            if (str_I == nullptr) {
                return 0;
            }          
            i = str_I->get_i();
        }
    }

    return sum;
}

int submatrix(element* A,  int I1, int I2, int J1, int J2) {
    FILE* oup;
    int flag = 0;
    int m = 0;
    int n = 0;
    int tmp = 0;
    int i_prev_str = 0;
    element* str_tmp;
    str_tmp = A;
    element* col_tmp;
    col_tmp = A;
    if (A == nullptr) {
        printf("Eroror in print matrix! A is nullptr");
        return 1;
    }
    oup = fopen("tmp.txt", "w");
    if (!oup) {
        printf("Cannot open file data.txt!\n");
        return 1;
    }
    flag = such_size_matrix(A, &m, &n);
    if (flag != 0) {
        printf("Error!\n");
    }
    if (max(I1, I2) > m || min(I1, I2) < 1) {
        printf("Error! Incorrect (I1, I2)\n");
        return 1;
    }
    if (max(J1, J2) > n || min(J1, J2) < 1) {
        printf("Error! Incorrect (J1, J2)\n");
        return 1;
    }
    if (I1 > I2 || J1 > J2) {
        printf("Error! I1 > I2 || J1 > J2\n");
        return 1;
    }
    m = I2 - I1 + 1;
    n = J2 - J1 + 1;
    i_prev_str = I1;
    tmp = J1 - 1;
    fprintf(oup, "%d %d\n\n", m, n);

    while (str_tmp != nullptr) {
        if ((*str_tmp).get_i() > I2) {
            break;
        }
        if ((*str_tmp).get_i() >= I1) {
            for (int i = 1; i < (*str_tmp).get_i() - i_prev_str; i++) {
                for (int j = 0; j < n; j++) {
                    fprintf(oup, "0 ");
                }
                fprintf(oup, "\n");
            }
            while (col_tmp != nullptr) {
                if ((*col_tmp).get_j() > J2) {
                    break;
                }
                if ((*col_tmp).get_j() >= J1) {
                    for (int j = tmp; j < (*col_tmp).get_j() - 1; j++) {
                        fprintf(oup, "0 ");
                    }
                    fprintf(oup, "%d ", (*col_tmp).get_value());
                }

                tmp = max((*col_tmp).get_j(), J1 - 1);
                col_tmp = (*col_tmp).get_next_e();
            }
            for (int i = tmp; i < J2; i++) {
                fprintf(oup, "0 ");
            }
            fprintf(oup, "\n");
        }
        
        tmp = J1 - 1;
        i_prev_str = (*str_tmp).get_i();
        str_tmp = (*str_tmp).get_next_s();
        col_tmp = str_tmp;

    }
    for (int i = i_prev_str; i < I2; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(oup, "0 ");
        }
        fprintf(oup, "\n");
    }
    
    fclose(oup);

 //   scan_matrix_from_file(B, "tmp.txt");
    return 0;
}

void free_element_memory(element* a) {
    delete a;
}

void free_list_memory(element* A) {
    int tmp = 1;
    element* str_tmp;
    str_tmp = A;
    element* col_tmp;
    col_tmp = A;

    while (str_tmp != nullptr) {
        if (str_tmp->get_prev_s() != nullptr) {
            free_element_memory(str_tmp->get_prev_s());
        }
        col_tmp = str_tmp;
        while ((*col_tmp).get_next_e() != nullptr) {
            col_tmp = (*col_tmp).get_next_e();
            if (col_tmp->get_prev_e()->get_prev_s() == nullptr) {
                if (col_tmp->get_prev_e()->get_next_s() == nullptr) {
                    if (col_tmp->get_prev_e() != nullptr) {
                        free_element_memory(col_tmp->get_prev_e());
                    }                 
                }
            }
        }
        str_tmp = (*str_tmp).get_next_s();    
    }
}