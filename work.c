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
    struct student *prev;
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
 * @return  1       �γ���ѧλ
 *          0       �γ�û��ѧλ
 * */
int UpdataCourseList(Course *head, int courseCode);

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
 * @param   control ��������
 * @return  ��
 * */
void ShowStudentCourse(Student *head, int control);

/**
 * �����������
 * 
 * �ý����������https://www.cnblogs.com/bokezhilu/p/7620181.html
 * @param   s1      ѧ����Ϣ�ṹ������1
 * @param   s2      ѧ����Ϣ�ṹ������2
 * @return  ��
 * */
void Swap(Student *s1, Student *s2);

/**
 * ��ѧ����Ϣ�ṹ�������������
 * @param   sp      ѧ����Ϣ�ṹ������
 * @return  ��
 * */
void SortStudentList(Student *sp);

/**
 * ����ѧ��ѡ����Ϣ
 * @param   head    ѧ����Ϣ�ṹ������
 * @return  ��
 * */
void SaveStudentInfo(Student *head);

/**
 * ��ȡѧ��ѡ����Ϣ
 * @param   control ��������
 * @return  ��
 * */
void ReadStudentCourse(int control);

int main(void)
{
    // ��������ʱ���ļ�����γ�����
    InputCourse();
    int i;
    // ѧ��������
    srand((int)time(NULL));
    // ��������Ϊ3�ˣ����Ը��Ĳ�������
    int studentCount = rand() % 3 + 1;
start:
    printf("\n\t\t��ӭʹ��ѧ��ѡ��ϵͳ!\n");
    printf("�˵���\n");
    printf("1.����γ���Ϣ\n");
    printf("2.ѧ��ѡ��\n");
    printf("3.ѧ��ѡ������鿴\n");
    printf("4.�洢ѡ�����\n");
    printf("5.����ѧ��ѡ���ļ�\n");
    printf("6.�˳�ϵͳ\n");
    printf("\n������˵�ѡ��(1~6):\n");
    scanf("%d", &i);
    if (i < 1 || i > 6)
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
        ShowStudentCourse(studentHead, i);
        goto start;
        break;
    case 4:
        system("cls");
        // ��ֹ������3��
        SortStudentList(studentHead);
        // ����ѡ����Ϣ
        SaveStudentInfo(studentHead);
        goto start;
        break;
    case 5:
        system("cls");
        ReadStudentCourse(i);
        goto start;
        break;
    case 6:
        system("cls");
        exit(0);
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
    fclose(fp);
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
        p1->next = NULL;
        p1->prev = NULL;
        if (i == 0)
        {
            studentHead = p1;
        }
        else
        {
            p2->next = p1;
            p1->prev = p2;
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
            if (UpdataCourseList(courseHead, code) == 1)
            {
                sp->courseCode[i] = code;
                sp->courseScore += code;
            }
            else
            {
                printf("���ſγ��Ѿ�û��ѧλ������ѡ��\n");
                i--;
            }
        }
        else
        {
            printf("����ѡ����ſγ̣�����ѡ��\n");
            i--;
        }
    }
    system("cls");
    printf("%sͬѧ�����ѡ�Σ�\n", sp->studentName);
}

int UpdataCourseList(Course *head, int courseCode)
{
    Course *p1 = head;

    for (; p1 != NULL; p1 = p1->next)
    {
        if (p1->courseNum == courseCode)
        {
            if (p1->chooseNum < p1->maxNum)
            {
                p1->chooseNum++;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

void ShowStudentCourse(Student *head, int control)
{
    Student *p1 = NULL;
    if (control == 3)
    {
        SortStudentList(head);
        p1 = studentHead;
    }
    else
    {
        p1 = head;
    }

    printf("ѧ������\t\t��ѡ�γ�\tѧ��\n");

    for (; p1 != NULL; p1 = p1->next)
    {
        for (int i = 0; i < p1->courseCount; i++)
        {
            printf("%-24s%-17s%d\n", p1->studentName,
                   courseName[p1->courseCode[i] - 1], p1->courseCode[i]);
        }
    }
}

void SortStudentList(Student *sp)
{
    Student *head = sp;
    char control = 1;

    // ��ѧ�ִ�С����˳������
    while (head != NULL)
    {
        Student *headNext = head->next;
        while (headNext != NULL)
        {
            if (headNext->courseScore < head->courseScore)
            {
                Swap(head, headNext);
                // ע������һ��Ҫ�����£���Ϊ��������ڵ��λ��
                Student *tmp = head;
                head = headNext;
                headNext = tmp;
            }
            headNext = headNext->next;
        }
        // ��ɵ�һ�ν�������Сֵ������ͷ
        if (control == 1)
        {
            studentHead = head;
            control = 0;
        }
        head = head->next;
    }

    // ѧ����ͬʱ������������ĸ��С��������
    head = studentHead;
    control = 1;
    while (head != NULL)
    {
        Student *headnext = head->next;
        while (headnext != NULL)
        {
            if ((head->courseScore == headnext->courseScore) &&
                (head->studentName[0] > headnext->studentName[0]))
            {
                Swap(head, headnext);
                Student *tmp = head;
                head = headnext;
                headnext = tmp;
            }
            headnext = headnext->next;
        }
        if (control == 1)
        {
            studentHead = head;
            control = 0;
        }
        head = head->next;
    }
}

void Swap(Student *s1, Student *s2)
{
    if (s1->next == s2)
    {
        if (s2->next != NULL)
        {
            s2->next->prev = s1;
        }
        if (s1->prev != NULL)
        {
            s1->prev->next = s2;
        }
        s1->next = s2->next;
        s2->prev = s1->prev;
        s1->prev = s2;
        s2->next = s1;
    }
    else if (s1->prev == s2)
    {
        if (s1->next != NULL)
        {
            s1->next->prev = s2;
        }
        if (s2->prev != NULL)
        {
            s2->prev->next = s1;
        }
        s2->next = s1->next;
        s1->prev = s2->prev;
        s2->prev = s1;
        s1->next = s2;
    }
    else
    {
        if (s1->next != NULL)
        {
            s1->next->prev = s2;
        }
        if (s1->prev != NULL)
        {
            s1->prev->next = s2;
        }
        if (s2->next != NULL)
        {
            s2->next->prev = s1;
        }
        if (s2->prev != NULL)
        {
            s2->prev->next = s1;
        }
        Student *s1Next = s1->next;
        Student *s1Prev = s1->prev;
        s2->next = s1Next;
        s2->prev = s1Prev;
    }
}

void SaveStudentInfo(Student *head)
{
    Student *p1 = head;
    FILE *fp1, *fp2;

    if ((fp1 = fopen("data.txt", "w")) == NULL ||
        (fp2 = fopen("situation.txt", "w")) == NULL)
    {
        printf("�Ҳ�����Ӧ�ļ�\n");
        exit(0);
    }

    fprintf(fp2, "����\t�γ�����\tѧ��\n");
    for (; p1 != NULL; p1 = p1->next)
    {
        // ����������ѧ�֣��γ̱�ŵ�˳��洢
        fprintf(fp1, "%s %d %d %d %d %d %d %d\n", p1->studentName, p1->courseScore,
                p1->courseCode[0], p1->courseCode[1], p1->courseCode[2],
                p1->courseCode[3], p1->courseCode[4], p1->courseCount);
        for (int i = 0; i < p1->courseCount; i++)
        {
            fprintf(fp2, "%s\t%s\t%d\n", p1->studentName,
                    courseName[p1->courseCode[i] - 1], p1->courseCode[i]);
        }
        fprintf(fp2, "%sͬѧ�ܹ�ѡ��%d�ſγ̣�����%dѧ��\n", p1->studentName, p1->courseCount, p1->courseScore);
    }
    fclose(fp1);
    fclose(fp2);
}

void ReadStudentCourse(int control)
{
    FILE *fp;
    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("�Ҳ�����Ӧ�ļ�\n");
        exit(0);
    }

    // ������ȡ����
    Student *head = NULL;
    Student *p1, *p2;
    p1 = p2 = (Student *)malloc(sizeof(Student));
    p1->prev = NULL;

    fscanf(fp, "%s%d%d%d%d%d%d%d", p1->studentName, &p1->courseScore, &p1->courseCode[0],
           &p1->courseCode[1], &p1->courseCode[2],
           &p1->courseCode[3], &p1->courseCode[4], &p1->courseCount);
    head = p1;

    while (!feof(fp))
    {
        p2->next = p1;
        p2 = p1;
        p1 = (Student *)malloc(sizeof(Student));
        p1->prev = NULL;
        fscanf(fp, "%s%d%d%d%d%d%d%d", p1->studentName, &p1->courseScore, &p1->courseCode[0],
               &p1->courseCode[1], &p1->courseCode[2],
               &p1->courseCode[3], &p1->courseCode[4], &p1->courseCount);
    }
    p2->next = NULL;
    free(p1);
    p1 = NULL;
    fclose(fp);

    ShowStudentCourse(head, control);
}