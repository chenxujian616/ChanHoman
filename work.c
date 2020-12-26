#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 课程名称，用于显示学生选课情况，避免多次调用课程结构体链表
char courseName[6][20] = {"Chinese", "Math", "English",
                          "Physics", "Politics", "Chemistry"};

// 课程信息结构体
typedef struct course
{
    int courseNum;       /*课程序号*/
    char courseName[20]; /*课程名称*/
    int courseScore;     /*课程学分*/
    int chooseNum;       /*该课程已选人数*/
    int maxNum;          /*课程最大容纳人数*/
    struct course *next;
} Course;

// 定义课程结构体链表头
Course *courseHead = NULL;

// 学生信息结构体
typedef struct student
{
    char studentName[20]; /*学生姓名*/
    int courseCode[5];    /*已选课程编号，数组长度为5*/
    // int courseChooseNum;  /*已选课程数量*/
    int courseScore; /*已选课程学分*/
    int courseCount; /*需要选择课程的数量*/
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
 * 更新课程结构体链表
 * @param   head    课程信息结构体链表头
 * @param   courseCode  课程编号
 * @return  无
 * */
void UpdataCourseList(Course *head, int courseCode);

/**
 * 选课操作
 * @param   sp      学生信息结构体指针
 * @return  无
 * */
void ToSelectCourse(Student *sp);

/**
 * 学生选课操作
 * @param   count   学生人数
 * @return  无
 * */
void StudentSelect(int count);

/**
 * 显示学生选课情况
 * @param   head    学生信息结构体链表
 * @return  无
 * */
void ShowStudentCourse(Student *head);

/**
 * 对学生信息结构体链表进行排序
 * @param   sp      学生信息结构体链表
 * @return  无
 * */
void SortStudentList(Student *sp);

int main(void)
{
    // 程序运行时从文件读入课程数据
    InputCourse();
    int i;
    // 学生总人数
    srand((int)time(NULL));
    // 测试人数为3人
    int studentCount = rand() % 3 + 1;
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
    case 3:
        system("cls");
        // 显示学生选课情况
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
    printf("课程编号\t课程名称\t学分\t课程剩余人数\t课程人数上限\n");

    for (; p1 != NULL; p1 = p1->next)
    {
        printf("%-16d%-17s%-12d%-16d%d\n", p1->courseNum, p1->courseName,
               p1->courseScore, p1->maxNum - p1->chooseNum, p1->maxNum);
    }
}

void StudentSelect(int count)
{
    // 创建学生链表
    Student *p1 = NULL, *p2 = NULL;

    for (int i = 0; i < count; i++)
    {
        printf("有%d名学生需要选课，目前已完成%d人\n", count, i);
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
        // 需要选择3~5门课程，随机数产生
        srand((int)time(NULL));
        p1->courseCount = rand() % 3 + 3;
        // 输入姓名
        printf("请输入学生名字：");
        scanf("%s", p1->studentName);

        // 选课操作
        ToSelectCourse(p1);
    }
    p2->next = NULL;
    system("cls");
    printf("所有同学已完成选课!\n");
}

void ToSelectCourse(Student *sp)
{
    int code = 0;

    for (int i = 0; i < sp->courseCount; i++)
    {
        printf("您需要选择%d门课程，目前已选%d门\n", sp->courseCount, i);
        // 显示当前可选课程
        ShowCourse(courseHead);
        printf("请输入课程编号：");
        scanf("%d", &code);

        // 检查是否有重选情况
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
            printf("您已选择该门课程，请重选\n");
            i--;
        }
    }
    system("cls");
    printf("%s同学已完成选课！\n", sp->studentName);
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
    printf("学生姓名\t已选课程\t学分\n");

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
