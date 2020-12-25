#include <stdio.h>
#include <stdlib.h>

// 课程信息结构体
typedef struct course
{
    // 课程序号
    int courseNum;
    char courseName[20];
    int courseScore;
    // 已选人数
    int chooseNum;
    // 可容纳人数
    int maxNum;
    // 链表
    struct course *next;
} Course;

// 定义课程结构体链表头
Course *courseHead = NULL;

// 学生信息结构体
typedef struct student
{
    // 学生序号
    // int studentNum;
    char studentName[20];
    // 已选课程编号，数组长度为5
    int courseNum[5];
    // 已选课程数量
    int courseChooseNum;
    // 已选课程学分
    int courseScore;
    struct student *next;
} Student;

// 定义学生结构体链表头
Student *studentHead = NULL;

/**
 * 录入课程信息
 * @param   void
 * @return  无
 * */
void InputCourse(void);

/**
 * 显示课程信息
 * @param   head    课程信息结构体链表头
 * @return  无
 * */
void ShowCourse(Course *head);

/**
 * 学生选课操作
 * @param   count   学生人数
 * @return  无
 * */
void StudentSelect(int count);

int main(void)
{
    // 程序运行时从文件读入课程数据
    InputCourse();
    int i;
    // 学生总人数
    int studentCount = rand() % 10 + 1;
start:
    printf("\n\t\t欢迎使用学生选课系统!\n");
    printf("菜单：\n");
    printf("1.导入课程信息\n");
    printf("2.学生选课\n");
    printf("3.学生选课情况查看\n");
    printf("4.存储选课情况\n");
    printf("\n请输入菜单选项(1~7):\n");
    scanf("%d", &i);
    if (i < 1 || i > 7)
    {
        printf("输入错误，请重新输入：");
        system("cls");
        goto start;
    }
    switch (i)
    {
    case 1:
        system("cls");
        // 显示课程信息
        ShowCourse(courseHead);
        goto start;
        break;
    case 2:
        system("cls");
        // 学生选课
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
        printf("找不到相应文件\n");
        exit(0);
    }

    // 创建课程链表
    Course *p1 = NULL, *p2 = NULL;
    p1 = p2 = (Course *)malloc(sizeof(Course));

    // 录入课程信息
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
    printf("课程编号\t课程名称\t学分\t课程已选人数\t课程人数上限\n");

    for (; p1 != NULL; p1 = p1->next)
    {
        printf("%-16d%-17s%-12d%-16d%d\n", p1->courseNum, p1->courseName, p1->courseScore, p1->chooseNum, p1->maxNum);
    }
}

void StudentSelect(int count)
{
    // 创建学生链表
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
