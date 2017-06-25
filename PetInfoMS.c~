#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>

struct pet //保存宠物信息的结构体
{
    char type[10];    //类型
    int id;           //编号
    char name[20];    //姓名
    float age;        //年龄
    char sex[10];     //性别
    char color[10];   //颜色
    int shape;        //体型
    char variety[20]; //品种
    float price;      //价格
    struct pet *next; //指向下一个宠物信息结构体的指针
};
struct user //保存用户帐号密码的结构体
{
    char id[20];  //用户帐号
    char passwd[20];  //用户密码
    struct user *next;  //指向下一个用户信息结构体的指针
};

int getch();
struct user *ReadUser(); //读取user.txt文件
void Register();  //注册
void Login();     //登录
struct pet *Read_File();  //读取pet.txt文件
void Write_File(struct pet *phead);  //保存宠物信息
struct pet *Input();  //录入宠物信息
void Add();  //添加宠物信息
void Delete();  //删除宠物信息
void Modify();  //修改宠物信息
void Search();  //查询宠物信息
void SingleSearch();  //单一查询
void IdSearch();  //按编号查询
void NameSearch();  //按姓名查询
void DoubleSearch();  //组合查询
void TypeAgeSearch();  //按种类和年龄查询
void TypePriceSearch();  //按种类和价格查询
void Count();  //统计宠物信息
void SimpleCount();  //简单统计
void TypeCount();  //按类型统计
void SexCount();  //按性别统计
void MultipleCount();  //综合统计
void Sort();  //排序宠物信息
void IdSort();  //按编号升序
void PriceSort();  //按价格升序
void AgeSort();  //按年龄降序
void ShapeSort();  //按体型降序
void SortOutput(struct pet *phead);  //排序输出
void Output();  //输出宠物信息
void MenuSelect();  //主菜单
void WelcomeMenu();  //欢迎菜单
void Login_head();  //界面优化，下同
void Register_head();
void Input_head();
void Add_head();
void Delete_head();
void IdSearch_head();
void NameSearch_head();
void TypePriceSearch_head();
void TypeAgeSearch_head();
void TypeCount_head();
void SexCount_head();
void IdSort_head();
void AgeSort_head();
void PriceSort_head();
void ShapeSort_head();
void Output_head();


int getch()
{
        int c=0;
        struct termios org_opts, new_opts;
        int res=0;
        //-----  store old settings -----------
        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
        //---- set new terminal parms --------
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();
        //------  restore old settings ---------
        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
        return c;
}

void Login_head()  //界面优化，下同
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                     登录                     *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void Register_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                     注册                     *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void Input_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 录入宠物信息                 *|\n");
    printf("\t\t\t\t|*         提示:类型只可输入狗猫兔猪鸟鼠        *|\n");
    printf("\t\t\t\t|*         年龄不足一岁的时候,用小数表示        *|\n");
    printf("\t\t\t\t|*         性别只可输入B(boy) 或 G(girl)        *|\n");
    printf("\t\t\t\t|*         体型分为不同的等级,用整数表示        *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void Add_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 添加宠物信息                 *|\n");
    printf("\t\t\t\t|*         提示:类型只可输入狗猫兔猪鸟鼠        *|\n");
    printf("\t\t\t\t|*         年龄不足一岁的时候,用小数表示        *|\n");
    printf("\t\t\t\t|*         性别只可输入B(boy) 或 G(girl)        *|\n");
    printf("\t\t\t\t|*         体型分为不同的等级,用整数表示        *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void Delete_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 删除宠物信息                 *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void IdSearch_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*              按编号查询宠物信息              *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void NameSearch_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*              按姓名查询宠物信息              *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void TypePriceSearch_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*           按种类和价格查询宠物信息           *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void TypeAgeSearch_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*           按种类和年龄查询宠物信息           *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void TypeCount_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*              按类型统计宠物信息              *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void SexCount_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*              按性别统计宠物信息              *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void IdSort_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*               宠物编号升序排列                *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void AgeSort_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 宠物年龄降序                 *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void ShapeSort_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 宠物体型降序                 *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void PriceSort_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================ ===============|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 宠物价格升序                 *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void Output_head()
{
    printf("\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 输出宠物信息                 *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
}
void MenuSelect()  //主菜单
{
    int choice;
    char ch;
    do{
        system("clear");
        printf("\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*               1. 录入宠物信息                *|\n");
	    printf("\t\t\t\t|*               2. 添加宠物信息                *|\n");
	    printf("\t\t\t\t|*               3. 删除宠物信息                *|\n");
	    printf("\t\t\t\t|*               4. 修改宠物信息                *|\n");
	    printf("\t\t\t\t|*               5. 查询宠物信息                *|\n");
	    printf("\t\t\t\t|*               6. 统计宠物信息                *|\n");
	    printf("\t\t\t\t|*               7. 排序宠物信息                *|\n");
	    printf("\t\t\t\t|*               8. 输出宠物信息                *|\n");
	    printf("\t\t\t\t|*               9. 注册新帐号                  *|\n");
	    printf("\t\t\t\t|*               0. 退出                        *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——9):");
        scanf("%d",&choice);
        getchar();
        if(choice==0||(choice>=2&&choice<=9))
        {
            printf("\t\t\t\t按任意键进入下一步...");
            getch();
        }
        if(choice==1)
        {
            printf("\n\t\t\t\t该操作可能会清空历史数据,确定重新录入宠物信息吗?(Y/N):");
            scanf("%c",&ch);
            getchar();
            if(ch=='N'||ch=='n')
                MenuSelect();
        }
        switch(choice)
        {
            case 1:Input();break;
            case 2:Add(); break;
            case 3:Delete();break;
            case 4:Modify();break;
            case 5:Search(); break;
            case 6:Count();break;
            case 7:Sort();break;
            case 8:Output();break;
            case 9:Register();break;
            case 0:WelcomeMenu();break;
        }
    }while(choice!=0);
}
void WelcomeMenu()  //欢迎界面菜单
{
    int choice;
    do{
        system("clear");
	    printf("\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*                    1.登录                    *|\n");
	    printf("\t\t\t\t|*                    0.退出                    *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——1):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        printf("\n");
        switch(choice)
        {
            case 1:Login();      break;
            case 0:exit(0);      break;
        
        }
    }while(choice!=0);
}
int main()
{
    WelcomeMenu();
    return 0;
}

