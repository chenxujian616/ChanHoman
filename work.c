#include <stdio.h>
#include <stdlib.h>

// �γ���Ϣ�ṹ��
typedef struct course
{
    // �γ����
    int courseNum;
    char courseName[20];
    int courseScore;
    // ��ѡ����
    int chooseNum;
    // ����������
    int maxNum;
    // ����
    struct course *next;
} Course;

// ����γ̽ṹ������ͷ
Course *courseHead = NULL;

// ѧ����Ϣ�ṹ��
typedef struct student
{
    // ѧ�����
    // int studentNum;
    char studentName[20];
    // ��ѡ�γ̱�ţ����鳤��Ϊ5
    int courseNum[5];
    // ��ѡ�γ�����
    int courseChooseNum;
    // ��ѡ�γ�ѧ��
    int courseScore;
    struct student *next;
} Student;

// ����ѧ���ṹ������ͷ
Student *studentHead = NULL;

/**
 * ¼��γ���Ϣ
 * @param   void
 * @return  ��
 * */
void InputCourse(void);

/**
 * ��ʾ�γ���Ϣ
 * @param   head    �γ���Ϣ�ṹ������ͷ
 * @return  ��
 * */
void ShowCourse(Course *head);

/**
 * ѧ��ѡ�β���
 * @param   count   ѧ������
 * @return  ��
 * */
void StudentSelect(int count);

int main(void)
{
    // ��������ʱ���ļ�����γ�����
    InputCourse();
    int i;
    // ѧ��������
    int studentCount = rand() % 10 + 1;
start:
    printf("\n\t\t��ӭʹ��ѧ��ѡ��ϵͳ!\n");
    printf("�˵���\n");
    printf("1.����γ���Ϣ\n");
    printf("2.ѧ��ѡ��\n");
    printf("3.ѧ��ѡ������鿴\n");
    printf("4.�洢ѡ�����\n");
    printf("\n������˵�ѡ��(1~7):\n");
    scanf("%d", &i);
    if (i < 1 || i > 7)
    {
        printf("����������������룺");
        system("cls");
        goto start;
    }
    switch (i)
    {
    case 1:
        system("cls");
        // ��ʾ�γ���Ϣ
        ShowCourse(courseHead);
        goto start;
        break;
    case 2:
        system("cls");
        // ѧ��ѡ��
        StudentSelect(studentCount);
        goto start;
        break;

    default:
        break;
    }
    system("pause");
    return 0;
}

void InputCourse(void)
{
    FILE *fp;
    if ((fp = fopen("course.txt", "r")) == NULL)
    {
        printf("�Ҳ�����Ӧ�ļ�\n");
        exit(0);
    }

    // �����γ�����
    Course *p1 = NULL, *p2 = NULL;
    p1 = p2 = (Course *)malloc(sizeof(Course));

    // ¼��γ���Ϣ
    fscanf(fp, "%d%s%d%d", &(p1->courseNum), p1->courseName, &(p1->courseScore), &(p1->maxNum));
    p1->chooseNum = 0;

    while (!feof(fp))
    {
        if (p1->courseNum == 1)
        {
            courseHead = p1;
        }
        else
        {
            p2->next = p1;
        }
        p2 = p1;
        p1 = (Course *)malloc(sizeof(Course));
        p1->chooseNum = 0;
        fscanf(fp, "%d%s%d%d", &(p1->courseNum), p1->courseName, &(p1->courseScore), &(p1->maxNum));
    }
    p2->next = NULL;
    free(p1);
    p1 = NULL;
}

void ShowCourse(Course *head)
{
    Course *p1 = head;
    printf("�γ̱��\t�γ�����\tѧ��\t�γ���ѡ����\t�γ���������\n");

    for (; p1 != NULL; p1 = p1->next)
    {
        printf("%-16d%-17s%-12d%-16d%d\n", p1->courseNum, p1->courseName, p1->courseScore, p1->chooseNum, p1->maxNum);
    }
}

void StudentSelect(int count)
{
    // ����ѧ������
    Student *p1 = NULL, *p2 = NULL;
    p1 = p2 = (Student *)malloc(sizeof(Student));

    for (int i = 0; i < count; i++)
    {
        if (i == 0)
        {
            studentHead = p1;
        }
        else
        {
            p2->next = p1;
        }
    }
}
