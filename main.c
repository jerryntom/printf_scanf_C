#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct point_t {
    int x;
    int y;
};

int my_printf(char *text, ...) {
    if(text == NULL) return -1;

    va_list args;

    int index, char_counter = 0;

    va_start(args, text);

    index = 0;
    while(*(text + index) != '\0') {
        if(*(text + index) == '%' && ((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') ||
                                      (*(text + index + 1) == 'f') || (*(text + index + 1) == 'p'))) {
            if(*(text + index + 1) == 's') {
                char *arg_text;
                arg_text = va_arg(args, char *);
                for(int i = 0; (unsigned int)i < strlen(arg_text); i++) {
                    putc(*(arg_text + i), stdout);
                    char_counter++;
                }
            }
            else if(*(text + index + 1) == 'd') {
                int arg_int;
                arg_int = va_arg(args, int);

                if(arg_int == 0) {
                    putc('0', stdout);
                    char_counter++;
                    index++;
                    continue;
                }
                char digit;

                int size_of_number = 0, temp_int, is_negative;

                if(arg_int < 0) {
                    is_negative = 1;
                    arg_int *= -1;
                }
                else is_negative = 0;

                temp_int = arg_int;

                while(temp_int >= 1) {
                    size_of_number++;
                    temp_int /= 10;
                }

                int power = size_of_number, exp;

                if(is_negative) {
                    putc('-', stdout);
                    char_counter++;
                }

                while(power >= 1) {
                    power--;
                    exp = (int)pow(10, power);
                    temp_int = arg_int;
                    temp_int /= exp;
                    digit = (char)(48 + (temp_int % 10));
                    putc(digit, stdout);
                    char_counter++;
                }
            }
            else if(*(text + index + 1) == 'f') {
                double f_num;
                f_num = va_arg(args, double);

                int is_negative;

                if(f_num < 0) {
                    is_negative = 1;
                    f_num *= -1;
                }
                else is_negative = 0;

                if(is_negative) {
                    putc('-', stdout);
                    char_counter++;
                }

                int digits_num = (int)log10(f_num) + 1;
                int i;
                for (i = 0; i < digits_num; i++) {
                    int digit = (unsigned char)(48 + (int)(f_num / pow(10, digits_num - i - 1)) % 10);
                    putc(digit, stdout);
                    char_counter++;
                }

                if((int)f_num == 0) {
                    putc('0', stdout);
                    char_counter++;
                }

                putc('.', stdout);
                char_counter++;
                int decimal_digits = 5;
                for (i = 0; i < decimal_digits; i++) {
                    f_num -= floor(f_num);
                    f_num *= 10;
                    int digit = (unsigned char)(48 + (int)f_num);
                    putc(digit, stdout);
                }
                char_counter += 5;
            }
            else if(*(text + index + 1) == 'p') {
                struct point_t point;
                point = va_arg(args, struct point_t);
                putc('(', stdout);
                char_counter++;

                int arg_int;
                arg_int = point.x;

                if(arg_int == 0) {
                    putc('0', stdout);
                    char_counter++;
                    index++;
                }
                char digit;

                int size_of_number = 0, temp_int, is_negative;

                if(arg_int < 0) {
                    is_negative = 1;
                    arg_int *= -1;
                }
                else is_negative = 0;

                temp_int = arg_int;

                while(temp_int >= 1) {
                    size_of_number++;
                    temp_int /= 10;
                }

                int power = size_of_number, exp;

                if(is_negative) {
                    putc('-', stdout);
                    char_counter++;
                }

                while(power >= 1) {
                    power--;
                    exp = (int)pow(10, power);
                    temp_int = arg_int;
                    temp_int /= exp;
                    digit = (char)(48 + (temp_int % 10));
                    putc(digit, stdout);
                    char_counter++;
                }

                putc(' ', stdout);
                char_counter++;

                arg_int = point.y;

                if(arg_int == 0) {
                    putc('0', stdout);
                    char_counter++;
                    index++;
                }

                size_of_number = 0;

                if(arg_int < 0) {
                    is_negative = 1;
                    arg_int *= -1;
                }
                else is_negative = 0;

                temp_int = arg_int;

                while(temp_int >= 1) {
                    size_of_number++;
                    temp_int /= 10;
                }

                power = size_of_number;

                if(is_negative) {
                    putc('-', stdout);
                    char_counter++;
                }

                while(power >= 1) {
                    power--;
                    exp = (int)pow(10, power);
                    temp_int = arg_int;
                    temp_int /= exp;
                    digit = (char)(48 + (temp_int % 10));
                    putc(digit, stdout);
                    char_counter++;
                }

                putc(')', stdout);
                char_counter++;
            }
        }
        else {
            if(((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') || (*(text + index + 1) == 'f')
            || (*(text + index + 1) == 'p')) && *(text + index - 1) != '%') {
                putc(*(text + index), stdout);
                char_counter++;
            }
            else if(((*(text + index + 1) != 's') && (*(text + index + 1) != 'd') && (*(text + index + 1) != 'f')
                && (*(text + index + 1) != 'p')) && *(text + index - 1) != '%') {
                putc(*(text + index), stdout);
                char_counter++;
            }
        }
        index++;
    }

    return char_counter;
}

int my_scanf(char *text, ...) {
    if(text == NULL) return -1;

    va_list args;

    int index = 0, c, elem_counter = 0;

    va_start(args, text);

    while(*(text + index) != '\0') {
        if(*(text + index) == '%' && ((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') ||
                                      (*(text + index + 1) == 'f') || (*(text + index + 1) == 'p'))) {
            if(*(text + index + 1) == 'd') {
                int num_size = 0, pos = 9, is_negative = 0;
                long long int num = 0, add;
                int *ptr = va_arg(args, int *);

                while(1) {
                    c = getchar();
                    if(isdigit(c)) {
                        add = (long long int)pow(10, pos) * ((int)c - 48);
                        num += add;
                        pos--;
                        num_size++;
                    }
                    else if(c == '-') {
                        is_negative = 1;
                        continue;
                    }
                    else {
                        if(num_size != 0) {
                            for(int i = 0; i <= (9 - num_size); i++) {
                                num /= 10;
                            }

                            if(is_negative) {
                                num *= -1;
                            }

                            *ptr = (int)num;
                            elem_counter++;
                        }

                        index++;

                        if(((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') || (*(text + index + 1) == 'f')
                            || (*(text + index + 1) == 'p')) && *(text + index - 1) != '%') {
                            if(c == *(text + index)) {
                                index++;
                            }
                            else return 0;
                        }
                        else if(((*(text + index + 1) != 's') && (*(text + index + 1) != 'd') && (*(text + index + 1) != 'f')
                                 && (*(text + index + 1) != 'p')) && *(text + index - 1) != '%') {
                            if(c == *(text + index)) {
                                index++;
                            }
                            else return 0;
                        }
                        else break;
                    }
                }
            }
            else if(*(text + index + 1) == 'f') {
                long double num = 0;

                int num_size = 0, pos = 9, is_negative = 0, is_decimal = 0;
                long double add;
                double *double_ptr = va_arg(args, double *);
                *double_ptr = 0;

                while(1) {
                    c = getchar();
                    if(isdigit(c)) {
                        if(c == '0' && num_size == 0) {
                            *double_ptr = 0;
                            elem_counter++;
                            break;
                        }

                        add = (long double)pow(10, pos) * ((int)c - 48);
                        num += add;
                        pos--;
                        num_size++;
                    }
                    else if(c == '-') {
                        is_negative = 1;
                        continue;
                    }
                    else {
                        if(c == '.') is_decimal = 1;

                        if(num_size != 0) {
                            for(int i = 0; i <= (9 - num_size); i++) {
                                num /= 10;
                            }

                            if(is_negative) {
                                num *= -1;
                            }

                            *double_ptr += (double)num;
                            elem_counter++;
                        }
                        index++;
                        break;
                    }
                }

                if(is_decimal != 1) {
                    index++;
                    continue;
                }
                else {
                    pos = 15;
                    num_size = 0;
                    long long int num = 0;
                    while(1) {
                        c = getchar();
                        if (isdigit(c)) {
                            add = (long long int) pow(10, pos) * ((int) c - 48);
                            num += add;
                            pos--;
                            num_size++;
                        }
                        else if (c == '-') {
                            is_negative = 1;
                            continue;
                        }
                        else {
                            if (num_size != 0) {
                                for (int i = 0; i <= (15 - num_size); i++) {
                                    num /= 10;
                                }

                                double add_decimal;
                                int power = num_size;

                                while(num >= 1) {
                                    add_decimal = (int)(num % 10) * pow(0.1, power);
                                    if(is_negative) *double_ptr -= add_decimal;
                                    else *double_ptr += add_decimal;
                                    num /= 10;
                                    power--;
                                }
                            }

                            index++;

                            if(*(text + index) == '\0') {
                                index--;
                                break;
                            }

                            if(((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') || (*(text + index + 1) == 'f')
                                || (*(text + index + 1) == 'p')) && *(text + index - 1) != '%') {
                                if(c != *(text + index)) return 0;
                            }
                            else if(((*(text + index + 1) != 's') && (*(text + index + 1) != 'd') && (*(text + index + 1) != 'f')
                                     && (*(text + index + 1) != 'p')) && *(text + index - 1) != '%') {
                                if(c != *(text + index)) return 0;
                            }

                            break;
                        }
                    }
                }
            }
            else if(*(text + index + 1) == 'p') {
                int pos = 0, num_counter = 0;
                struct point_t *point = va_arg(args, struct point_t *);

                c = getchar();
                if(c != '(') {
                    index++;
                    break;
                }
                pos++;

                long long int add, num = 0;
                int num_size = 0, is_negative = 0, pos_int = 9;

                if(pos != 0) {
                    while(1) {
                        c = getchar();
                        if(isdigit(c)) {
                            add = (long long int)pow(10, pos_int) * ((int)c - 48);
                            num += add;
                            pos_int--;
                            num_size++;
                        }
                        else if(c == '-') {
                            is_negative = 1;
                            continue;
                        }
                        else {
                            if(num_size != 0) {
                                for(int i = 0; i <= (9 - num_size); i++) {
                                    num /= 10;
                                }

                                if(is_negative) {
                                    num *= -1;
                                }
                                point->x = (int)num;
                                elem_counter++;
                            }
                            break;
                        }
                    }
                    num_counter++;
                }

                if(c != ' ') {
                    elem_counter -= 1;
                }

                num = 0;
                num_size = 0, is_negative = 0, pos_int = 9;

                if(num_counter == 1) {
                    while(1) {
                        c = getchar();
                        if(isdigit(c)) {
                            add = (long long int)pow(10, pos_int) * ((int)c - 48);
                            num += add;
                            pos_int--;
                            num_size++;
                        }
                        else if(c == '-') {
                            is_negative = 1;
                            continue;
                        }
                        else {
                            if(c != ')') {
                                elem_counter -= 1;
                                index++;
                                continue;
                            }

                            if(num_size != 0) {
                                for(int i = 0; i <= (9 - num_size); i++) {
                                    num /= 10;
                                }

                                if(is_negative) {
                                    num *= -1;
                                }
                                point->y = (int)num;
                                elem_counter++;
                            }

                            index += 2;

                            if(*(text + index) == '\0') {
                                index--;
                                break;
                            }

                            if(((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') || (*(text + index + 1) == 'f')
                                || (*(text + index + 1) == 'p')) && *(text + index - 1) != '%') {
                                c = getchar();
                                if(c != *(text + index)) return 0;
                            }
                            else if(((*(text + index + 1) != 's') && (*(text + index + 1) != 'd') && (*(text + index + 1) != 'f')
                                     && (*(text + index + 1) != 'p')) && *(text + index - 1) != '%') {
                                c = getchar();
                                if(c != *(text + index)) return 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
        else {
            if(((*(text + index + 1) == 's') || (*(text + index + 1) == 'd') || (*(text + index + 1) == 'f')
                || (*(text + index + 1) == 'p')) && *(text + index - 1) != '%') {
                if(c == *(text + index)) {
                    index++;
                    continue;
                }
                else return 0;
            }
            else if(((*(text + index + 1) != 's') && (*(text + index + 1) != 'd') && (*(text + index + 1) != 'f')
                     && (*(text + index + 1) != 'p')) && *(text + index - 1) != '%') {
                if(c == *(text + index)) {
                    index++;
                    continue;

                }
                else return 0;
            }
        }
        index++;
    }

    return elem_counter;
}

int main(void) {

    return 0;
}

