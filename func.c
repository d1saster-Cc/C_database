#include <stdio.h> //подключаем заголовочный файл библиотеки стандартного ввода и вывода
#include <stdlib.h> //подключаем заголовочный файл библиотеки для работы с динамической памятью и других функций
#include <string.h> //подключаем заголовочный файл библиотеки для работы с строками
#include <ctype.h> //tolower


char* GetStr(size_t length) { //создаём функцию, отвечающую за выделение памяти для строки определённой или неопределённой длины (зависит от передаваемого параметра)
  if (length <= 0) length = SIZE_MAX; //если передаём 0 или отрицательное число, размер строки считается неопределённым и мы задаём максимальную длину в SIZE_MAX (зависит от параметров системы)
  char* str = (char*)malloc(1), character; //создаём строку размера 1 и переменную под символы
  int size = 0; //создаём переменную целого типа, отвечающую за размер строки и индексы символов в ней
  for (int i = 1; (character = getchar()) != '\n'; ++size) { //считываем строку посимвольно в цикле
    if (size == length) //случай переполнения
      goto err1; //оператор безусловного перехода, перейдём на метку err1
    else if (i > length / 2 && i != length) //если размер строки больше чем максимальная её длина делённая пополам, заданная нами, то выделяем память сразу под максимальную длину (Это нужно, чтобы например при условии выбора SIZE_MAX в качестве максимальной длины строки, мы не привысили это значение, увеличивая выделяемую память в два раза)
      str = (char*)realloc(str, i = length);
    else if (size == i)
      str = (char*)realloc(str, i *= 2); //увеличиваем выделяемую память в два раза
    if (str == NULL) //если не удалось выделить память
      goto err2; //оператор безусловного перехода, перейдём на метку err2
    else str[size] = character; //записываем символ в строку по индексу
  }
  if ((str = (char*)realloc(str, size + 1)) == NULL) goto err2; //увеличиваем память на 1 единицу соответствующего размера (char) и сразу проверяем, что это выделение памяти прошло успешно
  str[size] = 0; //записываем в конце 0, чтобы си воспринимал ассив символов, как строку
  return str; //возвращаем нашу строку
  err1:
  free(str); //высвобождаем память выделенную под str
  err2: // Возвращаем NULL указатель, так как не удалось выделить необходимое кол-во памяти под строку
  return NULL;
}

void inputUInt(int* val, char lol) { //функция ввода целых беззнаковых значений
  int f; //флажок выхода из цикла
  do { //цикл, из которого пользователь не выйдет, пока не введёт значение переменной правильно
    f = 0; //флаг
    lol == '\0' ? printf("\0") : printf("Enter %c:", lol); //Тернарный оператор, отвечающий за способ вывода сообщения в зависимости от передаваемого значения типа char
    scanf_s("%d", val); //ввод переменной
    if (getchar() != '\n') { //проверка, осталось ли что-то в потоке ввода, если да - было введено не только число
      f = 1; //смена флажка, чтобы цикл повторился
      printf("Invalid input!\n"); //сообщени о неправильном вводе
      while (getchar() != '\n'); //очищение строки ввода
    }
  } while (f == 1);
  if (*val < 0) *val *= -1;
}


struct district { //структура, описывающая жителя района
  char* fio;
  char* street;
  int house;
  int kv;
  int bd;
};

char isEqual(const char* str1, const char* str2) { //проверка на равенство двух строк вне зависимости от регистра
    if (strlen(str1)!=strlen(str2)) return 0; //если не равны длины возвращаем 0
    for (char i = 0; str2[i]; ++i)
        if (tolower(str1[i]) != tolower(str2[i])) //если не равны соответствующие элементы в нижнем регистре возвращаем 0
            return 0;
    return 1;
}



int count_lines(const char* filename) { //функция для нахождения количества строк - 1
   FILE* fpf;
   int cnt = 0;
   char ch;
   if((fpf = fopen(filename, "r")) == NULL) //открываем файл в режиме чтения
         return 0;
   while (!feof(fpf) && !ferror(fpf)) //пока не достигнут конец файла и нет ошибки
  {
      ch = getc(fpf);
      if (ch == '\n') cnt++; //при символе перехода на новую строку прибавляем 1 к cnt
  }
   if (ferror(fpf))
       printf("err\n");
   fclose(fpf); //закрываем файл
   return cnt; //возвращаем количество строк - 1
}



void red(int m) { //функция редактирования записи
  int res = m*5 - 4, i = 1;
  char ch;
  FILE *file; //ссылка на поток
  FILE *fp2; //ссылка на поток
  struct district ds;
  if (count_lines("bd.txt") / 5 < m || m <= 0) {puts("\n\n"); puts("Not enough entries in database!!"); puts("\n\n"); return;} //если нет такой записи
  if ((file=fopen("bd.txt", "r"))==NULL) { //открываем текстовый файл в режиме чтения
  printf("Cannot open file.\n");
  exit (1);
  }

  if ((fp2=fopen("newbd.txt", "w"))==NULL) { //открываем текстовый файл в режиме записи
  printf("Cannot open file.\n");
  exit (1);
  }

  //считываем новые данные о пользователе
  puts("Enter fio: ");
  ds.fio = GetStr(0); //С помощью функции GetStr считываем строку неизвестной длины
  puts("Enter street name: ");
  ds.street = GetStr(0);
  puts("Enter the house number: ");
  inputUInt(&ds.house, '\0');
  puts("Enter the number of apartments: ");
  inputUInt(&ds.kv, '\0');
  puts("Enter year of birth: ");
  inputUInt(&ds.bd, '\0');
  fflush(stdin);
  int flag = 0;

  while (!feof(file) && !ferror(file)) //пока не достигнут конец файла и нет ошибки
  {
      ch = getc(file); //считываем посимвольно
      if (ch == '\n') i += 1; //счётчик строки
      if (ch != EOF)
      {
        if (i < res || i > (res + 4)) {
          fputc(ch, fp2); //если мы не на нужной строке, то просто записываем в ноый файл из старого
        }
        if (i >= res && i <= (res + 4) && flag == 0 && m!=1) {fprintf(fp2, "\n%s\n%s\n%d\n%d\n%d", ds.fio, ds.street, ds.house, ds.kv, ds.bd); flag = 1;} //при не первой записи, записываем так
        else if (i >= res && i <= (res + 4) && flag == 0 && m==1) {fprintf(fp2, "%s\n%s\n%d\n%d\n%d", ds.fio, ds.street, ds.house, ds.kv, ds.bd); flag = 1;} //при первой записи, записываем так
      }

  }

  fclose(file); //закрываем файлы
  fclose(fp2);



  system("del bd.txt"); //удаляем старый файл
  rename("newbd.txt", "bd.txt"); //переименовываем
  cat("bd.txt"); //выводим на экран бд
}


void search() { //функция поиска по заданной строке
  int field, s, i = 1, fl = 0;
  char* str;
  char ch;
  char *str1;
  str1 = (char*)malloc(sizeof(char));
  int n = 0, m = 1;

  FILE *file; //ссылка на поток

  if ((file=fopen("bd.txt", "r"))==NULL) { //открываем текстовый файл в режиме чтения
  printf("Cannot open file.\n");
  exit (1);
  }

  nbc:
  puts("Enter the field you want to search( Fio(1) Street(2) House(3) Apartments(4) Year of birth(5) ): ");
  scanf("%d", &field); //считываем нужное поле
  fflush(stdin);

  if (field == 1 || field == 2 || field == 3 || field == 4 || field == 5) { //проверка на корректность введеного поля
    puts("Enter the string: ");
    str = GetStr(0);
  }
  else {puts("Error!"); goto nbc;}
  if (field == 5) field = 0;

BB:
  while (!feof(file) && !ferror(file)) //пока не достигнут конец файла и нет ошибки
  {
      if (ch == '\n') i += 1; //счетчик строк
      ch = getc(file); //посимвольно считываем
      if (ch != EOF && i % 5 == field) { //при нужной строке
        if (ch == '\n') {str1[n] = 0; break;} //выходим из цикла, если строка закончилась, в конце ставим 0
        str1[n] = ch;
        str1 = (char*)realloc(str1, sizeof(char)*(n+2)); //выделяем доп память на следующий раз, с местом под 0 в конце
        n++; //индекс записываемого символа
      }
  }

  if (strcmp(str1, str) == 0) //если строки совпали
  {
    char ch2;
    FILE* fp2;
    FILE* fp3;
    FILE* fp4;
    if ((fp2=fopen("bd.txt", "r"))==NULL) { //открываем текстовый файл в режиме записи
    printf("Cannot open file.\n");
    exit (1);
    }
    if ((fp3=fopen("tmpbd.txt", "w"))==NULL) { //открываем текстовый файл в режиме записи
    printf("Cannot open file.\n");
    exit (1);
    }

    while (!feof(fp2) && !ferror(fp2)) //создаём клон bd.txt
    {
        ch2 = getc(fp2);
        if (ch2 != EOF)
        {
          fputc(ch2, fp3);
        }
    }

    fclose(fp2);//закрываем файл
    fclose(fp3);//закрываем файл

    if ((fp3=fopen("tmpbd.txt", "r"))==NULL) { //открываем текстовый файл в режиме записи
    printf("Cannot open file.\n");
    exit (1);
    }

    if (fl == 0) { //запись или дозапись, в зависимости от флага
    if ((fp4=fopen("tmps.txt", "w"))==NULL) { //открываем текстовый файл в режиме записи
    printf("Cannot open file.\n");
    exit (1);
    }

    }
    else {
    if ((fp4=fopen("tmps.txt", "a"))==NULL) { //открываем текстовый файл в режиме записи
    printf("Cannot open file.\n");
    exit (1);
    }
  }


    int u = 1;
    char ch1;
    while (!feof(fp3) && !ferror(fp3)) //переписываем только запись, с нужным номером во временный файл
    {
        if (ch1 == '\n') u += 1;
        ch1 = getc(fp3);
        if (ch1 != EOF && u >= m*5 - 4 && u <= m*5)
        {
          fputc(ch1, fp4);
        }
    }
    fclose(fp3); //закрываем файл
    fclose(fp4); //закрываем файл
    fl = 1; //флаг
    m++; //номер записи
    if (!feof(file) && !ferror(file)){str1 = (char*)realloc(str1, sizeof(char)); n = 0; goto BB;}// сбрасываем все переменные и идём дальше
  }
  else {
    m++;
    if (!feof(file) && !ferror(file)){str1 = (char*)realloc(str1, sizeof(char)); n = 0; goto BB;} //если строки не совпали, сбрасываем все переменные и идём дальше, если не достигнут конец файла
  }

  cat("tmps.txt"); //вывод на экран
  system("del tmpbd.txt"); //удаление файлов
  system("del tmps.txt");
  fclose(file); //закрываем файл
}


void delete(int m) { //функция удаления записи
  if (count_lines("bd.txt") / 5 < m || m <= 0) {puts("\n\n"); puts("Not enough entries in database!!"); puts("\n\n"); return;} //проверка на существования номера записи
  int res = m*5 - 4, i = 1;
  char ch;
  FILE *file; //ссылка на поток
  FILE *fp2; //ссылка на поток

  if ((file=fopen("bd.txt", "r"))==NULL) { //открываем текстовый файл в режиме чтения
  printf("Cannot open file.\n");
  exit (1);
  }

  if ((fp2=fopen("newbd.txt", "w"))==NULL) { //открываем текстовый файл в режиме записи
  printf("Cannot open file.\n");
  exit (1);
  }


  while (!feof(file) && !ferror(file)) //переписываем в новый файл всё, кроме выбранной записи
  {
      ch = getc(file);
      if (ch == '\n') i += 1;
      if (ch != EOF && (i < res || i > res + 4))
      {
        if (m == 1 && i == 6 && ch == '\n')
          continue; //перейти к следующей итерации цикла
        else fputc(ch, fp2);
      }

  }

  fclose(file);//закрываем файлы
  fclose(fp2);



  system("del bd.txt");//удаляем, переименовываем и выводим на экран
  rename("newbd.txt", "bd.txt");
  cat("bd.txt");
}






void cat(const char* filename) //функция вывода бд в табличном виде
{
    int ch, i = 1;
    int ch1;
    FILE *file = fopen(filename, "r"); //открываем файл в режиме чтения
    printf("\nFio: ");
    while (!feof(file) && !ferror(file))
    {
        ch = getc(file); //считается символ из файла
        if (ch != EOF)
        {
            putchar(ch); //выводим символ на экран
        }
        if (ch == '\n') //если произошел переход к новой строке
        {
          i += 1; //счётчик строк
          ch1 = getc(file); //считается символ из файла
          if (!feof(file) && !ferror(file)) {
            if (i % 5 == 1) printf("\nFio: "); //смотрим остаток от деления номера строки на 5 и выводим нужное
            if (i % 5 == 2) printf("Street: ");
            if (i % 5 == 3) printf("House number: ");
            if (i % 5 == 4) printf("Apartments: ");
            if (i % 5 == 0) printf("Year of birth: ");
        }
        if (ch1 != EOF)
        {
            putchar(ch1);//выводим символ на экран
        }
        }
    }
    putchar('\n');//выводим символ на экран
    fclose(file);//закрываем файл
}

void dozapis(){ //функция дозаписи в бд
  FILE *fp;
  char RoE; //для выбора действий
  struct district ds; //создаём объект типа district
  if ((fp=fopen("bd.txt", "at"))==NULL) { //открываем файл в режиме дозаписи
   printf ("Cannot open file.\n");
    exit(1);
  }
  puts("Enter fio: ");
  ds.fio = GetStr(0); //считывается строка неизвестной заранее длины
  puts("Enter street name: ");
  ds.street = GetStr(0);
  puts("Enter the house number: ");
  inputUInt(&ds.house, '\0'); //считывается целое число по модулю
  puts("Enter the number of apartments: ");
  inputUInt(&ds.kv, '\0');
  puts("Enter year of birth: ");
  inputUInt(&ds.bd, '\0');

  puts("record(1) or not(2)?");
  RoE = getch(); //выбор записывать или нет
  if (RoE == '1')
  {
    fprintf(fp, "%s\n%s\n%d\n%d\n%d\n", ds.fio, ds.street, ds.house, ds.kv, ds.bd); //записываем в конец файлы
    fflush(stdin); //очищаем буфер
    fclose(fp); //закрываем файл
  }
  else{fflush(stdin); fclose(fp);} //очищаем буфер и закрываем файл
}


int zapol(){ //функция формирования бд, возвращает количество записей
  FILE *fp;
  int flag = 0;
  int count = 0;
  int RoE;
  struct district ds;
  char* cmd;

  printf("\n\n");
  puts("Are you sure you want to rewrite the database? (write yes or no)"); //выводим строку, где убеждаем или нет в согласии пользователя
  printf("\n\n");
  cmd = GetStr(0); //считываем команду
  fflush(stdin);

  if(!strcmp(cmd, "yes")) { //сравниваем строки


  if ((fp=fopen("bd.txt", "wt"))==NULL) {
   printf ("Cannot open file.\n");
    exit(1);
  }

  for(;;){
    if(flag) {
      puts("Continue(1) or exit(2)?");
      RoE = getch();
      if (RoE == '2'){fclose(fp); return count;}
      fflush(stdin);
    }
    puts("Enter fio: ");
    ds.fio = GetStr(0); //считывается строка неизвестной заранее длины
    puts("Enter street name: ");
    ds.street = GetStr(0);
    puts("Enter the house number: ");
    inputUInt(&ds.house, '\0'); //считывается целое число по модулю
    puts("Enter the number of apartments: ");
    inputUInt(&ds.kv, '\0');
    puts("Enter year of birth: ");
    inputUInt(&ds.bd, '\0');
    puts("record(1) or exit(2)?"); //выбор производить ли запись
    RoE = getch();
    if (RoE == '1')
    {
      fprintf(fp, "%s\n%s\n%d\n%d\n%d\n", ds.fio, ds.street, ds.house, ds.kv, ds.bd); //записываем в файл
      fflush(stdin);
      count++;
      flag = 1;
    }
    else if (RoE == '2') {fclose(fp); return count;}
    else{fclose(fp); return count;}
  }

}



if(!strcmp(cmd, "no")) {return 0;} //сравниваем строки

printf("\n\"%s\" is not recognized as an internal or external command.\n\n", cmd); //при неверной команде возвращаем -1
return -1;

}

void swap(int m, int n, const char* filenamestr) { //функция для того, чтобы поменять местами записи в текстовом
  int res1 = m*5-4;//вычисляем первую строку каждой записи
  int res2 = n*5-4;
  FILE* gg;
  /*Опишу принцип работы: Создаётся 3 временных файла, в первый записывается первая нужная запись, во второй вторая, а в третий
  переписывается наша бд, но на нужном месте переписываются данные из других временных файлов в обратном порядке(для смены мест)
  затем два временных файла удаляются, старый файл бд удаляется, а новый переименовывается*/
  FILE* tmp;
  FILE* tmpn1;
  FILE* tmpn2;
  char ch;
  int i = 1, fl1 = 1, fl2 = 1;

  if ((gg=fopen(filenamestr, "rt"))==NULL) { //открываем файл в режиме чтения
   printf ("Cannot open file.\n");
    exit(1);
  }
  if ((tmp=fopen("tmpbd.txt", "wt"))==NULL) {//открываем файл в режиме записи
   printf ("Cannot open file.\n");
    exit(1);
  }
  if ((tmpn1=fopen("tmpn1.txt", "wt"))==NULL) {
   printf ("Cannot open file.\n");
    exit(1);
  }
  if ((tmpn2=fopen("tmpn2.txt", "wt"))==NULL) {
   printf ("Cannot open file.\n");
    exit(1);
  }

  while (!feof(gg) && !ferror(gg)) //считываем нужную запись в 1 текстовый файл
  {
      if (ch == '\n') i += 1;
      ch = getc(gg);
      if (ch != EOF && i >= res1 && i <= res1 + 4) {
        fputc(ch, tmpn1);
      }
  }
  fseek(gg, 0, SEEK_SET); //переводим каретку в начало
  ch = '\0';
  i = 1;
  while (!feof(gg) && !ferror(gg)) //считываем нужную запись в 2 текстовый файл
  {
      if (ch == '\n') i += 1;
      ch = getc(gg);
      if (ch != EOF && i >= res2 && i <= res2 + 4) {
        fputc(ch, tmpn2);
      }
  }
  fseek(gg, 0, SEEK_SET); //переводим каретку в начало
  ch = '\0';
  i = 1;
  fclose(tmpn1); //закрываем файлы для записи и открываем для чтения
  fclose(tmpn2);
  if ((tmpn1=fopen("tmpn1.txt", "rt"))==NULL) {
   printf ("Cannot open file.\n");
    exit(1);
  }
  if ((tmpn2=fopen("tmpn2.txt", "rt"))==NULL) {
   printf ("Cannot open file.\n");
    exit(1);
  }

  while (!feof(gg) && !ferror(gg)) //переписываем уже как нужно в новый файл бд i счётчик строки
  {
    if (ch == '\n') i += 1;
    ch = getc(gg);
    if (ch != EOF && (i < res1 || i > res1+4) && (i < res2 || i > res2+4)) {
      fputc(ch, tmp);
    }
    if (ch != EOF && i >= res1 && i <= res1 + 4 && fl1 == 1) {
      while (!feof(tmpn2) && !ferror(tmpn2)) {
        //if (ch == '\n') tn += 1;
        ch = getc(tmpn2);
        if (ch != EOF){
          fputc(ch, tmp);
        }

      }
      ch = '\0'; //обнуляем ch
      fl1 = 0;
    }
    if (ch != EOF && i >= res2 && i <= res2 + 4 && fl2 == 1) {
      while (!feof(tmpn1) && !ferror(tmpn1)) {
        //if (ch == '\n') tm += 1;
        ch = getc(tmpn1);
        if (ch != EOF){
          fputc(ch, tmp);
        }

      }
      ch = '\0'; //обнуляем ch
      fl2 = 0;
    }


  }
  fclose(gg); //закрываем  все файлы, удаляем ненужные и переименовываем временный
  fclose(tmp);
  fclose(tmpn1);
  fclose(tmpn2);
  remove(filenamestr);
  system("del tmpn1.txt");
  system("del tmpn2.txt");
  rename("tmpbd.txt", filenamestr);
  //cat("bd.txt");

}



char** create(int m, int field, const char* filename) { //функция формирует массив из строк по полю
  if (field == 5) field = 0;
  char** newChar;
  FILE* fpf;
  char* str11;
  char ch;
  int n = 0;
  str11 = (char*)malloc(sizeof(char)); //выделяем память под один символ
  int i = 1;
  newChar = (char**)malloc(sizeof(char*)*m); //выделяем память для m элементов типа char*
  if ((fpf=fopen(filename, "rt"))==NULL) {
   printf ("Cannot open file.\n");
    exit(1);
  }
  for(int b = 0; b < m; b++) {
    newChar[b] = (char*)malloc(sizeof(char)); //и каждому выделяем по памяти для одного символа
  }

  for(int u = 0; u < m; u++) {
  n = 0;
  while (!feof(fpf) && !ferror(fpf)) //считываем только нужну строку (уже было выше)
  {
      if (ch == '\n') i += 1;
      ch = getc(fpf);
      if (ch != EOF && i % 5 == field) {
        if (ch == '\n') {str11[n] = 0; break;}
        str11[n] = ch;
        str11 = (char*)realloc(str11, sizeof(char)*(n+2));
        n++;
      }
  }

  newChar[u] = (char*)realloc(newChar[u], sizeof(str11[0])*(strlen(str11)+1)); //изменяем память под нужную
  strcpy(newChar[u], str11); //копируем строку в элемент нашего массива
  free(str11);//освобождаем память
  str11 = (char*)malloc(sizeof(char)); //и снова её выделяем
}
  fclose(fpf); //закрываем файл
  return newChar; //возвращаем этот массив из строк
}

void sort (int field, int m) {
  char **mass;
  if (count_lines("bd.txt") / 5 < m || m <= 0) {puts("\n\n"); puts("Not enough entries in database!!"); puts("\n\n"); return;} //проверка на существования номера записи
  mass = create (m, field, "bd.txt");
  if (field != 1 && field != 2 && field != 3 && field != 4 && field != 5) {puts("\n\n"); puts("ERROR!!"); puts("\n\n"); return;}//проверка на существования номера поля


  // Для всех элементов
  for (int i = 0; i < m - 1; i++)
  {
    for (int j = (m - 1); j > i; j--) // для всех элементов после i-ого
    {
      if (strcmp(mass[j - 1], mass[j]) > 0) // если текущий элемент меньше предыдущего //проверка лексикографическая, значит 22>1234, но в задании, к сожалению, не сказано по какому приницпу сортировать, поэтому оставим так
      {
        char* temp = mass[j - 1]; // меняем их местами
        mass[j - 1] = mass[j];
        mass[j] = temp;
        swap(j, j+1, "bd.txt"); //меняем местами записи в бд
      }
    }
  }




}
