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
struct user *ReadUser() //读取user.txt文件
{
    struct user *phead,*pnew,*pend;  //创建链表
    FILE *fp;
    fp=fopen("user.txt","rt");  //以只读方式打开user.txt文本文件
    phead=NULL; //头指针指向空
    if(fp!=NULL)
    {
        while(!feof(fp))  //文件结束，循环才停止
        {
            pnew=(struct user *)malloc(sizeof(struct user));  //给新结点开辟空间
            pnew->next=NULL;
            if((fscanf(fp,"%s %s",pnew->id,pnew->passwd))!=2)  //如果一行不是两个数据,则终止循环
               break;
            if(phead==NULL)
            {
                phead=pnew;
            }
            else
            {
                pend->next=pnew;
            }
            pend=pnew;
        }
    }
    fclose(fp); //关闭文件
    return phead; //返回头指针
}
void Register()  //注册
{
    FILE *fp;
    char id[20];
    char passwd1[20];
    char passwd2[20];
    struct user *t;
    t=ReadUser();  //把文件数据里的头指针地址赋给指针t
    system("clear");  //清屏
    Register_head();  //界面
    printf("\t\t\t\t\t请输入帐号:");
    scanf("%s",id);
    getchar(); //吸收回车
    while(t!=NULL)  //遍历文件里的id，进行判断
    {
        if(strcmp(id,t->id)==0)
        {
            printf("\n\t\t\t\t\t该帐号已存在!按任意键返回.");
            getch();
            return;
        }
        t=t->next;
    }
    fp=fopen("user.txt","at");  //以追加方式打开文件
    printf("\n\t\t\t\t\t请输入密码:");
    scanf("%s",passwd1);
    printf("\n\t\t\t\t\t请再次输入密码:");
    scanf("%s",passwd2);
    if(strcmp(passwd1,passwd2)==0)  //判断两次输入密码是否一致
    {
        fprintf(fp,"%s %s\n",id,passwd1);
        fclose(fp);
        getchar();
        printf("\n\t\t\t\t\t帐号注册成功!按任意键返回.");
    }
    else
    {
        fclose(fp);
        getchar();
        printf("\n\t\t\t\t\t输入密码有误,帐号注册失败!\n\n\t\t\t\t\t按任意键返回.");
    }
    getch(); //吸收任意键
}
void Login()  //登录
{
    int i,n,count=0;
    char ch;
    char *p;
    system("clear");
    Login_head();
    for(i=0;i<3;i++)  //三次输入判断
    {
        struct user *t;
        t=ReadUser();
        char id[20]={0};
        char passwd[20]={0};
        printf("\n\t\t\t\t\t请输入帐号:");
        scanf("%s",id);
        getchar();  //吸收回车
        printf("\n\t\t\t\t\t请问您输入时是否需要隐藏密码:(Y/N):");
        scanf("%c",&ch);
        printf("\n");
        if(ch=='Y'||ch=='y')  //隐藏密码
        {
            getchar();
            p=getpass("\t\t\t\t\t请输入密码:");
            strcpy(passwd,p);
        }
        if(ch=='N'||ch=='n')  //不隐藏密码
        {
            getchar();
            printf("\t\t\t\t\t请输入密码:");
            scanf("%s",passwd);
            getchar();
        }
        while(t!=NULL)  //遍历文件里的id和passwd，进行判断
        {
            if(strcmp(id,t->id)==0&&strcmp(passwd,t->passwd)==0)
            {
                printf("\n\t\t\t\t\t登录成功!按任意键进入主菜单.");
                system("xcowsay hahaha 来找我玩呀～");
                getch();
                MenuSelect();
                break;
            }
            t=t->next;
        }
        if(t==NULL)
        {
            printf("\n\t\t\t\t\t用户名或密码有误,请重新输入!\n");
            count++; //错误次数
        }
    }
    if(count==3)  //输入密码三次均错误
    {
        printf("\n\t\t\t\t\t您已连续3次用户名或密码输入有误,登录失败!系统将退出.\n");
        sleep(6);  //休眠函数，短时间暂停
        exit(0);
    }
}
struct pet *Read_File()  //读取pet.txt文件
{
    struct pet *phead,*pnew,*pend;
    FILE *fp;
    fp=fopen("pet.txt","rt");
    phead=NULL;
    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            pnew=(struct pet *)malloc(sizeof(struct pet));
            pnew->next=NULL;
            if((fscanf(fp,"%s %d %s %f %s %s %d %s %f",pnew->type,&pnew->id,pnew->name,&pnew->age,pnew->sex,pnew->color,&pnew->shape,pnew->variety,&pnew->price))!=9)
                   break;
            if(phead==NULL)
            {
                phead=pnew;
            }
            else
            {
                pend->next=pnew;
            }
            pend=pnew;
        }
    }
    fclose(fp);
    return phead;
}
void Write_File(struct pet *phead)  //保存宠物信息
{
    struct pet *t;
    t=phead;
    FILE *fp;
    fp=fopen("pet.txt","wt");
    if(fp==NULL)
    {
        printf("文件打开失败!\n");
        exit(1);
    }
    while(t!=NULL)
    {
        fprintf(fp,"%s %d %s %.1f %s %s %d %s %.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
        t=t->next;
    }
    fclose(fp);
}
struct pet *Input()  //录入宠物信息
{
    system("clear");
    Input_head();
    struct pet *phead,*pnew,*pend;  //创建链表
    int i,npet;
    phead=pend=pnew=(struct pet *)malloc(sizeof(struct pet));
    //判断内存是否为空
    if(pnew==NULL||pend==NULL)
    {
        printf("内存分配失败,程序终止!\n");
        exit(1);
    }
    printf("\t\t\t\t请输入录入宠物信息的数量(大于0):");
    scanf("%d",&npet);
    getchar(); //吸收回车
    printf("\t\t\t\t按任意键进入下一步...");
    getch();
    system("clear");
    Input_head();
    printf("\t\t\t\t\t\t类型:");
    scanf("%s",pnew->type);
    printf("\t\t\t\t\t\t编号:");
    scanf("%d",&pnew->id);
    printf("\t\t\t\t\t\t姓名:");
    scanf("%s",pnew->name);
    printf("\t\t\t\t\t\t年龄:");
    scanf("%f",&pnew->age);
    printf("\t\t\t\t\t\t性别:");
    scanf("%s",pnew->sex);
    printf("\t\t\t\t\t\t颜色:");
    scanf("%s",pnew->color);
    printf("\t\t\t\t\t\t体型:");
    scanf("%d",&pnew->shape);
    printf("\t\t\t\t\t\t品种:");
    scanf("%s",pnew->variety);
    printf("\t\t\t\t\t\t价格:");
    scanf("%f",&pnew->price);
    for(i=0;i<npet-1;i++)
    {
        system("clear");
        Input_head();
        pnew=(struct pet *)malloc(sizeof(struct pet));
        if(pnew==NULL)
        {
            printf("内存分配失败,程序终止!\n");
            exit(1);
        }
        printf("\t\t\t\t\t\t类型:");
        scanf("%s",pnew->type);
        printf("\t\t\t\t\t\t编号:");
        scanf("%d",&pnew->id);
        printf("\t\t\t\t\t\t姓名:");
        scanf("%s",pnew->name);
        printf("\t\t\t\t\t\t年龄:");
        scanf("%f",&pnew->age);
        printf("\t\t\t\t\t\t性别:");
        scanf("%s",pnew->sex);
        printf("\t\t\t\t\t\t颜色:");
        scanf("%s",pnew->color);
        printf("\t\t\t\t\t\t体型:");
        scanf("%d",&pnew->shape);
        printf("\t\t\t\t\t\t品种:");
        scanf("%s",pnew->variety);
        printf("\t\t\t\t\t\t价格:");
        scanf("%f",&pnew->price);
        pend->next=pnew;  //原来的尾结点指向新结点
        pend=pnew;  //新结点称为新的尾结点
    }
    pend->next=NULL;
    Write_File(phead);  //保存链表信息
    getchar();
    printf("\n\t\t\t\t\t\t录入完成!按任意键返回.");
    getch();
    return phead;
}
void Add()  //添加宠物信息
{
    system("clear");
    Add_head();
    struct pet *phead,*t,*newadd;
    phead=Read_File();
    t=phead;
    while(t&&t->next!=NULL)   //找到尾结点
    {
        t=t->next;
    }
    newadd=(struct pet*)malloc(sizeof(struct pet));
    system("clear");
    Add_head();
    printf("\t\t\t\t\t\t类型:");
    scanf("%s",newadd->type);
    printf("\t\t\t\t\t\t编号:");
    scanf("%d",&newadd->id);
    printf("\t\t\t\t\t\t姓名:");
    scanf("%s",newadd->name);
    printf("\t\t\t\t\t\t年龄:");
    scanf("%f",&newadd->age);
    printf("\t\t\t\t\t\t性别:");
    scanf("%s",newadd->sex);
    printf("\t\t\t\t\t\t颜色:");
    scanf("%s",newadd->color);
    printf("\t\t\t\t\t\t体型:");
    scanf("%d",&newadd->shape);
    printf("\t\t\t\t\t\t品种:");
    scanf("%s",newadd->variety);
    printf("\t\t\t\t\t\t价格:");
    scanf("%f",&newadd->price);
    t->next=newadd;
    newadd->next=NULL;
    Write_File(phead);
    getchar();
    printf("\n\t\t\t\t\t\t添加完成!按任意键返回.");
    getch();
}
void Delete()  //删除宠物信息
{
    system("clear");
    Delete_head();
    struct pet *phead,*cur,*pre;
    char ch,petname[20];
    int flag=0;
    phead=Read_File();
    printf("\t\t\t\t\t请输入您想删除的宠物姓名:");
    scanf("%s",petname);
    if(phead==NULL)
    {
        printf("宠物信息为空,无法删除!\n");
        return;
    }
    cur=pre=phead;
    do{
        if(strcmp(cur->name,petname)==0)
        {
            printf("\n\t\t\t\t\t已找到该宠物,详细信息如下:\n");
            printf("\t\t----------------------------------------------------------------------------------------\n");
            printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
            printf("\t\t----------------------------------------------------------------------------------------\n");
            printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",cur->type,cur->id,cur->name,cur->age,cur->sex,cur->color,cur->shape,cur->variety,cur->price);
            getchar();
            printf("\n\n\t\t\t\t\t确定删除该宠物信息吗?(Y/N):");
            scanf("%c",&ch);
            if(ch=='Y'||ch=='y')
            {
                if(cur==phead)  //当前结点是头结点
                {
                    phead=cur->next;  //头结点指向当前结点的下一个结点
                    free(cur);
                }
                else if(cur->next==NULL)  //当前结点是尾结点
                {
                    pre->next=NULL;  //当前结点的前一个结点作为尾结点
                    free(cur);
                }
                else
                {
                    pre->next=cur->next;  //当前结点的前一个结点指向当前结点的下一个结点
                    free(cur);
                }
                flag=1;  //已删除
                break;
            }
            else
            {
                getchar();               
                printf("\n\t\t\t\t\t不删除该宠物信息,按任意键返回.");
                getch();
                return;
            }
        }
        else
        {
            pre=cur;  //当前结点作为前一个结点
            cur=cur->next;  //当前结点指向下一个结点
        }
    }while(cur);  //直到当前结点为空循环终止
    Write_File(phead);
    if(flag==1)
    {
        getchar();
        printf("\n\t\t\t\t\t已删除该宠物信息!按任意键返回.");
    }
    else
    {
        getchar();
        printf("\n\t\t\t\t\t未找到该宠物信息,删除失败!按任意键返回.");
    }
    getch();
}
void Modify()  //修改宠物信息
{
    system("clear");
    printf("\n\n\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*                 修改宠物信息                 *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*        1.类型  2.姓名  3.年龄  4.性别        *|\n");
    printf("\t\t\t\t|*        5.颜色  6.体型  7.品种  8.价格        *|\n");
    printf("\t\t\t\t|*        9.修改全部      0.退出                *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
    struct pet *phead,*t;
    int petid,choice;
    char ch;
    phead=Read_File();
    printf("\t\t\t\t\t请输入您想修改的宠物编号:");
    scanf("%d",&petid);
    if(phead==NULL)
    {
        printf("\n\t\t\t\t\t宠物信息为空,无法修改!\n");
        return;
    }
    t=phead;
    while(t!=NULL)
    {
        if(t->id==petid)
        {
            printf("\n\t\t\t\t\t已找到该宠物,详细信息如下:\n");
            printf("\t\t----------------------------------------------------------------------------------------\n");
            printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
            printf("\t\t----------------------------------------------------------------------------------------\n");
            printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
            printf("\n\t\t\t\t请选择您要修改的选项(输入0——9):");
            scanf("%d",&choice);
            getchar();
            switch(choice)
            {
                case 1:
                        printf("\n\t\t\t\t请输入宠物新类型:");
                        scanf("%s",t->type);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 2:
                        printf("\n\t\t\t\t请输入宠物新姓名:");
                        scanf("%s",t->name);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 3:
                        printf("\n\t\t\t\t请输入宠物新年龄:");
                        scanf("%f",&t->age);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 4:
                        printf("\n\t\t\t\t请输入宠物新性别:");
                        scanf("%s",t->sex);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 5:
                        printf("\n\t\t\t\t请输入宠物新颜色:");
                        scanf("%s",t->color);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 6:
                        printf("\n\t\t\t\t请输入宠物新体型:");
                        scanf("%d",&t->shape);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 7:
                        printf("\n\t\t\t\t请输入宠物新品种:");
                        scanf("%s",t->variety);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 8:
                        printf("\n\t\t\t\t请输入宠物新价格:");
                        scanf("%f",&t->price);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 9:
                        printf("\n\t\t\t\t请输入宠物新类型:");
                        scanf("%s",t->type);
                        printf("\n\t\t\t\t请输入宠物新姓名:");
                        scanf("%s",t->name);
                        printf("\n\t\t\t\t请输入宠物新年龄:");
                        scanf("%f",&t->age);
                        printf("\n\t\t\t\t请输入宠物新性别:");
                        scanf("%s",t->sex);
                        printf("\n\t\t\t\t请输入宠物新颜色:");
                        scanf("%s",t->color);
                        printf("\n\t\t\t\t请输入宠物新体型:");
                        scanf("%d",&t->shape);
                        printf("\n\t\t\t\t请输入宠物新品种:");
                        scanf("%s",t->variety);
                        printf("\n\t\t\t\t请输入宠物新价格:");
                        scanf("%f",&t->price);
                        printf("\n\t\t\t\t修改成功!\n");
                        break;
                case 0:
                        break;
            }
            getchar();
            printf("\n\t\t\t\t是否保存修改后的信息?(Y/N):");
            scanf("%c",&ch);
            if(ch=='Y'||ch=='y')
            {
                getchar();
                printf("\n\t\t\t\t保存成功!按任意键返回.");
                Write_File(phead);
            }
            if(ch=='N'||ch=='n')
            {
                getchar();
                printf("\n\t\t\t\t不保存该宠物修改信息!按任意键返回.");
            }
            getch();
            break;
        }
        t=t->next;
    }
    if(t==NULL)
    {
        getchar();
        printf("\n\t\t\t\t\t未找到该宠物信息,修改失败!按任意键返回.");
        getch();
    }
}
void Search()  //查询宠物信息
{
    int choice;
    do{
        system("clear");
        printf("\n\n\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*                 1. 单一查询                  *|\n");
	    printf("\t\t\t\t|*                 2. 组合查询                  *|\n");
	    printf("\t\t\t\t|*                 0. 退出                      *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——2):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        switch(choice)
        {
            case 1:SingleSearch();  break;
            case 2:DoubleSearch();  break;
            case 0:return;          break;
        }
    }while(choice!=0);
}
void SingleSearch()  //单一查询
{
    int choice;
    do{
        system("clear");
        printf("\n\n\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*                1. 按编号查询                 *|\n");
	    printf("\t\t\t\t|*                2. 按名字查询                 *|\n");
	    printf("\t\t\t\t|*                0. 退出                       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——2):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        switch(choice)
        {
            case 1:IdSearch();    break;
            case 2:NameSearch();  break;
            case 0:return;        break;
        }
    }while(choice!=0);
}
void IdSearch()  //按编号查询
{
    system("clear");
    IdSearch_head();
    struct pet *phead,*t;
    int petid;
    phead=Read_File();
    printf("\t\t\t\t\t请输入您想查询的宠物编号:");
    scanf("%d",&petid);
    getchar();
    if(phead==NULL)
    {
        printf("\n\t\t\t\t\t宠物信息为空,无法查询!\n");
        return;
    }
    t=phead;
    while(t!=NULL)  //遍历pet.txt
     {
        if(t->id==petid)
            break;
        t=t->next;
    }
    if(t==NULL)
    {
        printf("\n\t\t\t\t\t未找到该宠物信息,查询失败!按任意键返回.\n");
    }
    else
    {
        printf("\n\t\t\t\t\t已找到该宠物,详细信息如下:\n");
        printf("\t\t----------------------------------------------------------------------------------------\n");
        printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
        printf("\t\t----------------------------------------------------------------------------------------\n");
        printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
        printf("\n\t\t\t\t\t按任意键返回.\n");
    }
    getch();
}
void NameSearch()  //按姓名查询
{
    system("clear");
    NameSearch_head();
    struct pet *phead,*t;
    char petname[20];
    phead=Read_File();
    printf("\t\t\t\t\t请输入您想查询的宠物姓名:");
    scanf("%s",petname);
    if(phead==NULL)
    {
        printf("宠物信息为空,无法查询!\n");
        return;
    }
    t=phead;
    while(t!=NULL)
    {
        if(strcmp(t->name,petname)==0)
            break;
        t=t->next;
    }
    if(t==NULL)
    {
        getchar();
        printf("\n\t\t\t\t\t未找到该宠物信息,查询失败!按任意键返回.\n");
    }
    else
    {
        getchar();
        printf("\n\t\t\t\t\t已找到该宠物,详细信息如下:\n");
        printf("\t\t----------------------------------------------------------------------------------------\n");
        printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
        printf("\t\t----------------------------------------------------------------------------------------\n");
        printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
        printf("\n\t\t\t\t\t按任意键返回.\n");
    }
    getch();
}
void DoubleSearch()  //组合查询
{
    int choice;
    do{
        system("clear");
        printf("\n\n\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*             1. 按种类和价格查询              *|\n");
	    printf("\t\t\t\t|*             2. 按种类和年龄查询              *|\n");
	    printf("\t\t\t\t|*             0. 退出                          *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——2):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        switch(choice)
        {
            case 1:TypePriceSearch();   break;
            case 2:TypeAgeSearch();     break;
            case 0:return;              break;
        }
    }while(choice!=0);
}
void TypePriceSearch()  //按种类和价格查询
{
    system("clear");
    TypePriceSearch_head();
    struct pet *phead,*t;
    char pettype[20];
    float petprice1,petprice2,temp;
    int flag=1,flagflag=0;
    phead=Read_File();
    printf("\t\t\t\t\t请输入您想查询的宠物类型:");
    scanf("%s",pettype);
    printf("\n\t\t\t\t\t请输入您想查询的宠物价格范围(由低到高):");
    scanf("%f%f",&petprice1,&petprice2);
    if(petprice2<petprice1)  //若前高后低，则交换
    {
        temp=petprice1;petprice1=petprice2;petprice2=temp;
    }
    if(phead==NULL)
    {
        printf("宠物信息为空,无法查询!\n");
        return;
    }
    t=phead;
    while(t!=NULL)
    {
        if((strcmp(t->type,pettype)==0)&&((t->price>=petprice1)&&(t->price<=petprice2)))  //同时符合两种要求
        {
            if(flag==1)  //符合要求的第一个输出要有表头
            {
                printf("\n\t\t\t\t\t已找到该宠物,详细信息如下:\n");
                printf("\t\t----------------------------------------------------------------------------------------\n");
                printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
                printf("\t\t----------------------------------------------------------------------------------------\n");
                printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
                flag=0;
            }
            else
            {
                printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
            }
            flagflag=1;
        }
        t=t->next;
    }
    if(flagflag==0)
    {
        getchar();
        printf("\n\t\t\t\t\t未找到该宠物信息,查询失败!按任意键返回.\n");
    }
    else
    {
        getchar();
        printf("\n\t\t\t\t\t按任意键返回.\n");
    }
    getch();
}
void TypeAgeSearch()  //按种类和年龄查询
{
    system("clear");
    TypeAgeSearch_head();
    struct pet *phead,*t;
    char pettype[20];
    float petage1,petage2,temp;
    int flag=1,flagflag=0;
    phead=Read_File();
    printf("\t\t\t\t\t请输入您想查询的宠物类型:");
    scanf("%s",pettype);
    printf("\n\t\t\t\t\t请输入您想查询的宠物年龄范围(由低到高):");
    scanf("%f%f",&petage1,&petage2);
    if(petage2<petage1)
    {
        temp=petage1;petage1=petage2;petage2=temp;
    }
    if(phead==NULL)
    {
        printf("宠物信息为空,无法查询!\n");
        return;
    }
    t=phead;
    while(t!=NULL)
    {
        if((strcmp(t->type,pettype)==0)&&((t->age>=petage1)&&(t->age<=petage2)))
        {
            if(flag==1)
            {
                printf("\n\t\t\t\t\t已找到该宠物,详细信息如下:\n");
                printf("\t\t----------------------------------------------------------------------------------------\n");
                printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
                printf("\t\t----------------------------------------------------------------------------------------\n");
                printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
                flag=0;
            }
            else
            {
                printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
            }
            flagflag=1;
        }
        t=t->next;
    }
    if(flagflag==0)
    {
        getchar();
        printf("\n\t\t\t\t\t未找到该宠物信息,查询失败!按任意键返回.\n");
    }
    else
    {
        getchar();
        printf("\n\t\t\t\t\t按任意键返回.\n");
    }
    getch();
}
void Count()  //统计宠物信息
{
    int choice;
    do{
        system("clear");
        printf("\n\n\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*                 1. 简单统计                  *|\n");
	    printf("\t\t\t\t|*                 2. 综合统计                  *|\n");
	    printf("\t\t\t\t|*                 0. 退出                      *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——2):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        switch(choice)
        {
            case 1:SimpleCount();    break;
            case 2:MultipleCount();  break;
            case 0:return;           break;
        }
    }while(choice!=0);
}
void SimpleCount()  //简单统计
{
    int choice;
    do{
        system("clear");
        printf("\n\n\n\n");
	    printf("\t\t\t\t|================================================|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*               简单统计宠物信息               *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*                 1.按类型统计                 *|\n");
	    printf("\t\t\t\t|*                 2.按性别统计                 *|\n");
	    printf("\t\t\t\t|*                 0.退出                       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——2):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        switch(choice)
        {
            case 1:TypeCount();    break;
            case 2:SexCount();    break;
            case 0:return;        break;
        }
    }while(choice!=0);
}
void TypeCount()  //按种类统计
{
    system("clear");
    TypeCount_head();
    struct pet *phead,*t;
    int gou,mao,tu,zhu,niao,shu;
    gou=mao=tu=zhu=niao=shu=0;
    phead=Read_File();
    t=phead;
    while(t!=NULL)
    {
        if(strcmp(t->type,"狗")==0) gou++;
        if(strcmp(t->type,"猫")==0) mao++;
        if(strcmp(t->type,"兔")==0) tu++;
        if(strcmp(t->type,"猪")==0) zhu++;
        if(strcmp(t->type,"鸟")==0) niao++;
        if(strcmp(t->type,"鼠")==0) shu++;
        t=t->next;
    }
    printf("\t\t\t\t\t统计结果如下:\n");
    printf("\n\t\t\t\t\t狗有%d只，猫有%d只，兔有%d只。",gou,mao,tu);
    printf("\n\t\t\t\t\t猪有%d只，鸟有%d只，鼠有%d只。\n",zhu,niao,shu);
    printf("\n\t\t\t\t\t按任意键返回.");
    getch();
}
void SexCount()  //按性别统计
{
    system("clear");
    SexCount_head();
    struct pet *phead,*t;
    int boys,girls;
    boys=girls=0;
    phead=Read_File();
    t=phead;
    while(t!=NULL)
    {
        if(strcmp(t->sex,"B")==0) boys++;
        if(strcmp(t->sex,"G")==0) girls++;
        t=t->next;
    }
    printf("\t\t\t\t\t统计结果如下:\n");
    printf("\n\t\t\t\t\tBoys有%d只，Girls有%d只。\n",boys,girls);
    printf("\n\t\t\t\t\t按任意键返回.");
    getch();
}
void MultipleCount()  //综合统计
{
    system("clear");
    printf("\n\n\n\n");
    printf("\t\t\t\t|================================================|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*       ***欢迎使用安生萌宠店管理系统***       *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*----------------------------------------------*|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*               综合统计宠物信息               *|\n");
    printf("\t\t\t\t|*                                              *|\n");
    printf("\t\t\t\t|*==============================================*|\n");
    printf("\n\n");
    struct pet *phead,*t;
    phead=Read_File();
    t=phead;
    int gou1,mao1,tu1,zhu1,niao1,shu1;
    int gou2,mao2,tu2,zhu2,niao2,shu2;
    int gou3,mao3,tu3,zhu3,niao3,shu3;
    int gou4,mao4,tu4,zhu4,niao4,shu4;
    int gou5,mao5,tu5,zhu5,niao5,shu5;
    int gou6,mao6,tu6,zhu6,niao6,shu6;
    gou1=mao1=tu1=zhu1=niao1=shu1=0;
    gou2=mao2=tu2=zhu2=niao2=shu2=0;
    gou3=mao3=tu3=zhu3=niao3=shu3=0;
    gou4=mao4=tu4=zhu4=niao4=shu4=0;
    gou5=mao5=tu5=zhu5=niao5=shu5=0;
    gou6=mao6=tu6=zhu6=niao6=shu6=0;
    while(t!=NULL)
    {
        if(t->price>0&&t->price<=250)
        {
            if(strcmp(t->type,"狗")==0) gou1++;
            if(strcmp(t->type,"猫")==0) mao1++;
            if(strcmp(t->type,"兔")==0) tu1++;
            if(strcmp(t->type,"猪")==0) zhu1++;
            if(strcmp(t->type,"鸟")==0) niao1++;
            if(strcmp(t->type,"鼠")==0) shu1++;
        }
        if(t->price>250&&t->price<=500)
        {
            if(strcmp(t->type,"狗")==0) gou2++;
            if(strcmp(t->type,"猫")==0) mao2++;
            if(strcmp(t->type,"兔")==0) tu2++;
            if(strcmp(t->type,"猪")==0) zhu2++;
            if(strcmp(t->type,"鸟")==0) niao2++;
            if(strcmp(t->type,"鼠")==0) shu2++;
        }
        if(t->price>500&&t->price<=1000)
        {
            if(strcmp(t->type,"狗")==0) gou3++;
            if(strcmp(t->type,"猫")==0) mao3++;
            if(strcmp(t->type,"兔")==0) tu3++;
            if(strcmp(t->type,"猪")==0) zhu3++;
            if(strcmp(t->type,"鸟")==0) niao3++;
            if(strcmp(t->type,"鼠")==0) shu3++;
        }
        if(t->price>1000&&t->price<=2000)
        {
            if(strcmp(t->type,"狗")==0) gou4++;
            if(strcmp(t->type,"猫")==0) mao4++;
            if(strcmp(t->type,"兔")==0) tu4++;
            if(strcmp(t->type,"猪")==0) zhu4++;
            if(strcmp(t->type,"鸟")==0) niao4++;
            if(strcmp(t->type,"鼠")==0) shu4++;
        }
        if(t->price>2000&&t->price<=5000)
        {
            if(strcmp(t->type,"狗")==0) gou5++;
            if(strcmp(t->type,"猫")==0) mao5++;
            if(strcmp(t->type,"兔")==0) tu5++;
            if(strcmp(t->type,"猪")==0) zhu5++;
            if(strcmp(t->type,"鸟")==0) niao5++;
            if(strcmp(t->type,"鼠")==0) shu5++;
        }
        if(t->price>5000)
        {
            if(strcmp(t->type,"狗")==0) gou6++;
            if(strcmp(t->type,"猫")==0) mao6++;
            if(strcmp(t->type,"兔")==0) tu6++;
            if(strcmp(t->type,"猪")==0) zhu6++;
            if(strcmp(t->type,"鸟")==0) niao6++;
            if(strcmp(t->type,"鼠")==0) shu6++;
        }
        t=t->next;
    }
    printf("\t\t\t\t\t\t   统计结果如下:\n");
    printf("\t\t-------------------------------------------------------------------------------\n");
    printf("\t\t|  价格/类型  |    狗    |    猫    |    兔    |    猪    |    鸟    |   鼠   |\n");
    printf("\t\t-------------------------------------------------------------------------------\n");
    printf("\t\t|    0--250   |     %d    |     %d    |     %d    |     %d    |    %d     |    %d   |\n",gou1,mao1,tu1,zhu1,niao1,shu1);
    printf("\t\t|  250--500   |     %d    |     %d    |     %d    |     %d    |    %d     |    %d   |\n",gou2,mao2,tu2,zhu2,niao2,shu2);
    printf("\t\t|  500--1000  |     %d    |     %d    |     %d    |     %d    |    %d     |    %d   |\n",gou3,mao3,tu3,zhu3,niao3,shu3);
    printf("\t\t| 1000--2000  |     %d    |     %d    |     %d    |     %d    |    %d     |    %d   |\n",gou4,mao4,tu4,zhu4,niao4,shu4);
    printf("\t\t| 2000--5000  |     %d    |     %d    |     %d    |     %d    |    %d     |    %d   |\n",gou5,mao5,tu5,zhu5,niao5,shu5);
    printf("\t\t|    5000+    |     %d    |     %d    |     %d    |     %d    |    %d     |    %d   |\n",gou6,mao6,tu6,zhu6,niao6,shu6);
    printf("\t\t-------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\t\t按任意键返回.");
    getch();

}
void Sort()  //排序宠物信息
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
	    printf("\t\t\t\t|*                 宠物信息排序                 *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*----------------------------------------------*|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*                 1.按编号升序                 *|\n");
	    printf("\t\t\t\t|*                 2.按价格升序                 *|\n");
	    printf("\t\t\t\t|*                 3.按年龄降序                 *|\n");
	    printf("\t\t\t\t|*                 4.按体型降序                 *|\n");
	    printf("\t\t\t\t|*                 0.退出                       *|\n");
	    printf("\t\t\t\t|*                                              *|\n");
	    printf("\t\t\t\t|*==============================================*|\n");
        printf("\n\n");
        printf("\t\t\t\t请选择您要进行的操作(输入0——4):");
        scanf("%d",&choice);
        getchar();
        printf("\t\t\t\t按任意键进入下一步...");
        getch();
        switch(choice)
        {
            case 1:IdSort();      break;
            case 2:PriceSort();   break;
            case 3:AgeSort();     break;
            case 4:ShapeSort();   break;
            case 0:return;        break;
        }
    }while(choice!=0);
}
void IdSort()  //按编号升序
{
    system("clear");
    IdSort_head();
    struct pet *p1,*p2,*phead;
    phead=Read_File();
    char type[10];
    int id;
    char name[20];
    float age;
    char sex[10];
    char color[10];
    int shape;
    char variety[20];
    float price;
    for(p1=phead;p1!=NULL;p1=p1->next)
        for(p2=p1->next;p2!=NULL;p2=p2->next)
            if(p1->id > p2->id)  //如果前者id大于后者，则交换结构体每一个成员
            {
                id=p1->id;
                strcpy(type,p1->type);
                strcpy(name,p1->name);
                age=p1->age;
                strcpy(sex,p1->sex);
                strcpy(color,p1->color);
                shape=p1->shape;
                strcpy(variety,p1->variety);
                price=p1->price;

                p1->id=p2->id;
                strcpy(p1->type,p2->type);
                strcpy(p1->name,p2->name);
                p1->age=p2->age;
                strcpy(p1->sex,p2->sex);
                strcpy(p1->color,p2->color);
                p1->shape=p2->shape;
                strcpy(p1->variety,p2->variety);
                p1->price=p2->price;

                p2->id=id;
                strcpy(p2->type,type);
                strcpy(p2->name,name);
                p2->age=age;
                strcpy(p2->sex,sex);
                strcpy(p2->color,color);
                p2->shape=shape;
                strcpy(p2->variety,variety);
                p2->price=price;
            }
    SortOutput(phead);  //将排序结果输出
}
void AgeSort()  //按年龄降序
{
    system("clear");
    AgeSort_head();
    struct pet *p1,*p2,*phead;
    phead=Read_File();
    char type[10];
    int id;
    char name[20];
    float age;
    char sex[10];
    char color[10];
    int shape;
    char variety[20];
    float price;
    for(p1=phead;p1!=NULL;p1=p1->next)
        for(p2=p1->next;p2!=NULL;p2=p2->next)
            if(p1->age < p2->age)
            {
                age=p1->age;
                strcpy(type,p1->type);
                strcpy(name,p1->name);
                id=p1->id;
                strcpy(sex,p1->sex);
                strcpy(color,p1->color);
                shape=p1->shape;
                strcpy(variety,p1->variety);
                price=p1->price;

                p1->age=p2->age;
                strcpy(p1->type,p2->type);
                strcpy(p1->name,p2->name);
                p1->id=p2->id;
                strcpy(p1->sex,p2->sex);
                strcpy(p1->color,p2->color);
                p1->shape=p2->shape;
                strcpy(p1->variety,p2->variety);
                p1->price=p2->price;

                p2->age=age;
                strcpy(p2->type,type);
                strcpy(p2->name,name);
                p2->id=id;
                strcpy(p2->sex,sex);
                strcpy(p2->color,color);
                p2->shape=shape;
                strcpy(p2->variety,variety);
                p2->price=price;
            }
    SortOutput(phead);
}
void PriceSort()  //按价格升序
{
    system("clear");
    PriceSort_head();
    struct pet *p1,*p2,*phead;
    phead=Read_File();
    char type[10];
    int id;
    char name[20];
    float age;
    char sex[10];
    char color[10];
    int shape;
    char variety[20];
    float price;
    for(p1=phead;p1!=NULL;p1=p1->next)
        for(p2=p1->next;p2!=NULL;p2=p2->next)
            if(p1->price > p2->price)
            {
                price=p1->price;
                strcpy(type,p1->type);
                strcpy(name,p1->name);
                id=p1->id;
                strcpy(sex,p1->sex);
                strcpy(color,p1->color);
                shape=p1->shape;
                strcpy(variety,p1->variety);
                age=p1->age;

                p1->price=p2->price;
                strcpy(p1->type,p2->type);
                strcpy(p1->name,p2->name);
                p1->id=p2->id;
                strcpy(p1->sex,p2->sex);
                strcpy(p1->color,p2->color);
                p1->shape=p2->shape;
                strcpy(p1->variety,p2->variety);
                p1->age=p2->age;

                p2->price=price;
                strcpy(p2->type,type);
                strcpy(p2->name,name);
                p2->id=id;
                strcpy(p2->sex,sex);
                strcpy(p2->color,color);
                p2->shape=shape;
                strcpy(p2->variety,variety);
                p2->age=age;
            }
    SortOutput(phead);
}
void ShapeSort()  //按体型降序
{
    system("clear");
    ShapeSort_head();
    struct pet *p1,*p2,*phead;
    phead=Read_File();
    char type[10];
    int id;
    char name[20];
    float age;
    char sex[10];
    char color[10];
    int shape;
    char variety[20];
    float price;
    for(p1=phead;p1!=NULL;p1=p1->next)
        for(p2=p1->next;p2!=NULL;p2=p2->next)
            if(p1->shape < p2->shape)
            {
                age=p1->age;
                strcpy(type,p1->type);
                strcpy(name,p1->name);
                id=p1->id;
                strcpy(sex,p1->sex);
                strcpy(color,p1->color);
                shape=p1->shape;
                strcpy(variety,p1->variety);
                price=p1->price;

                p1->age=p2->age;
                strcpy(p1->type,p2->type);
                strcpy(p1->name,p2->name);
                p1->id=p2->id;
                strcpy(p1->sex,p2->sex);
                strcpy(p1->color,p2->color);
                p1->shape=p2->shape;
                strcpy(p1->variety,p2->variety);
                p1->price=p2->price;

                p2->age=age;
                strcpy(p2->type,type);
                strcpy(p2->name,name);
                p2->id=id;
                strcpy(p2->sex,sex);
                strcpy(p2->color,color);
                p2->shape=shape;
                strcpy(p2->variety,variety);
                p2->price=price;
            }
    SortOutput(phead);
}
void SortOutput(struct pet *phead)  //将排序结果输出
{
    struct pet *t;
    t=phead;
    printf("\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
    printf("\t\t----------------------------------------------------------------------------------------\n");
    if(t==NULL)
    {
        printf("\n\t\t\t\t\t\t宠物信息为空!\n");
    }
    while(t!=NULL)//当前结点不为空时，执行输出信息
    {
        printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
        t=t->next;
    }
    printf("\n\t\t\t\t\t\t排序完成!按任意键返回.");
    getch();
}
void Output()  //输出宠物信息
{
    system("clear");
    Output_head();
    struct pet *t;
    t=Read_File();
    printf("\t\t----------------------------------------------------------------------------------------\n");
    printf("\t\t  类型      编号      姓名      年龄      性别      颜色      体型      品种      价格  \n");
    printf("\t\t----------------------------------------------------------------------------------------\n");
    if(t==NULL)
    {
        printf("\n\t\t\t\t\t\t宠物信息为空!\n");
    }
    while(t!=NULL)//当前结点不为空时，执行输出信息
    {
        printf("\t\t  %-11s%-10d%-12s%-10.1f%-10s%-12s%-10d%-12s%-10.2f\n",t->type,t->id,t->name,t->age,t->sex,t->color,t->shape,t->variety,t->price);
        t=t->next;
    }
    printf("\n\t\t\t\t\t\t输出完成!按任意键返回.");
    getch();
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

