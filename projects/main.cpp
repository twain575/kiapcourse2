#include <stdlib.h> //для очистки экрана в функции cls
#include <iostream>
using namespace std;
 
#define SIZE 1000 //размер библиотеки, не более SIZE книг может быть
 
void cls()
{
  if (system("clear")) system( "cls" ); //очистка экрана в linux и затем в windows
}
 
class lib
{
  int num=0,id[SIZE],hand[SIZE]; //количество книг, массив id книг, массив книг на руках
  string author[SIZE], title[SIZE]; //массив авторов, массив названий
 
  bool libis(); //возвращает булеву пееменную и отображает сообщение если книг в библиотеке нет совсем
 
  public:
  bool is(int n); //поиск карточки книги по id
  int qnty(); //возвращает значение
  void show(int n); //отображение карточки книги
  void showall(); //отображение все карточки книги
  int store(string auth, string tit, int hd); //добавление карточки книги
  void del(int n); //удаление карточки книги
  void give(int n); //книга отдана на руки
  void bring(int n); //книга возвращена в библиотеку
};
 
bool lib::libis()
{
  if (num==0) {
     cout << "Книг в библиотеке нет!\n";
     return false;
  }
  return true;
}
 
bool lib::is(int n)
{
  int i;
  for (i=0;i<num;i++){
      if (i==n) return true;
  }
  return false;
}
 
int lib::qnty()
{
  if ((num-1) >= 0 ) return num-1;
  else return 0;
}
 
void lib::show(int n)
{
  if ( (n>=0) && (n<num) ) {
     cout << "id: " << id[n] << " Автор: " << author[n] << endl;
     cout << "Название: " << title[n] << endl;
     cout << "Выдано: " << hand[n] << endl;
     return;
 
  } else cout << "Книги с таким id не обнаружено. id: " << n << endl;
}
 
void lib::showall()
{
  int i;
  libis();
  for (i=0;i<num;i++) {
     cout << "id: " << id[i] << " Автор: " << author[i] << endl;
     cout << "Название: " << title[i] << endl;
  }
}
 
int lib::store(string auth, string tit, int hd)
{
  if (num == SIZE) {
     cout << "Библиотека переполнена! Количество книг: " << num << endl;
     cout << "Нельзя добавить больше книг\n";
     return -1;
  }
  id[num] = num;
  cout << "id: " << id[num] << endl;
  author[num] = auth;
  title[num] = tit;
  hand[num] = hd;
  num = num+1;
  return id[num];
}
 
void lib::del(int n)
{
  int i,j=0;
  libis();
  if (!is(n)) {
     cout << "Книги с таким id не обнаружено. id: " << n << endl;
     return;
  }
  for (i=0;i<num;i++) {
      if (i==n) {
          continue;
      } else {
         id[j] = j;
         author[j] = author[i];
         title[j] = title[i];
         hand[j] = hand[i];
         j++;
      }
  }
  num--;
}
 
void lib::give(int n)
{
  libis();
  is(n);
  hand[n]++;
}
 
void lib::bring(int n)
{
  libis();
  is(n);
  if (hand[n] == 0) {
     cout << "Не было информации о том, что книга была выдана";
  } else hand[n]--;
}
 
void mainscreen()
{
	setlocale(LC_ALL, "Rus");
  cls();
  cout << "Программа библиотека\n";
  cout << "1 - Количество книг\n";
  cout << "2 - Показать книги\n";
  cout << "3 - Добавить книгу\n";
  cout << "4 - Удалить книгу\n";
  cout << "5 - Выдать книгу\n";
  cout << "6 - Принять книгу\n";
  cout << "9 - Выход\n";
 
}
 
int main()
{
  int i,j,k,hand,command;
  string author;
  string title;
  lib mylib;
 
  mylib.store("Толстой","Казаки",1);
  mylib.store("Некрасов","Сборник стихов",0);
  mylib.store("Маяковский","Стихи",0);
  mylib.store("Карамзин","История государства",0);
  mylib.store("А.С.Пушкин","Стихи",0);
 
 
  while(1) {
     mainscreen();
     cout << "Номер меню: ";
     cin >> command;
     switch (command) {
 
     case 1:
         cout << "Количество книг в библиотеке: " << mylib.qnty() << endl;;
         break;
 
     case 2:
         if (mylib.qnty() <= 0) {
             cout << "В библиотеке нет книг.\n";
             break;
         }
         cls();
         cout << "Книги библиотеки\n";
         cout << "Введите число книг для постраничного отображения на экране\n";
         cin >> k;
         j=0;
         do {
             for (i=0;i<k;i++) {
                 mylib.show(j);
                 cout << endl;
                 j++;
                 if (j>mylib.qnty()) {
                     cout << "Это все книги, которые есть в библиотеке\n";
                     break;
                 }
             }
             if (j<=mylib.qnty()) {
                 cout << "Для отображения следующих книг введите любое число, кроме 0, и нажмите Ввод \n";
                 cout << "Для завершения отображения книг введите 0 и нажмите Ввод ";
                 cin >> i;
                 cls();
             }
         } while ( ( j<=mylib.qnty() ) && (i != 0) );
         break;
 
     case 3:
         cls();
         cout << "Добавление книги\n";
         cout << "Введите автора (латиницей без пробелов): ";
         cin >> author;
         cout << "Введите название (латиницей без пробелов): ";
         cin >> title;
         cout << "Введите колчество выданны на руки экземпляров: ";
         cin >> hand;
         mylib.store(author, title, hand);
         cout << "Книга добавлена:\n";
         mylib.show(mylib.qnty());
         break;
 
     case 4:
         cls();
         cout << "Удаление книги\n";
         cout << "Введите id книги для удаления: ";
         cin >> i;
         if (mylib.is(i)) {
             cout << "Вы собираетесь удалить книгу: ";
             mylib.show(i);
             cout << "Введите 1 для удаления или любое другое число для отмены: ";
             cin >> k;
             if (k==1) {
                 mylib.del(i);
                 cout << "Книга удалена\n";
             }
         } else cout << "Книги с таким id не найдено. id: " << i << endl;
         break;
     case 5:
         cls();
         cout << "Выдача книги\n";
         cout << "Введите id книги для выдачи: ";
         cin >> i;
         if (mylib.is(i)) {
             mylib.give(i);
             cout << "Книга выдана\n";
             mylib.show(i);
         } else cout << "Книги с таким id не найдено. id: " << i << endl;
         break;
     case 6:
         cls();
         cout << "Приём книги\n";
         cout << "Введите id принятой книги: ";
         cin >> i;
         if (mylib.is(i)) {
             mylib.bring(i);
             cout << "Книга принята\n";
             mylib.show(i);
         } else cout << "Книги с таким id не найдено. id: " << i << endl;
         break;
     case 9: return 0;
         break;
     }
     cout<<"Для продолжения работы введите любое число и нажмите Ввод ";
     cin >> k;
  }
  return 0;
}
