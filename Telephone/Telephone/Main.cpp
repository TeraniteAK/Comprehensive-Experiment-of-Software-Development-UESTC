#include <stdio.h>
#include "Contact.h"

int main()
{
	int a;   //指令变量
	Sqlist telephonehash, namehash;   //定义两个哈希表 
	Sqlist * pt = &telephonehash;
	Sqlist * pn = &namehash;  //定义两个哈希表指针并分别指向哈希表首地址，用于函数传参 
	int size = 200; //定义电话本容量 
	Contact * pnow;   //Contact指针变量 指向当前联系人 规定：1.搜索到联系人后立刻指向搜索到的联系人 
	int telnum;    //存储当前联系人在telephonehash中的下标 
	int namenum;   //存储当前联系人在namehash中的下标 
	char name[20], telephone[15], address[20];  //记录键盘输入的name，telephone和address信息（不管是用于新建还是查找）
	
	InitialContact(size, pt, pn); //初始化操作 
	
	for(;;)
	{
		printf("欢迎使用电话号码本,请选择功能：\n");
        printf("按1:创建新联系人\n");
        printf("按2:按姓名查找联系人\n");
        printf("按3:按电话号码查找联系人\n");
        printf("按4:查看当前电话号码本状态\n");
        printf("按5:删除联系人\n");
        printf("按0:退出程序\n");
        printf("\n");
        scanf("%d",&a);
	switch(a)
    {
    	case 0:
    	{
    		printf("感谢您的使用！\0");
    		free(telephonehash.elem);
    		telephonehash.elem = NULL;
    		free(namehash.elem);
    		namehash.elem = NULL;
   	    	return 0;
	    }
	    case 1:
    	{
    		GetInfo(name, telephone, address);  //先获得信息 
    		CreateContact(pt, pn, name, telephone, address);  //再创建 
    		break;
	    }
	    case 2:
    	{
    		GetName(name);
    		SearchName(name, pn, pt, pnow, name, telephone, address);
    		break;
	    }
	    case 3:
    	{
    		GetTelephone(telephone);
    		SearchTelephone(telephone, pt, pn, pnow, name, telephone, address);
    		break;
	    }
	    case 4:
    	{
    		TelephoneInfo(telephonehash, namehash);
    		break;
	    }
	    case 5:
    	{
    		GetName(name);
    		PosiDeleteContact(name, pn, pt);
    		break;
	    }
	    default:
	    {
    		printf("非法命令！\n");
    		printf("\n");
    		break;
    	}
    }
	}
}

/*功能说明：
1.若有两个重名的人在电话本里，按名字查找该人只会出现其中一个人
2.若有两个同电话号码的人在电话本里，按名字查找该人只会出现其中一个人
3.查找时必须输入全名或全电话，否则程序会出错
4.目前时间复杂度还存在问题，需要检查是哪里时间比较长（个人觉得是trans函数的时间太长了，其实跟hash算法没有关系，hash算法是没有问题的） 
*/
