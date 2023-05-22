#include <stdio.h>
#include <stdlib.h>


#ifndef SRC_IP_SRT_LIB_HPP_
#define SRC_IP_SRT_LIB_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#define FILENAME_SZ \
  255  //  expected length of the filename with IP addressed database
#define LINE_BUFF_SZ 80  //  buffer to read lines from file with IP-addresses

struct Ip {
  unsigned long id = 0;
  unsigned char ip1 = 0;
  unsigned char ip2 = 0;
  unsigned char ip3 = 0;
  unsigned char ip4 = 0;
  Ip *prev = NULL;
  Ip *next = NULL;
};

//  aux function to compare value of the ip-fields
//  returns:
//  * 0 if a < b
//  * 1 if a > b
//  * 2 if a == b
int Ip_Compare(struct Ip *a, struct Ip *b);

//  aux function to print Ip struct values;
void Ip_print(struct Ip value);

//  prints full list of the elements
void Ip_list_print(struct Ip *pointer, struct Ip **end, int *qty);

//  prints lists of the elements from element X to element Y
void Ip_elements_print(struct Ip **pointer[], int x, int y);

//  aux function to convert char number into integer number
int char_to_num(char ch);

//  used to do parsing of the line in the address-list
Ip ln_parsing(char buff[]);

//  used to do linereading
int line_read(FILE *fh, char buff[]);

//  function to add member to the list
int Ip_add(struct Ip **head, struct Ip **current, struct Ip value);

//  fileopen procedure
FILE *fileopen();

//  used to read ip-addresses from source file
int fileread(struct Ip **ip_head, struct Ip *current);

//  function to sort list using Haara method
//  HOLD - function to be optimized swapping pointer rather than values of the list!!!
void quicksort(struct Ip **array[], int low, int high);

#ifdef __cplusplus
}
#endif

#endif  //  SRC_IP_SRT_LIB_HPP_