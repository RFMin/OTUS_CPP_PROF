#include "ip_srt_lib.h"

//  aux function to compare value of the ip-fields
//  returns:
//  * 0 if a < b
//  * 1 if a > b
//  * 2 if a == b
int Ip_Compare(struct Ip *a, struct Ip *b) {
  if ((a->ip1) < (b->ip1))
    return 0;
  else if ((a->ip1) > (b->ip1))
    return 1;

  //  if function doesn't exit by this point, field a->ip1 == b->ip1
  //  and it is necessary to compare second fields
  if ((a->ip2) < (b->ip2))
    return 0;
  else if ((a->ip2) > (b->ip2))
    return 1;

  if ((a->ip3) < (b->ip3))
    return 0;
  else if ((a->ip3) > (b->ip3))
    return 1;

  if ((a->ip4) < (b->ip4))
    return 0;
  else if ((a->ip4) > (b->ip4))  // a->ip4 is > b->ip4
    return 1;
  else
    return 2;  // a == b
}

//  aux function to print Ip struct values;
void Ip_print(struct Ip value) {
  printf("\nIp-address is %d.%d.%d.%d", value.ip1, value.ip2, value.ip3,
         value.ip4);
}

//  prints full list of the elements
void Ip_list_print(struct Ip *pointer, struct Ip **end, int *qty) {
  //  printf("\n=== %s ===", __PRETTY_FUNCTION__);
  if (pointer != NULL) {
    do {
      // printf("\nId: %d\tIP: %d.%d.%d.%d,\tcurrent=%p,\tprev=%p,\tnext=%p",
      //        pointer->id, pointer->ip1, pointer->ip2, pointer->ip3,
      //        pointer->ip4, pointer, pointer->prev, pointer->next);
      *end = pointer;
      pointer = pointer->next;
      ++(*qty);
    } while (pointer != NULL);
  } else {
    printf("\nIp-address list is empty - nothing to print!");
  }
}

//  prints lists of the elements from element X to element Y
void Ip_elements_print(struct Ip **pointer[], int x, int y) {
  //  printf("\n=== %s ===", __PRETTY_FUNCTION__);
  if ((**pointer != NULL) && (x < y)) {
    do {
      printf("\nId: %lu\tIP: %d.%d.%d.%d", (*(*pointer + x))->id,
             (*(*pointer + x))->ip1, (*(*pointer + x))->ip2,
             (*(*pointer + x))->ip3, (*(*pointer + x))->ip4);
      x++;
    } while (x <= y);
  } else {
    printf("\nIp-address list is empty - nothing to print!");
  }
}

//  aux function to convert char number into integer number
int char_to_num(char ch) {
  int num = 0;
  switch (ch) {
    case '0':
      num = 0;
      break;
    case '1':
      num = 1;
      break;
    case '2':
      num = 2;
      break;
    case '3':
      num = 3;
      break;
    case '4':
      num = 4;
      break;
    case '5':
      num = 5;
      break;
    case '6':
      num = 6;
      break;
    case '7':
      num = 7;
      break;
    case '8':
      num = 8;
      break;
    case '9':
      num = 9;
      break;
    default:
      return (-1);
  }
  return (num);
}

//  used to do parsing of the line in the address-list
struct Ip ln_parsing(char buff[]) {
  // printf("\n=== %s ===", __PRETTY_FUNCTION__);
  Ip rv = {0, 0, 0, 0, 0, NULL, NULL};  //  structure with line parsed data
  unsigned char num = 0;  //  current position of the ip-address field
  char toggle = 0;        //  to toggle field address detection
  char field = 0;         //  current ip-address field
  for (int i = 0; (buff[i] != '\0' && field < 5); i++) {
    if ('0' <= buff[i] && buff[i] <= '9') {
      if (toggle == 0) {
        toggle = 1;
        field++;
      };
      num *= 10;
      num += char_to_num(buff[i]);
    } else {
      if (toggle) {
        switch (field) {
          case 1: {
            rv.ip1 = num;
            break;
          }
          case 2: {
            rv.ip2 = num;
            break;
          }
          case 3: {
            rv.ip3 = num;
            break;
          }
          case 4: {
            rv.ip4 = num;
            break;
          }
          default: {
            printf("\nExcessive fields. Check input data!");
          }
        }
        //  reset field values until new field is met
        toggle = 0;
        num = 0;
      }
    }
  }
  //  DEBUG
  //  Ip_print(rv);
  return (rv);
}

//  used to do linereading
int line_read(FILE *fh, char buff[]) {
  int rc = 0;
  int ch;
  unsigned char buff_idx = 0;
  while (((ch = fgetc(fh)) != '\n')) {
    if (char(ch) != '\n') {
      buff[buff_idx++] = ch;
      //  DEBUG
      //  printf("%c", ch);
    }
    if (ch == EOF) {
      rc = -1;
      break;
    }
  }

  buff[buff_idx++] = '\0';
  //  DEBUG condition. Delete after DEBUG is completed
  if (rc == 0) {
    //  DEBUG
    //  ln_parsing(buff);

    //  printf("\nReaded line is \"%s\"\n", buffer);
    //  printf("\n");
    buff_idx = 0;
  }

  return (rc);
}

//  function to add member to the list
int Ip_add(struct Ip **head, struct Ip **current, struct Ip value) {
  int rc = 0;                        //  return code of the function
  static unsigned int id_field = 0;  //  counter for id-field
  struct Ip *new_elem = NULL;

  if (*head == NULL) {
    (*head) = (struct Ip *)malloc(sizeof(struct Ip));
    if (head != NULL) {
      (*head)->id = id_field;
      (*head)->ip1 = value.ip1;
      (*head)->ip2 = value.ip2;
      (*head)->ip3 = value.ip3;
      (*head)->ip4 = value.ip4;
      (*head)->prev = NULL;
      (*head)->next = NULL;
      *current = *head;
      //  DEBUG
      //  printf("\n*head Ip_add = %p", *head);
      id_field++;
    } else {
      rc = -1;
      printf("\nError in memory allocation!");
    }
  } else {  //  memory allocation for second and other members
    //  HOLD - add memory allocation check
    (new_elem) = (struct Ip *)malloc(sizeof(struct Ip));
    if (new_elem != NULL) {
      (new_elem)->id = id_field;
      (new_elem)->ip1 = value.ip1;
      (new_elem)->ip2 = value.ip2;
      (new_elem)->ip3 = value.ip3;
      (new_elem)->ip4 = value.ip4;
      (new_elem)->prev = *current;
      (new_elem)->next = NULL;
      (*current)->next = new_elem;
      (*current) = (new_elem);
      //  DEBUG
      // printf("\n*current = %p,\tcurrent->prev = %p,\tcurrent->next = %p",
      //        *current, (*current)->prev, (*current)->next);
      id_field++;
    } else {
      rc = -1;
      printf("\nError in memory allocation!");
    }
  }
  return (rc);
}

//  fileopen procedure
FILE *fileopen() {
  //  HOLD - uncomment 4 lines to implement "filename" variable and change
  //  array initialization to ""
   char filename[FILENAME_SZ] = "list.txt";
  // char filename[FILENAME_SZ] = "ip_filter.tsv";
  // char filename[FILENAME_SZ];
  // printf("\nEnter name of the file with IP addresses: ");
  // scanf("%s", filename);
  // printf("Entered filename is %s", filename);

  FILE *fh = NULL;
  fh = fopen(filename, "r");
  if (!fh) {
    printf("\nFile %s is not found.", filename);
  } else {
    //  DEBUG purposes
    //  printf("\nFile %s is found. Reading information from it...\n", filename);
  }
  return (fh);
}

//  used to read ip-addresses from source file
int fileread(struct Ip **ip_head, struct Ip *current) {
  //  printf("\n=== %s ===", __PRETTY_FUNCTION__);
  char rc = 0;  //  return code of the function
  struct Ip *head = *ip_head;

  FILE *fh = fileopen();
  if (!fh) {  //  File is not found
    rc = -1;
  } else {  //  File is found.
    char buffer[LINE_BUFF_SZ] = "";

    while (!line_read(fh, buffer)) {
      Ip_add(&head, &current, ln_parsing(buffer));
    }
    fclose(fh);
  }
  *ip_head = head;
  return (rc);
}

//  function to sort list using Haara method
//  HOLD - function to be optimized swapping pointer rather than values of the list!!!
void quicksort(struct Ip **array[], int low, int high) {
  int i = low;
  int j = high;
  struct Ip y = {0, 0,    0,   0,
                 0, NULL, NULL};  //  used to temporary store value during
                                  //  elements swapping
  struct Ip i_val = {0, 0,    0,   0,
                     0, NULL, NULL};  //  aux variable to make code easy to read
  struct Ip j_val = {0, 0,    0,   0,
                     0, NULL, NULL};  //  aux variable to make code easy to read
  struct Ip z = *(*(*array + (low + high) / 2));  //  median value in the array
  //  DEBUG
  // printf("\n== QUICKSORT iteration ==");
  // Ip_elements_print(array, low, high);
  // printf("\nlow = %d,\thigh = %d", low, high);
  // printf("\n====  z_val: ");
  // Ip_print(z);

  do {  //  main do
    i_val = *(*(*array + i));
    //  * 0 if i_val < z
    while (Ip_Compare(&i_val, &z) == 0) {
      i++;
      i_val = *(*(*array + i));
    };

    j_val = *(*(*array + j));
    //  * 1 - if j_val > z
    while (Ip_Compare(&j_val, &z) == 1) {
      j--;
      j_val = *(*(*array + j));
    };

    if (i <= j) {
      //  HOLD - not optimum sorting due to swapping values
      //  It is much more efficient to swap pointers!!! Optimization could be done later
      y = i_val;
      *(*(*array + i)) = j_val;
      *(*(*array + j)) = y;
      i++;
      j--;
    }
  } while (i <= j);  //  main do end

  //  recursion
  if (low < j) quicksort(array, low, j);
  if (i < high) quicksort(array, i, high);
}
