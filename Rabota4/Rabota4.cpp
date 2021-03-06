// Rabota4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//1.Администратор гостиницы.
//Список всех номеров, которые подразделяются на классы(обычный класс, полулюкс, люкс, королевский номер), число мест.
//Программа показывает список номеров, которые уже заняты и список свободных номеров.
//Поселение гостей : выбор подходящего номера(при наличии свободных мест), регистрация, оформление квитанции.
//Отъезд : выбор всех постояльцев, отъезжающих сегодня, освобождение места или оформление задержки с выпиской 
//дополнительной квитанции.Возможность досрочного отъезда с перерасчетом.
//При заселении создается список постояльцев, в котором хранится информация : ФИО, паспортные данные,
//номер комнаты, дата приезда и выселения.
//Поиск постояльца по произвольному признаку.
//Программа рассчитывает стоимость проживания(количество суток * стоимость одних суток).


struct HotelN {
	int Nclass=0;			//1-обычный класс, 2-полулюкс, 3-люкс, 4-королевский номер
	int Nnumber=0;			//номер номера
	int Nnumbofpl=0;		//кол-во мест
	int cost=0;				//цена номера
	bool free=true;			//занят или нет
	int count = 0;			//Кол-во номеров
};

struct lodger {
	char name[50];
	char pasport[20];
	int Hnumber;
	int count=0;
	time_t z;
};

struct zap {
	lodger *cur=NULL;
	zap *next=NULL;
};

struct HotelN *mas;
struct zap *list=NULL;
int number;

int read();
void save(int a);
char *convert(int q);
void insert(lodger *p);
void add(lodger *p);
void display(int number);
void calculation(int number);


int main() 
{
	setlocale(LC_ALL, "RUS");

	bool done = false;
	char c,s[300];
	int a;
	time_t t;
	number = read();
	

	while (!done)
	{
		system("cls");
		lodger *temp = new lodger;
		HotelN *tt = new HotelN;
		bool d = false;
		display(number);
		printf("\nS-Показать список номеров\nR-Размещение нового посетителя\nV-Выписка постояльца\nQ)uit\n\n\n");
		c = _getch();
		switch (toupper(c))
		{
		case 'S':
			display(number);
			/*temp = list->cur;
			temp->count = 0;
			temp->Hnumber = 0;
			temp->z = NULL;
			save(number);*/
			break;

		case 'R':
			system("cls");
			char string[50];
			printf("Введите фамилию посетителя:\n");
			gets_s(string, 49);
			strcpy_s(temp->name,string);

			printf("Введите номер паспорта посетителя:\n");
			gets_s(string, 49);
			strcpy_s(temp->pasport, string);

			t = time(NULL);
			temp->z = t;
			while (!d)
			{
				display(number);

				printf("В какой номер разместить?\nQ)uit\n");
				gets_s(string, 49);

				char q = toupper(string[0]);
				if (q == 'Q') 
				{
					d = true;
					break;
				}
				a = atoi(string);
				tt = &mas[a - 1];
				if (!tt->free)
				{
					printf("Номер занят\n");
				}
				else
				{
					temp->Hnumber = a;
					tt->free = false;
					add(temp);
					save(number);
					d = true;
				}
			}

			break;

		case 'V':
			system("cls");
			while (!d)
			{
				display(number);
				printf("Из какого номера выселить посетителя:\nQ)uit\n");
				gets_s(string, 49);
				char q = toupper(string[0]);
				if (q == 'Q')
				{
					d = true;
					break;
				}
				calculation(atoi(string));
				save(number);
				getchar();
			}
			break;

		case 'Q':
			save(number);
			done = true;
			break;
		}
	}
return 0;
}



	int read()
	{
		FILE *ff;
		errno_t err;
		err = fopen_s(&ff, "HotelNumbers.dat", "rb");
		int p;
		if (err == 0)
		{
			HotelN *temp = new HotelN;
			fread(temp, sizeof(HotelN), 1, ff);
			p = temp->count;
			mas = new HotelN[p];
 			for (int i = 0; i < p; i++)
			{
				fread(&mas[i], sizeof(HotelN), 1, ff);
			}
		}
			else
			{
			printf("The file 'HotelNumbers.dat' was not opened\n");
			}
		fclose(ff);

		FILE *fff;
		err = fopen_s(&fff, "Lodgers.dat", "rb");
		if (err == 0) 
		{
		
			zap *tt = new zap;
			lodger *temp = new lodger;
			fread(temp, sizeof(lodger), 1, ff);
			tt->cur = temp;
			list = tt;
			int q = temp->count;

			for ( int i = 0; i < q; i++)	
			{
				lodger *temp = new lodger;
				fread(temp, sizeof(lodger), 1, fff);
				insert(temp);
			}
		}
		fclose(fff);
		return p;
	}



	void save(int a) 
	{
		FILE *ff;
		errno_t err;
		err = fopen_s(&ff, "HotelNumbers.dat", "wb");

		HotelN *temp = new HotelN;
		temp->count = a;
		fwrite(temp, sizeof(HotelN), 1, ff);

		for (int i = 0; i < a; i++) 
		{
			HotelN *temp = new HotelN;
			temp = &mas[i];
			fwrite(temp, sizeof(HotelN), 1, ff);
		}
		fclose(ff);

		if (list != nullptr) 
		{
			FILE *fff;
			errno_t err;
			err = fopen_s(&fff, "Lodgers.dat", "wb");

			zap *tt = new zap;
			lodger *temp = new lodger;
			tt = list;
			temp = tt->cur;
			
			fwrite(temp, sizeof(lodger), 1, ff);
			int p = temp->count;
			for (int i = 0; i < p; i++) 
			{
				tt = tt->next;
				temp = tt->cur;
				fwrite(temp, sizeof(lodger), 1, ff);
			}
			fclose(fff);
		}

	}



	char *convert(int q) 
	{
		char p[300];
		switch (q)
		{
		case 1:
			strcpy_s(p, "Королевский");
			return p;
			break;

		case 2:
			strcpy_s(p, "Люкс");
			return p;
			break;

		case 3:
			strcpy_s(p, "Полулюкс");
			return p;
			break;

		case 4:
			strcpy_s(p, "Обычный");
			return p;
			break;
		}

	}



	void insert(lodger *p) 
	{
		zap *temp = new zap;
		if (list->next == nullptr)
		{ 
			temp->cur = p;
			list->next = temp;
		}
		else
		{
			temp = list;

			while (temp->next != nullptr)
			temp = temp->next;

			zap *q = new zap;
			q->cur = p;
			temp->next = q;
		}
		
	}


	void add(lodger *p)
	{
		zap *temp = new zap;
		if (list->next == nullptr)
		{
			temp->cur = p;
			list->next = temp;
			list->cur->count++;
		}
		else
		{
			temp = list;

			while (temp->next != nullptr)
				temp = temp->next;

			zap *q = new zap;
			q->cur = p;
			temp->next = q;
			list->cur->count++;
		}

	}




	void display(int number)
	{
		system("cls");

		char s[300];
		for (int i = 0; i < number; i++)
		{
			struct HotelN* p;
			p = &mas[i];
			strcpy_s(s, convert(p->Nclass));
			printf("Номер %d:\n%s\nМест:%d\n", p->Nnumber, s, p->Nnumbofpl);
			if (p->free)
				printf("Свободен\n\n");
			else
				printf("Занят\n\n");
		}
		printf("Посетители отеля:\n\n");
		zap *tt = new zap;
		lodger *temp = new lodger;
		tt = list;

		if (list->cur->count==0)
			printf("Постояльцев нет\n\n");
		else 
		{
			int p = tt->cur->count;
			for (int i = 0; i < p; i++) 
			{
				tm *tminfo = new tm;
				char buffer[32];
				tt = tt->next;
				temp = tt->cur;
				localtime_s(tminfo, &temp->z);
				asctime_s(buffer, 32, tminfo);
				printf("Постоялец: %s\nПаспортные данные: %s\nДата заселения: %s\n", temp->name, temp->pasport, buffer);
				printf("Проживает в номере %d \n\n", temp->Hnumber);
			}
		}

		
	}


	void calculation(int number) 
	{
		HotelN *nomer = &mas[number - 1];
		zap *t = list->next;
		lodger *temp = t->cur;
		zap *cur = t;
		while (!temp->Hnumber==number)
		{
			zap *cur = t;
			t = t->next;
			temp = t->cur;
		}

		cur->next = t->next;
		nomer->free = true;
		time_t tim = time(NULL);
		tim = tim - temp->z;
		int cost =(int)ceil( ((double)tim)/86400)*(nomer->cost);
		printf("Постоялец %s выселен\n",temp->name);
		printf("К оплате за проживание %d", cost);
		list->cur->count--;
		free(t);
	}



//int main()   //была использована для добавления номеров
//{
//	setlocale(LC_ALL, "RUS");
//
//	//1-королевский(2 места), 2-люкс(2 места), 3 - полулюкс(3 места), 4 -обычный(1 место)
//
//	char string[10];
//	printf("Введите количество номеров в гостинице\n");
//	int number=atoi(gets_s(string, 10));
//
//	FILE *ff;
//	errno_t err;
//	err = fopen_s(&ff, "HotelNumbers.dat", "ab");
//
//	if (err == 0)
//	{
//		printf("The file 'HotelNumbers.dat' was opened\n");
//	}
//	else
//	{
//		printf("The file 'HotelNumbers.dat' was not opened\n");
//	}
//
//	HotelN *temp = new HotelN;
//	temp->count = number;
//	fwrite(temp, sizeof(HotelN), 1, ff);
//
//	for (int i = 0; i < number; i++) 
//	{
//		HotelN *temp = new HotelN;
//		printf("Введите класс %d номера\n", i+1 );
//		int n = atoi(gets_s(string, 10));
//		temp->Nclass = n;
//
//		printf("Введите количество мест %d номера\n", i+1);
//		n = atoi(gets_s(string, 100));
//		temp->Nnumbofpl = n;
//
//		printf("Введите стоимлсть %d номера\n", i + 1);
//		n = atoi(gets_s(string, 10));
//		temp->cost = n;
//
//		temp->Nnumber = i + 1;
//		
//		fwrite(temp,sizeof(HotelN),1,ff);
//	}
//	fclose(ff);
//
//    return 0;
//}

