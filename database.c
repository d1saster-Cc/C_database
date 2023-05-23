#include <stdio.h> //подключаем загаловочный файл библиотеки стандартного ввода и вывода
#include <stdlib.h> //подключаем загаловочный файл библиотеки для работы с динамической памятью и других функций
#include <string.h> //подключаем загаловочный файл библиотеки для работы с строками
#include <ctype.h> //tolower


//определяем внешние функции из файла func.c
extern int zapol();
extern void dozapis();
extern void cat(const char* filename);
extern void delete(int m);
extern void search();
extern void red(int m);
extern void sort(int field, int m);
extern void swap(int m, int n, const char* filenamestr);
extern char* GetStr(size_t length);
extern char isEqual(const char* str1, const char* str2);









int main (){
  int mmm, field, count;
  char* command;
mainmenu: //метка главного меню, далее происходит вывод на экран информации с помощью функции  puts
  puts("Populating the database(Populating)");
  puts("Adding a record to the database(Add)");
  puts("Removing the specified record from the database(Remove)");
  puts("Search for a record by a given field(Search)");
  puts("Editing a given record in the database(Edit)");
  puts("Sorting data in the database by a given field(Sort)");
  puts("Displaying the contents of the database in a table form(Show)");
  puts("Select an action");
  command = GetStr(0); //считываем строку-команду
  fflush(stdin); //очищение буфера

      if(isEqual(command, "Populating")) //проверка на равенство строк вне зависимости от регистра букв
      {
        zapol(); //вызов нужной функции
        goto mainmenu; //вовзрат в главное меню //далее всё аналогично
      }

      if(isEqual(command, "Add"))
      {
        dozapis();
        goto mainmenu;
      }

      if(isEqual(command, "Remove"))
      {
        puts("Enter the number of the record you want to delete: ");
        scanf("%d", &mmm);
        fflush(stdin);
        delete(mmm);
        goto mainmenu;
      }

      if(isEqual(command, "Search"))
      {
        search();
        goto mainmenu;
      }

      if(isEqual(command, "Edit"))
      {
        puts("Enter the number of the record you want to rewrite: ");
        scanf("%d", &mmm);
        fflush(stdin);
        red(mmm);
        goto mainmenu;
      }

      if(isEqual(command, "Sort"))
      {
        puts("Enter the number of the field you want to sort by( Fio(1) Street(2) House(3) Apartments(4) Year of birth(5) ): ");
        scanf("%d", &field);
        fflush(stdin);
        puts("Enter the count of elements for sort: ");
        scanf("%d", &count);
        fflush(stdin);
        sort(field, count);
        goto mainmenu;
      }

      if(isEqual(command, "Show"))
      {
        cat("bd.txt");
        goto mainmenu;
      }

      if(isEqual(command, "exit"))
      {
        return 0;
      }

      printf("\n\"%s\" is not recognized as an internal or external command.\n\n", command);
      goto mainmenu;



}
