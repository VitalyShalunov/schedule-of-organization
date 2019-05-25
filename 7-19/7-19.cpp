// text_console.cpp: определяет точку входа для консольного приложения.
//
//#define _WIN32_WINNT 0x0500//for windows 7 =)
#include "stdafx.h"
#include <windows.h>
#include <conio.h>
//#include <WinUser.h>
//#include <afxwin.h>


struct Root
{
	char post[25];
	int kol_ed;
	int kol_vac;
	Root *left, *right;
} *root;

struct list
{
	char name_division[40];
	char post[25];
	//char specialite[20];
	//char education[20];
	int salary;
	char FIO[60];
	list *next; // указатель на следующий элемент
}*first;

struct forvac
{
	char name_division[40];
	char post[25];
	int salary;
}vacans;

struct schedule //штатное расписание
{
	char name_division[40];
	char post[25];
	int salary;
	char FIO[60];
} sched;
struct requirements //квалификационные требования
{
	char name_division[40];
	char post[25];
	char specialite[20];
	char education[20];
	int experience;
} req;
int count1 = 0, count2 = 0;
FILE *ras, *treb, *vac, *sotrudniki;
char sym; int j1 = 0, j2 = 0,j3=0;

int input1()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	ras = fopen("schedule.dat", "rb+");
	vac = fopen("vacancy.dat", "ab+");
	sotrudniki = fopen("sotrudniki.dat", "ab+");
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	if (ras)
	{
		printf("Файл 'Штатное расписание' существует выберете действия: \n");
		printf("1 - создать новый файл \n2 - добавить данные в существующий файл \n0 - выйти из операции ввода \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		fflush(stdin);
		if (j2 != 0)
		{
			while (getchar() != '\n');

		}
		j2++; j1++;
		sym = getchar();
		printf("\n");
		switch (sym)
		{
		case '1':ras = fopen("schedule.dat", "wb"); vac = fopen("vacancy.dat", "wb"); break;
		case '2':ras = fopen("schedule.dat", "ab"); 	//fclose(vac); vac = fopen("vacancy.dat", "a+b");
			break;
		case '0':return 0;
		}
	}
	else
	{
		ras = fopen("schedule.dat", "wb");
		vac = fopen("vacancy.dat", "wb");
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Следует заполнить файл 'Штатное расписание' \n");
	}

	do
	{

		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите название подразделения: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		//fflush(stdin);
		while (getchar() != '\n');
		gets_s(sched.name_division);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Должность: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(sched.post);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Оклад: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		scanf("%d", &sched.salary);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите имя сотрудника, если место не занято, то поставьте '-': \n");
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(sched.FIO);
		char ysl[] = "-";
		fflush(stdin);
		if (strcmp(sched.FIO, ysl) == 0) {
			//fwrite(&sched, sizeof(sched), 1, vac);
			if (fwrite(&sched, sizeof(sched), 1, vac));
			
		}
		fwrite(&sched, sizeof(sched), 1, ras);
		fwrite(&sched, sizeof(sched), 1, sotrudniki);

		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Продолжить ввод? [Д/Н] \n");
		//while (getchar() != '\n'); 
		count1++;
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		sym = getchar();
	} while (sym == -28 || sym == -60);
	fclose(ras); fclose(vac); fclose(sotrudniki); return count1;

}
void view1()
{
	system("cls");
	//system("color F0");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));


	ras = fopen("schedule.dat", "rb");
	if (!ras)
	{
		printf("Файла не существует.\n");
		system("pause");
	}
	else
	{
		count1 = 0;
		printf("\nШтатное расписание: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		printf("_____________________________________________________________________________________________________________\n");
		printf("Название подразделения              |   Должность          |     Оклад  |  ФИО сотрудника \n");
		printf("____________________________________________________________________________________________________________ \n");
		while (fread(&sched, sizeof(sched), 1, ras))
		{
			printf("%-40s", sched.name_division);
			printf("%-25s", sched.post);
			printf("%-10d", sched.salary);
			if (strcmp(sched.FIO,"-")!=0)
			printf("%16s", sched.FIO);
			else printf("%-20s", sched.FIO);
			printf("\n");
			count1++;
		}
		fclose(ras);
		if (!count1) printf("Нет данных \n");
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		system("pause");
	}
}

int input2()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	treb = fopen("requirements.dat", "rb+");
	if (ras)
	{
		printf("Файл 'Квалификационные требования' существует выберете действия: \n");
		printf("1 - создать новый файл \n2 - добавить данные в существующий файл \n0 - выйти из операции ввода \n");
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		sym = getchar();
		switch (sym)
		{
		case '1':treb = fopen("requirements.dat", "wb"); break;
		case '2':treb = fopen("requirements.dat", "ab"); break;
		case '0':return 0;
		}
	}
	else
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Следует заполнить файл 'Квалификационные требования' \n");
		treb = fopen("requirements.dat", "wb");
	}
	do
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите название подразделения: \n");
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(req.name_division);
		fflush(stdin);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Должность: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(req.post);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Специальность: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(req.specialite);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Образование: Высшее|Среднее \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(req.education);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Стаж работы: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		scanf("%d", &req.experience);
		fwrite(&req, sizeof(req), 1, treb);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Продолжить ввод? [Д/Н] \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		while (getchar() != '\n');
		count2++;
		sym = getchar();
	} while (sym == -28 || sym == -60);
	fclose(treb); return count2;
}
void view2()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	treb = fopen("requirements.dat", "rb");
	if (!treb)
	{
		printf("Файла не существует\n");
		system("pause");
	}
	else
	{

		int count2 = 0;
		printf("Квалификационне требования: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		printf("_________________________________________________________________________________________________________________\n");
		printf("Название подразделения              |   Должность          |     Специальность  |    Образование | Опыт работы \n");
		printf("_________________________________________________________________________________________________________________\n");
		while (fread(&req, sizeof(req), 1, treb))
		{
			printf("%-40s", req.name_division);
			printf("%-25s", req.post);
			printf("%-20s", req.specialite);
			printf("%-20s", req.education);
			printf("%-4d", req.experience);
			printf("\n");
			count2++;
		}

		fclose(treb);
		if (!count2) printf("Нет данных \n");
		system("pause");
	}
}

void request1()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	do
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите Вашу специальность: \n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		char spec[20]; char tspec[20];
		fflush(stdin);
		if (j1 != 0)
		{
			while (getchar() != '\n');

		}
		j1++;
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(spec);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите Ваше образование: Высшее|Среднее \n");
		char obr[20]; char tobr[20];
		fflush(stdin);
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(obr);
		int stag; int tstag;
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите Ваш стаж работы:\n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		scanf("%d", &stag);
		vac = fopen("vacancy.dat", "rb+");
		treb = fopen("requirements.dat", "rb+");
		int prov = 0;
		char div1[40], div2[40];
		char post1[25], post2[25];
		while (fread(&sched.name_division, sizeof(sched.name_division), 1, vac))
		{

			fread(&sched.post, sizeof(sched.post), 1, vac);
			fread(&sched.salary, sizeof(sched.salary), 1, vac);
			//fread(&sched.FIO, sizeof(sched.FIO), 1, vac);
			//printf("Из вакансий: %s     %s \n", sched.name_division, sched.post);
			strcpy(div1, sched.name_division);
			strcpy(post1, sched.post);
			fseek(treb, 0, 0);
			while (fread(&req, sizeof(req), 1, treb))
			{

				//printf("Из требований: %s      %s \n", req.name_division, req.post);
				if (strcmp(req.name_division, div1) == 0)
				{
					strcpy(div2, req.name_division);
					int kol = 0;
					for (int i = 0; i < strlen(div1); i++)
						if (*(div1 + i) == *(div2 + i)) kol++;
						else i = strlen(div1);
						if (kol == strlen(div1))
						{
							strcpy(post2, req.post);
							if (strcmp(post1, post2) == 0)
							{
								kol = 0;
								for (int i = 0; i < strlen(post1); i++)
									if (*(post1 + i) == *(post2 + i)) kol++; else i = strlen(post1);
								if (kol == strlen(post1))
								{
									strcpy(tspec, req.specialite);
									if (strcmp(tspec, spec) == 0)
									{
										kol = 0;
										for (int i = 0; i < strlen(spec); i++)
											if (*(tspec + i) == *(spec + i)) kol++; else i = strlen(spec);
										if (kol == strlen(spec))
										{
											strcpy(tobr, req.education);
											if (strcmp(tobr, obr) == 0)
											{
												kol = 0;
												for (int i = 0; i < strlen(tobr); i++)
													if (*(tobr + i) == *(obr + i)) kol++; else i = strlen(obr);
												if (kol == strlen(obr))
												{
													tstag = req.experience;
													if (stag >= tstag)
													{
														prov++;
														SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
														printf("\nВы можете работать на должности:%-25s", req.post);
														printf("в подразделении: %-40s \n\n", req.name_division);
													}
												}
											}

										}

									}
								}
							}
						}
				}
			}
		}
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		if (prov == 0) printf("Вакансий по Вашим данным не найдено \n");
		printf("Может у Вас есть ещё специальность, хотите проверить вакантные места заново? [Д|Н] \n");
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		sym = getchar();
		fclose(treb);
		fclose(vac);
	} while (sym == -28 || sym == -60);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	system("pause");
}

void request2()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	do
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите, какой бы оклад Вы хотели иметь: \n");
		int okl;
		j2++;
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		scanf("%d", &okl);
		vac = fopen("vacancy.dat", "rb+");
		ras = fopen("schedule.dat", "rb+");
		int prov = 0;
		char div1[40], div2[40];
		char post1[25], post2[25];
		while (fread(&sched.name_division, sizeof(sched.name_division), 1, vac))
		{

			fread(&sched.post, sizeof(sched.post), 1, vac);
			fread(&sched.salary, sizeof(sched.salary), 1, vac);
		//	fread(&sched.FIO, sizeof(sched.FIO), 1, vac);
			//printf("Из вакансий: %s     %s \n", sched.name_division, sched.post);
			strcpy(div1, sched.name_division);
			strcpy(post1, sched.post);
			fseek(ras, 0, 0);
			while (fread(&sched, sizeof(sched), 1, ras))
			{
				//	printf("Из требований: %s      %s \n", req.name_division, req.post);
				if (strcmp(sched.name_division, div1) == 0)
				{
					strcpy(div2, sched.name_division);
					int kol = 0;
					for (int i = 0; i < strlen(div1); i++)
						if (*(div1 + i) == *(div2 + i)) kol++;
						else i = strlen(div1);
						if (kol == strlen(div1))
						{
							strcpy(post2, sched.post);
							if (strcmp(post1, post2) == 0)
							{
								kol = 0;
								for (int i = 0; i < strlen(post1); i++)
									if (*(post1 + i) == *(post2 + i)) kol++; else i = strlen(post1);
								if (kol == strlen(post1))
								{
									if (sched.salary >= okl)
									{
										SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
										printf("Должность: %-25s в подразделении: %-40s \n", sched.post, sched.name_division);
										prov++;
									}
								}
							}
						}
				}
			}
		}
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		if (prov == 0) printf("Вакансий превышающий заданный оклад не найдено \n");
		printf("\nХотите ещё узнать, какие вакантные должности превышают некоторый оклад? [Д|Н] \n");
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		sym = getchar();

		fclose(vac);
		fclose(ras);
	} while (sym == -28 || sym == -60);
}

void request3()
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	do
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Какую должность Вы бы хотели проверить на вакантность? \n");
		char svob[25];
		if (j3 != 0||j1!=0||j2!=0)
		{
			while (getchar() != '\n');

		}
		j3++;
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(svob);
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("В каком подразделении? \n");
		char podr[40];
		//while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(podr);
		vac = fopen("vacancy.dat", "rb+");

		//viewvac();
		if (!vac) {
			SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
			printf("файл 'vac'не открылся \n");
		}
		int i;
		fflush(stdin);
		fseek(vac, 0, 0);
		char post[25];
		char division[40];
		int prov = 0;

		while (fread(&sched.name_division, sizeof(sched.name_division), 1, vac))
		{
			fread(&sched.post, sizeof(sched.post), 1, vac);
			fread(&sched.salary, sizeof(sched.salary), 1, vac);
			//fread(&sched.FIO, sizeof(sched.FIO), 1, vac);
			//printf("%s		 ", sched.name_division);
			if (strcmp(sched.name_division, podr) == 0)
			{
				int kol = 0;
				strcpy(division, sched.name_division);
				for (i = 0; i < strlen(division); i++)
					if (*(division + i) == *(podr + i)) kol++;
					else i = strlen(division);
					if (kol == strlen(division))
					{

						//printf("%s \n", sched.post);
						//printf("%-20s",sched.post); printf("    "); printf("%-20s \n",svob);

						if (strcmp(sched.post, svob) == 0)
						{
							int kol = 0;
							strcpy(post, sched.post);
							for (i = 0; i < strlen(post); i++)
								if (*(post + i) == *(svob + i)) kol++;
							if (kol == strlen(post))
							{
								SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
								printf("\nДанная должность является вакантной в данном подразделении \n");
								prov++;
								fseek(vac, 0, 2);
							}
						}
					}
			}
		}
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		if (prov == 0) printf("\nДанная должность не является вакантной \n");
		printf("\nХотите проверить ещё какую-нибудь должность? [Д|Н] \n");
		//while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		sym = getchar();

	} while (sym == -28 || sym == -60);
	fclose(vac);
}
int kolsched()
{
	int kol1 = 0;
	sotrudniki = fopen("sotrudniki.dat", "rb");
	if (!sotrudniki)
	{
		printf("Файла не существует.\n");
		system("pause");
	}
	else
	{
		while (fread(&sched, sizeof(sched), 1, sotrudniki))
		{
			kol1++;
		}
	}
		fclose(sotrudniki);
		return kol1;
}
void sortbybinvstavkami()
{
	system("cls");
	int kol1=kolsched();
	schedule *strin = new schedule[kol1];
	sotrudniki = fopen("sotrudniki.dat", "rb");
	int i = 0;
	if (!sotrudniki)
	{
		printf("Файла не существует.\n");
		system("pause");
	}
	else {
		/*while (fread(&strin[i], sizeof(sched), 1, sotrudniki))
		{
			i++;
		}
		*/
		fread(strin, sizeof(sched), kol1, sotrudniki);
	}
	
	int count = kol1;

	char buf_name_division[40];
	char buf_post[25];
	int buf_salary;
	char buf_FIO[60];

	for (int i = 1; i < count; i++)
	{
		if (strcmp(strin[i].FIO, strin[i - 1].FIO) < 0)
		{
			strcpy(buf_name_division, strin[i].name_division);
			strcpy(buf_post, strin[i].post);
			buf_salary = strin[i].salary;
			strcpy(buf_FIO, strin[i].FIO);

			int left = 0;
			int right = i - 1;
			while (left <= right)
			{
				int mid = (left + right) / 2;
				if (strcmp(buf_FIO, strin[mid].FIO) > 0)

					left = mid + 1;
				else right = mid - 1;
			}
			for (int j = i - 1; j > right; j--) {
				strcpy(strin[j + 1].name_division, strin[j].name_division);
				strcpy(strin[j + 1].post, strin[j].post);
				strin[j + 1].salary = strin[j].salary;
				strcpy(strin[j+1].FIO, strin[j].FIO);
			}
			strcpy(strin[right + 1].name_division, buf_name_division);
			strcpy(strin[right + 1].post, buf_post);
			strin[right + 1].salary = buf_salary;
			strcpy(strin[right + 1].FIO, buf_FIO);
		}
	}
	printf("\nШтатное расписание: \n");
	printf("_____________________________________________________________________________________________________________\n");
	printf("Название подразделения              |   Должность          |     Оклад  |  ФИО сотрудника \n");
	printf("____________________________________________________________________________________________________________ \n");
	for (i = 0; i < kol1; i++)
	{
		printf("%-40s", strin[i].name_division);
		printf("%-25s", strin[i].post);
		printf("%-10d", strin[i].salary);
		printf("%-60s", strin[i].FIO);
		printf("\n");

	}
	fflush(stdin);
	system("pause");
	delete[] strin;
	fclose(sotrudniki);


}
int kolvac()
{
	vac=fopen("vacancy.dat", "rb+");
	int kol2 = 0;
	if (!vac)
	{
		printf("Файла не существует.\n");
		system("pause");
	}
	else
	{
		while (fread(&sched.name_division, sizeof(sched.name_division), 1,vac))
		{
			fread(&sched.post, sizeof(sched.post), 1, vac);
			fread(&sched.salary, sizeof(sched.salary), 1, vac);
			kol2++;
		}
	}

	fclose(vac);
	return kol2;
}
void sortbychel()
{
	system("cls");
	int kol2 = kolvac();
	schedule *sortch = new schedule[kol2];
	vac = fopen("vacancy.dat", "rb");
	int i = 0;
	int count = kol2;
	if (!vac)
	{
		printf("Файла не существует.\n");
		system("pause");
	}
	else {
		//while (fread(&sortch[i], sizeof(sched.name_division)+sizeof(sched.post)+sizeof(sched.salary), 1, vac))
		//while (fread(&sortch[i], sizeof(sched), 1, vac))
		while (fread(&sched.name_division, sizeof(sched.name_division), 1, vac))
		{
			fread(&sched.post, sizeof(sched.post), 1, vac);
			fread(&sched.salary, sizeof(sched.salary), 1, vac);
			
			strcpy(sortch[i].name_division, sched.name_division);
			strcpy(sortch[i].post, sched.post);
			sortch[i].salary = sched.salary;
			
			{
				i++;
			}
		}
		char buf_name_division[40];
		char buf_post[25];
		int buf_salary;
		int top = 0;
		int down = count - 1;
		int sorted = 0;
		while (top < down&&!sorted)
		{
			sorted = 1;
			for (int j = down; j > top; j--)
			{
				if (sortch[j].salary > sortch[j - 1].salary)
				{
					strcpy(buf_name_division, sortch[j - 1].name_division);
					strcpy(buf_post, sortch[j - 1].post);
					buf_salary = sortch[j - 1].salary;
				

					strcpy(sortch[j - 1].name_division, sortch[j].name_division);
					strcpy(sortch[j - 1].post, sortch[j].post);
					sortch[j - 1].salary = sortch[j].salary;

					strcpy(sortch[j].name_division, buf_name_division);
					strcpy(sortch[j].post, buf_post);
					sortch[j].salary = buf_salary;
				
					sorted = 0;
				}
			}
			top++;
			if (!sorted)
			{
				sorted = 1;
				for (int j = top; j < down; j++)
				{
					if (sortch[j].salary < sortch[j + 1].salary)
					{
						strcpy(buf_name_division, sortch[j].name_division);
						strcpy(buf_post, sortch[j].post);
						buf_salary = sortch[j].salary;

						strcpy(sortch[j].name_division, sortch[j+1].name_division);
						strcpy(sortch[j].post, sortch[j+1].post);
						sortch[j].salary = sortch[j+1].salary;

						strcpy(sortch[j+1].name_division, buf_name_division);
						strcpy(sortch[j+1].post, buf_post);
						sortch[j+1].salary = buf_salary;
						sorted = 0;
					}
				}
				down--;
			}

		}
	}
	printf("_____________________________________________________________________________________\n");
	printf("Название подразделения              |   Должность          |     Оклад   \n");
	printf("_____________________________________________________________________________________\n");
	for (i = 0; i < kol2; i++)
	{
		printf("%-40s", sortch[i].name_division);
		printf("%-25s", sortch[i].post);
		printf("%-10d", sortch[i].salary);
		printf("\n");

	}
	system("pause");
	fclose(vac);

}
void readvac()
{
	vac = fopen("vacancy.dat", "wb+");
	ras = fopen("schedule.dat", "rb+");
	while (fread(&sched, sizeof(sched), 1, ras))
	{
		if (strcmp(sched.FIO, "-") == 0)
		{
			fwrite(&sched.name_division, sizeof(sched.name_division), 1, vac);
			fwrite(&sched.post, sizeof(sched.post), 1, vac);
			fwrite(&sched.salary, sizeof(sched.salary), 1, vac);
		}
	}
	fclose(ras);
	fclose(vac);
}

void readrasp()
{
	sotrudniki = fopen("sotrudniki.dat", "rb+");
	if (!sotrudniki) sotrudniki = fopen("sotrudniki.dat", "wb");
	ras = fopen("schedule.dat", "rb+");
	while (fread(&sched, sizeof(sched), 1, ras))
	{
		if (strcmp(sched.FIO, "-") != 0)
			fwrite(&sched, sizeof(sched), 1, sotrudniki);
	}
	fclose(sotrudniki);
	fclose(ras);
}
void showvac()
{
	vac = fopen("vacancy.dat", "rb+");
	while (fread(&sched.name_division, sizeof(sched.name_division), 1, vac))
	{
		fread(&sched.post, sizeof(sched.post), 1, vac);
		fread(&sched.salary, sizeof(sched.salary), 1, vac);
		printf("%-40s", sched.name_division);
		printf("%-25s", sched.post);
		printf("%-10d", sched.salary);
		
		printf("\n");
	}
	fclose(vac);
	system("pause");
}

list *createlist()
{
	
	ras = fopen("schedule.dat", "rb+");
	
	int k = 0;
	
	while (fread(&sched, sizeof(sched), 1, ras))
	{
		int posl = 0;
		list *tek, *pred, *newel;
		newel = new list;
		(*newel).next = NULL;
		strcpy(newel->name_division, sched.name_division);
		strcpy(newel->post, sched.post);
		newel->salary = sched.salary;
		strcpy(newel->FIO, sched.FIO);
		
		tek = first;
		pred = NULL;
		if (k != 0) {
			
				while (strcmp(tek->name_division, newel->name_division) < 0)
				{
					pred = tek;
					tek = tek->next;
					if (tek == NULL)
					{
						tek = newel;
						posl = 1;
						goto sud;
					//	tek->next = NULL;
						break;
					}
				}
				if ((strcmp(tek->name_division, newel->name_division) == 0) && (tek->next == NULL))
				{
					pred = tek;
					//tek = tek->next;
					tek = newel;
					posl = 1;
					tek->next = NULL;
				}
		
				sud:
			if (pred == NULL)
				first = newel;
			else pred->next = newel;
			if (posl==0)
			newel->next = tek;
			else posl = 0;

		}
		else {
			if (tek==NULL)
			tek=newel;
			tek->next = NULL;
			first = newel;
			k++;
	}
		

	}

	fclose(ras);
	return first;
}

void listprint(list *lst)
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	printf("Список штатного расписания: \n\n");
	printf("_____________________________________________________________________________________________________________\n");
	printf("Название подразделения              |   Должность          |     Оклад  |  ФИО сотрудника \n");
	printf("____________________________________________________________________________________________________________ \n");
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	struct list *p;
	p = lst;
	do {
		

		printf("%-40s", p->name_division);
		printf("%-25s", p->post);
		printf("%-10d", p->salary);
		if (strcmp(p->FIO, "-") != 0)
			printf("%16s", p->FIO);
		else printf("%-20s", p->FIO);
		//printf("%-4d", p->experience);
		printf("\n");
		p = p->next; // переход к следующему узлу
	} while (p != NULL);
	SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
	system("pause");
	char sym;
	printf("\nХотите просмотреть информацию по конкретному поздразделению?\nОтветьте [Д]/[Н]\n");
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	//while (getchar() != '\n');
	sym=getchar();
	if ((sym == -28 || sym == -60))
	do{
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		printf("Введите название подразделения:\n");
		char searchdivision[40];
		while (getchar() != '\n');
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		gets_s(searchdivision);
		printf("\n");
		p = lst;
		SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
		do {
			if (strcmp(p->name_division, searchdivision) == 0) {
				printf("%-40s", p->name_division);
				printf("%-25s", p->post);
				printf("%-10d", p->salary);
				if (strcmp(p->FIO, "-") != 0)
					printf("%16s", p->FIO);
				else printf("%-20s", p->FIO);
				printf("\n");
			}
			p = p->next; // переход к следующему узлу
		} while (p != NULL);
		printf("\nПродолжить поиск?\n[Д]/[Н]\n");
		SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
		sym = getchar();
	} while (sym == -28 || sym == -60);
	j2++;
}


void add_tree(Root **curr, char *post,char *FIO)
{
	if (!(*curr))
	{
		*curr = new Root;
		(*curr)->kol_ed = 1;
		(*curr)->kol_vac = 0;
		strcpy((*curr)->post, post);
		if (strcmp(FIO, "-") == 0)
			(*curr)->kol_vac = 1;
		(*curr)->left = NULL;
		(*curr)->right = NULL;
	}
	else
		if (strcmp(post, (*curr)->post) < 0)
			add_tree(&((*curr)->left), post,FIO);
		else if (strcmp(post, (*curr)->post) > 0)
			add_tree(&((*curr)->right), post,FIO);
		else {
			(*curr)->kol_ed++;
			if (strcmp(FIO, "-") == 0)
				(*curr)->kol_vac++;
		}
}

void create_tree(Root **root)
{
	struct list *p;
	p = first;
	do {
		add_tree(&(*root), p->post,p->FIO);
		p = p->next; // переход к следующему узлу
	} while (p != NULL);

}

void view_tree(Root *root)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((9) | 3));
	if (root)
	{
		view_tree(root->left);
		printf("%-25s %-15d %15d\n", root->post,root->kol_ed,root->kol_vac);
		view_tree(root->right);
	}
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	//readrasp();
	readvac();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//showvac();
	// получение информации о консольном окне
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hcon = GetConsoleWindow();

	// программная установка консольного шрифта для отображения русского текста
	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(hConsole, false, &cfi);
	COORD fs = GetConsoleFontSize(hConsole, cfi.nFont);
	PCONSOLE_FONT_INFOEX ccf = new CONSOLE_FONT_INFOEX;
	(*ccf).dwFontSize.X = 12;
	(*ccf).dwFontSize.Y = 20;
	(*ccf).nFont = 11;
	(*ccf).cbSize = sizeof(CONSOLE_FONT_INFOEX);
	ccf->FontWeight = 400;
	lstrcpyW((*ccf).FaceName, L"Lucida Console");
	(*ccf).FontFamily = FF_DONTCARE;
	bool b = SetCurrentConsoleFontEx(hConsole, false, ccf);
	fs = GetConsoleFontSize(hConsole, cfi.nFont);

	// установка кодировки 1251 для отображения русского текста
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n = 11;			//кол-во пунктов меню
	COORD position[11];
	int punkt = 0;
	char names[11][100] = { "Ввод данных", "Просмотр 'Штатного расписания'","Просмотр 'Квалификационных требований'", "Вакансии с учётом вашей специальности", "Вакансии, которые превышают некоторой оклад", "Проверка должности на вакантность","Сортировка в алфавитном порядке сотрудников организации","Вакантные места по уменьшению оклада","Список","Дерево","Выход" };
	do
	{
		int xmax, ymax;

		// получение параметров окна 
		PCONSOLE_SCREEN_BUFFER_INFO pwi = new CONSOLE_SCREEN_BUFFER_INFO;
		PWINDOWINFO pgwi = new WINDOWINFO;
		GetConsoleScreenBufferInfo(hConsole, pwi);
		GetWindowInfo(hcon, pgwi);
		xmax = pwi->dwSize.X;
		ymax = pwi->dwSize.Y;

		int y0 = 7;
		for (int i = 0; i < n; i++)
		{
			position[i].X = (xmax - strlen(names[i])) / 2;
			position[i].Y = y0 + i;
		}
		SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
		system("cls");			// очистка окна
		char title[] = "Компания";
		COORD pos;
		pos.X = (xmax - strlen(title)) / 2;
		pos.Y = 5;
		SetConsoleCursorPosition(hConsole, pos);
		puts(title);
		for (int i = 0; i < 11; i++)
		{
			SetConsoleCursorPosition(hConsole, position[i]);
			puts(names[i]);
		}
		SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
		SetConsoleCursorPosition(hConsole, position[punkt]);	// выделение текущего пункта ярким цветом
		puts(names[punkt]);
		unsigned char ch;
		do
		{
			// обработка перемещения по меню клавишами со стрелками
			ch = getch();
			if (ch == 224)
			{
				ch = getch();
				switch (ch)
				{
				case 72:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
					puts(names[punkt]);
					punkt--;
					if (punkt < 0) punkt = 10;
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
					SetConsoleCursorPosition(hConsole, position[punkt]);
					puts(names[punkt]); break;
				case 80:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 1)));
					puts(names[punkt]);
					punkt++;
					if (punkt > 10) punkt = 0;
					SetConsoleTextAttribute(hConsole, (WORD)((3 | 11)));
					SetConsoleCursorPosition(hConsole, position[punkt]);
					puts(names[punkt]); break;
				}
			}
		} while (ch != 13);	// enter - выбор пункта меню
		switch (punkt)
		{
		case 0:
			count1 = input1();
			count2 = input2();
			break;
		case 1:
			view1();
			break;
		case 2:
			view2();
			break;
		case 3:
			request1();
			break;
		case 4:
			request2();
			break;
		case 5:
			request3();
			break;
		case 6:
			sortbybinvstavkami();
			break;
		case 7:
			sortbychel();
				break;
		case 8:
			first=createlist();
			listprint(first);
			break;
		case 9:
			first = createlist();
			root = NULL;
			create_tree(&root);
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
				printf("Должность      |   Количество единиц   |   Количество вакантных мест \n");
				printf("_____________________________________________________________________\n");
			view_tree(root);
			SetConsoleTextAttribute(hConsole, (WORD)((0) | 15));
			system("pause");
			break;
		}

	} while (punkt != 10);
	return 0;
}

