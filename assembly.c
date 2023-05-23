//#include <stdio.h> //подключаем загаловочный файл библиотеки стандартного ввода и вывода
#include <stdlib.h> //подключаем загаловочный файл библиотеки для работы с динамической памятью и других функций

int main() {
  system("gcc -c func.c laba9.c"); //Создаём объектные файлы
  system("gcc func.o laba9.o -o ext"); //объединяем их и создаём exe файл с названием ext
  system("del func.o"); //удаляем файл
  system("del laba9.o"); //удаляем файл
  system("ext.exe"); //запускаем файл
  return 1;
}
