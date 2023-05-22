/*
Выполнение домашнего задания по OTUS С++ Developer Professional.
Смотри задание в файле "02-homework-12995...pdf"
Основные решения, заложенные в программу:
1) считывание IP_адресов в список со структурой данных:
- поле 0: id записи
- поле 1: поле 1 IP-адреса
- поле 2: поле 2 IP-адреса
- поле 3: поле 3 IP-адреса
- поле 4: поле 4 IP-адреса
- указатель на предыдущий элемент;
- указатель на следующий элемент;
2) определение максимального количества строк;
3) создание вспомогательного массива указателей на записи в списке
4) сортировка вспомогательного массива по возрастанию/убыванию
5) вывод всего списка по убыванию/возрастанию;
6) вывод списка согласно критериям в полях.
Выполнено: Руслан Миначев
*/

#include <stdio.h>
#include <stdlib.h>
#include "ip_srt_lib.h"
#include "lib.h"


int main() {
  struct Ip *ip_head = NULL;
  struct Ip *ip_bottom = NULL;
  struct Ip *ip_current = NULL;
  int ip_list_qty = 0;

  if ( fileread(&ip_head, ip_current) ) 
    exit(-1);   //  leave program - were not able to open file to read
  //  DEBUG - to confirm proper reading of the
  Ip_list_print(ip_head, &ip_bottom, &ip_list_qty);

  //  pointers array to make soring more efficient, it is necessary to swap pointers of the 
  //  IP-list instead of the real IP-values
  //  Optimization is not implemented - to be done later
  struct Ip **aux_ptr_array = NULL;
  aux_ptr_array =
      (struct Ip **)realloc(aux_ptr_array, ip_list_qty * sizeof(struct Ip *));
  ip_current = ip_head;
  for (int i = 0; i < ip_list_qty; ++i) {
    aux_ptr_array[i] = ip_current;
    ip_current = ip_current->next;
  }

  //  DEBUG
  // for (int i = 0; i < ip_list_qty; ++i) {
  //   printf("\ni: %d,\tpointer %p", i, aux_ptr_array[i]);
  // }

  //  DEBUG - print list before sorting
  //  Ip_elements_print(&aux_ptr_array, 0, ip_list_qty - 1);

  quicksort(&aux_ptr_array, 0, ip_list_qty - 1);

  //  DEBUG - print list after sorting
  Ip_elements_print(&aux_ptr_array, 0, ip_list_qty - 1);

  return (0);
}
