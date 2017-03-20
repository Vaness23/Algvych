#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
using namespace std;

bool iscyrillic (char s)
{
    char alphabet[] = "�����Ũ����������������������������������������������������������";
    for(char *c = alphabet; *c; c++)
        if(s == *c)
            return true;
    return false;
}

void findSubstring (char str1[][81], int n1, int *substring)
{
    int i, count, min=90;
    char *s;

    for (i=0; i<n1; i++)
    {
        count = 0;
        s = str1[i];
        while (*s && (*s == '+' || *s == '-' || *s == '*' || *s == '/'))
        {
            s++;
            count++;
        }

        if (count < min && count != 0)
        {
            min = count;
            *substring = i;
        }
    }
}

void substr(int n, char str[][81], char str1[][81], int *n1, int num[])
{
    //setlocale(LC_ALL, "RUS");
    int i; char *s,*s1; //s-�� ������� ������. s1- �� ������ ���������
    *n1=0; //����� ��������
    for(i=0; i<n; i++)
    {
        s=str[i];
        s1=s;
        while(*s)
            if (iscyrillic(*s))
                    //(!(*s == 'E' || *s == '�' || *s >= '0' && *s <= '9' || *s == '.' || *s == '+' || *s == '-'))
               {
                if (s!=s1)
                { //����������� ���������
                    num [*n1]=i; //���������� ����� �������� c�����
                    strncpy(str1[*n1],s1,s-s1); //�������� ����� ������
                    str1[*n1][s-s1]='\0'; //��������� ����-������ � ����� �����
                    (*n1)++; //����������� ����� ��������
                }
                while (*s && iscyrillic(*s))
                    //(*s && !(*s == 'E' || *s == '�' || *s >= '0' && *s <= '9' || *s == '.' || *s == '+' || *s == '-'))
                    s++;

                s1=s; //������ ����� ���������
            }
            else s++;

        if (s!=s1)
        { //����������� ���������, ������������� � ����� ������
            num [*n1]=i;
            strncpy(str1[*n1],s1,s-s1);
            str1[*n1][s-s1]='\0';
            (*n1)++;
        }
    } //������������� ������ �� ����� for
}

void exchange(int num[], char str[][81], int substring)
{
    int i;
    char *s, *ptr;
    char victim = str[num[substring]];
    for(s = victim; *s; s++)
    {
        while(strstr(victim, 'begin'))
        {
            ptr = strstr(victim, 'begin');
            *ptr = '{';
            for (ptr++ ;ptr < strlen (victim) - 4; ptr++)
                *ptr = *(ptr+4);
            for(ptr = strlen(victim) - 1, i=1; i<=4; i++, ptr--)
                *ptr = '\0';
        }
        while(strstr(victim, 'begin'))
        {
            ptr = strstr(victim, 'end');
            *ptr = '}';
            for (ptr++ ;ptr < strlen (victim) - 4; ptr++)
                *ptr = *(ptr+4);
            for(ptr = strlen(victim) - 1, i=1; i<=4; i++, ptr--)
                *ptr = '\0';
        }


}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");
    char str[10][81], str1[30][81];
    int i, n=0, n1, num[10], substring=-1;
    puts("������� ������: \n");
    while(*gets(str[n]) && *str[n] && n < 10)
        n++;
    substr(n, str, str1, &n1, num);
    if (n1==0)
        puts("��� ��������");
    else
    {
        puts("���������");
        for (i=0; i<n1; i++)
            puts(str1[i]);

        findSubstring(str1, n1, &substring);
        if (substring == -1)
            puts("��� �������� �� ������� ��������");
        else
        {
            puts("���������, ������������ ����������� ����������� ������ ��������: ");
            puts(str1[substring]);
        }
    }
}





