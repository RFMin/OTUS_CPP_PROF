# вырезать первую колонку с адресами
# cut -f 1 list.txt

# сортировка в порядке возрастания - колонки 2 и 3 не фильтруются
# sort -t . -k 1,1n -k 2,2n -k 3,3n -k 4,4n ip_filter.tsv
#!/bin/bash
cut -f 1 list.txt | sort -t . -k 1,1n -k 2,2n -k 3,3n -k 4,4n
