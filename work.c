#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// �γ����ƣ�������ʾѧ��ѡ������������ε��ÿγ̽ṹ������
char courseName[6][20] = {"Chinese", "Math", "English",
                          "Physics", "Politics", "Chemistry"};

// �γ���Ϣ�ṹ��
typedef struct course
{
    int courseNum;       /*�γ����*/
    char courseName[20]; /*�γ�����*/
    int courseScore;     /*�γ�ѧ��*/
    int chooseNum;       /*�ÿγ���ѡ����*/
    int maxNum;          /*�γ������������*/
    struct course *next;
} Course;

// ����γ̽ṹ������ͷ
Course *courseHead = NULL;

// ѧ����Ϣ�ṹ��
typedef struct student
{
    char studentName[20]; /*ѧ������*/
    int courseCode[5];    /*��ѡ�γ̱�ţ����鳤��Ϊ5*/
    // int courseChooseNum;  /*��ѡ�γ�����*/
    int courseScore; /*��ѡ�γ�ѧ��*/
    int courseCount; /*��Ҫѡ��γ̵�����*/
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
 * ���¿γ̽ṹ������
 * @param   head    �γ���Ϣ�ṹ������ͷ
 * @param   courseCode  �γ̱��
 * @return  ��
 * */
void UpdataCourseList(Course *head, int courseCode);

/**
 * ѡ�β���
 * @param   sp      ѧ����Ϣ�ṹ��ָ��
 * @return  ��
 * */
void ToSelectCourse(Student *sp);

/**
 * ѧ��ѡ�β���
 * @param   count   ѧ������
 * @return  ��
 * */
void StudentSelect(int count);

/**
 * ��ʾѧ��ѡ�����
 * @param   head    ѧ����Ϣ�ṹ������
 * @return  ��
 * */
void ShowStudentCourse(Student *head);

/**
 * ��ѧ����Ϣ�ṹ�������������
 * @param   sp      ѧ����Ϣ�ṹ������
 * @return  ��
 * */
void SortStudentList(Student *sp);

int main(void)
{
    // ��������ʱ���ļ�����γ�����
    InputCourse();
    int i;
    // ѧ��������
    srand((int)time(NULL));
    // ��������Ϊ3��
    int studentCount = rand() % 3 + 1;
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
    case 3:
        system("cls");
        // ��ʾѧ��ѡ�����
        ShowStudentCourse(studentHead);
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
    printf("�γ̱��\t�γ�����\tѧ��\t�γ�ʣ������\t�γ���������\n");

    for (; p1 != NULL; p1 = p1->next)
    {
        printf("%-16d%-17s%-12d%-16d%d\n", p1->courseNum, p1->courseName,
               p1->courseScore, p1->maxNum - p1->chooseNum, p1->maxNum);
    }
}

void StudentSelect(int count)
{
    // ����ѧ������
    Student *p1 = NULL, *p2 = NULL;

    for (int i = 0; i < count; i++)
    {
        printf("��%d��ѧ����Ҫѡ�Σ�Ŀǰ�����%d��\n", count, i);
        p1 = (Student *)malloc(sizeof(Student));
        if (i == 0)
        {
            studentHead = p1;
        }
        else
        {
            p2->next = p1;
        }
        p2 = p1;
        // p1->courseChooseNum = 0;
        p1->courseScore = 0;
        memset(p1->courseCode, 0, 5 * sizeof(int));
        // ��Ҫѡ��3~5�ſγ̣����������
        srand((int)time(NULL));
        p1->courseCount = rand() % 3 + 3;
        // ��������
        printf("������ѧ�����֣�");
        scanf("%s", p1->studentName);

        // ѡ�β���
        ToSelectCourse(p1);
    }
    p2->next = NULL;
    system("cls");
    printf("����ͬѧ�����ѡ��!\n");
}

void ToSelectCourse(Student *sp)
{
    int code = 0;

    for (int i = 0; i < sp->courseCount; i++)
    {
        printf("����Ҫѡ��%d�ſγ̣�Ŀǰ��ѡ%d��\n", sp->courseCount, i);
        // ��ʾ��ǰ��ѡ�γ�
        ShowCourse(courseHead);
        printf("������γ̱�ţ�");
        scanf("%d", &code);

        // ����Ƿ�����ѡ���
        if (sp->courseCode[0] != code && sp->courseCode[1] != code &&
            sp->courseCode[2] != code && sp->courseCode[3] != code &&
            sp->courseCode[4] != code)
        {
            UpdataCourseList(courseHead, code);

            sp->courseCode[i] = code;
            sp->courseScore += code;
        }
        else
        {
            printf("����ѡ����ſγ̣�����ѡ\n");
            i--;
        }
    }
    system("cls");
    printf("%sͬѧ�����ѡ�Σ�\n", sp->studentName);
}

void UpdataCourseList(Course *head, int courseCode)
{
    Course *p1 = head;

    for (; p1->courseNum != courseCode; p1 = p1->next)
        ;
    p1->chooseNum++;
}

void ShowStudentCourse(Student *head)
{
    // SortStudentList(head);

    Student *p1 = head;
    printf("ѧ������\t��ѡ�γ�\tѧ��\n");

    for (; p1 != NULL; p1 = p1->next)
    {
        for (int i = 0; i < p1->courseCount; i++)
        {
            printf("%-20s%-10s%d\n", p1->studentName,
                   courseName[p1->courseCode[i] - 1], p1->courseCode[i]);
        }
    }
}

void SortStudentList(Student *sp)
{
    return;
}
