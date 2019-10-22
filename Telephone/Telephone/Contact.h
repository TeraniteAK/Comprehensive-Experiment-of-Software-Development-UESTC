//Contact.h                         //电话号码本结构及其操作 

#include<stdlib.h>

 
#define p 199

typedef struct contact              //定义结构体联系人 包含元素：姓名 电话 地址（为字符串类型） 标志变量int型表示该节点是否已经存了人了 
{
	char name[20];
	char telephone[15];
	char address[20];
	int flag;                       //标志变量 =0或者未赋值时表示此处无人 =1表示已经有人存在这里了 
}Contact;

typedef struct sqlist               //定义结构体顺序表 包含：Contact型指针用于指向第一个 nn表示现在已有联系人 mm表示电话本最大容量 
{
	Contact * elem;
	int nn;
	int mm;
}Sqlist;

void InitialContact(int size, Sqlist * telephonehash, Sqlist * namehash)         //Contact初始化操作 形参为：电话本容量size 
{ 
                                                                   //telephonehash表示按电话号码的哈希表，namehash表示按名字查找的哈希表 
    int i;
	telephonehash->elem = (Contact *)malloc(size*sizeof(Contact)); //初始化telephonehash 
	if(telephonehash->elem == NULL)
	{
		printf("内存分配出错！\n");
		return;
	}
	telephonehash->nn = 0;
	telephonehash->mm = size;
	
	/*for(i=0;i<200;i++)        //标记为空 
	{
		((telephonehash->elem)+i)->flag == 0;
	}*/
	
	namehash->elem = (Contact *)malloc(size*sizeof(Contact));      //初始化namehash 
	if(namehash->elem == NULL)
	{
		printf("内存分配出错！\n");
		return;
	}
	namehash->nn = 0;
	namehash->mm = size;
	
	/*for(i=0;i<200;i++)        //标记为空 
	{
		((namehash->elem)+i)->flag == 0;
	}*/
	
	
	return;
}

void TelephoneInfo(Sqlist telephonehash, Sqlist namehash)   //显示当前电话本的信息 
{
    printf("\n");
	printf("当前联系人数量：%d\n",telephonehash.nn);
	printf("当前电话本容量：%d\n",telephonehash.mm);
	printf("\n");
	return;
}

int Hashfunction(int key)   //哈希函数运算操作：除留取余法 
{                         
	return key%p;    //返回哈希函数值（作为数组下标使用） 
}

void strcpy( char *strDest, const char *strSrc ) 
{
  while( (*strDest++ = * strSrc++) != '\0');
}

int strcmp(const char *str1,const char *str2)    //两字符串相等：返回0 否则不是0 
{
    while(*str1 == *str2)
    {
        if(*str1 == '\0')
            return 0;
         
        str1++;
        str2++;
    }
    return 1;
}

int Trans(char * a)  //把字符串转换为整型并返回该整型数 
{
	int i = 0;
	int s = 0;
	while((*(a+i)) != '\0')
	{
		s = s + (*(a+i));
		i++;
	}
	return s;
} 

int Conflict(int i)  //冲突处理函数 ：使用线性探测再散列的开放地址法 
{
	i =  (i+1)%p;
	return i;        //返回值为新找的下标值 
}

void GetInfo(char * inputname, char * inputtelephone, char * inputaddress)   //获取信息操作，用于在主函数中提示用户输入信息传递该信息到主函数中 
{
	printf("\n");
	printf("请输入联系人姓名：\n");
	scanf("%s", inputname);
	printf("请输入联系人电话号码：\n");
	scanf("%s", inputtelephone);
	printf("请输入联系人地址：\n");
	scanf("%s", inputaddress);
	return;
}

void GetName(char * inputname)
{
	printf("\n");
	printf("请输入联系人姓名：\n");
	scanf("%s", inputname);
	return;
}

void GetTelephone(char * inputtelephone)
{
	printf("\n");
	printf("请输入联系人电话号码：\n");
	scanf("%s", inputtelephone);
	return;
}

void CreateContact(Sqlist * telephonehash, Sqlist * namehash, char newname[], char newtelephone[], char newaddress[])  //创建联系人操作,形参为：新名字 新电话 新地址 Sqlist类型的 
{                                                                                                                 //两个哈希表
                                                                                                             
    int i =  Hashfunction(Trans(newtelephone));                  //进行哈希运算，算出下标值（对电话号码进行哈希运算） 
    int j =  Hashfunction(Trans(newname));                  //进行哈希运算，算出下标值（对姓名进行哈希运算）
    
	if(telephonehash->nn >= telephonehash->mm)  //超出容量，返回值为0，表示出错
	{
		printf("出错：超出电话本容量！\n");     //提示：超出容量，出错 
		return;   //返回 
	}
	 
	if(telephonehash->nn < telephonehash->mm)
	{
		
		while((telephonehash->elem+i)->flag == 1)                //判断该位置是否有人，如果有，使用冲突处理函数，直到该位置没有人 
		{
			i = Conflict(i);
		}
        strcpy( (telephonehash->elem+i)->name, newname);  //给名字赋值 
		strcpy( (telephonehash->elem+i)->telephone, newtelephone);  //给电话号码赋值
		strcpy( (telephonehash->elem+i)->address, newaddress);  //给地址赋值
		(telephonehash->elem+i)->flag = 1;   //给标志变量赋值，表示有人了 
		telephonehash->nn++;      //现有元素数量+1 
	}
	
	if(namehash->nn >= namehash->mm)  //超出容量，返回值为0，表示出错
	{
		printf("出错：超出电话本容量！\n");     //提示：超出容量，出错 
		return;   //返回 
	}
	
	if(namehash->nn < namehash->mm)
	{
		 
		while((namehash->elem+j)->flag == 1)                     //判断该位置是否有人，如果有，使用冲突处理函数，直到该位置没有人 
		{
			j = Conflict(j);
		}
        strcpy( (namehash->elem+j)->name, newname);  //给名字赋值 
		strcpy( (namehash->elem+j)->telephone, newtelephone);  //给电话号码赋值
		strcpy( (namehash->elem+j)->address, newaddress);  //给地址赋值
		(namehash->elem+j)->flag = 1;   //给标志变量赋值，表示有人了
		namehash->nn++;      //现有元素数量+1
		printf("\n");
		printf("创建成功!\n");  //提示：联系人创建成功 
		printf("\n");
		return;  //返回
	}
}

void DeleteContact(Contact * now, Sqlist * namehash, Sqlist * telephonehash)     //删除联系人操作 
{
	now->flag = 0;
	namehash->nn--;
	telephonehash->nn--;
	return;
}

void SearchName(char * inputname, Sqlist * namehash, Sqlist * telephonehash, Contact * pnow, char *name, char *telephone, char*address)    //按名字查找操作  形参 1.输入的姓名 2.对应的namehash表  3.namehash对应下标 4.telephonehash对应下标 
{
	int j = Hashfunction(Trans(inputname));  //计算输入名字的哈希值
	if( ((namehash->elem)+j)->flag != 1)        //查无此人
	{
		printf("\n");
		printf("未找到该联系人！\n");     //加一个是否创建该联系人 
		printf("\n");
		return;
	} 
	if( ((namehash->elem)+j)->flag == 1)   //如果该位置有人 
	{
		if((strcmp(inputname, ((namehash->elem)+j)->name)) == 0)//如果就是这个人
		{
			printf("查询结果：\n姓名：%s\n电话：%s\n地址：%s\n",((namehash->elem)+j)->name,((namehash->elem)+j)->telephone,((namehash->elem)+j)->address);  //显示查找结果 
			int i; //指令变量 
			pnow = (namehash->elem)+j;
			printf("\n");
		    printf("是否修改联系人信息？请按键实现功能：\n");   //修改联系人信息操作：先删除，再输入新的信息，再创建 
            printf("按1:是\n");
            printf("按2:否\n");
            printf("\n");
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //其中实参pnow是main函数中的变量 
	            	GetInfo(name, telephone, address);  //这三个实参都是main函数中的变量 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//后三个是main函数中的变量
	            }
	            case 2:
	            {
            		break;
            	}
            	default:
            	{
	            	printf("非法输入！\n");
	            	printf("\n");
	            }
            }
		}
		else 
		{
			while((strcmp(inputname, ((namehash->elem)+j)->name)) != 0)  //如果不是这个 循环用冲突函数找i 直到找到这个人 
			{
				j = Conflict(j);
			}
			printf("查询结果：\n姓名：%s\n电话：%s\n地址：%s\n",((namehash->elem)+j)->name,((namehash->elem)+j)->telephone,((namehash->elem)+j)->address);  //显示查找结果 
			pnow = (namehash->elem)+j;
			printf("\n");
		    printf("是否修改联系人信息？请按键实现功能：\n");   //修改联系人信息操作：先删除，再输入新的信息，再创建 
            printf("按1:是\n");
            printf("按2:否\n");
            printf("\n");
            int i;
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //其中实参pnow是main函数中的变量 
	            	GetInfo(name, telephone, address);  //这三个实参都是main函数中的变量 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//后三个是main函数中的变量
	            }
	            case 2:
	            {
            		break;
            	}
           		default:
            	{
	            	printf("非法输入！\n");
	            	printf("\n");
	            }
            }
		}
	}      
	return;   
}

void SearchTelephone(char * inputtelephone, Sqlist * telephonehash, Sqlist * namehash, Contact * pnow, char *name, char *telephone, char*address)   //按电话号码查找操作  形参 1.输入的电话号码 2.对应的telephonehash表 
{
	int i;
	for(i=0;i<200;i++)
	{
		if(((telephonehash->elem)+i)->flag == 1)
		{
			printf("查询结果：\n姓名：%s\n电话：%s\n地址：%s\n",((telephonehash->elem)+i)->name,((telephonehash->elem)+i)->telephone,((telephonehash->elem)+i)->address);  //显示查找结果 
			printf("\n");
			pnow = (telephonehash->elem)+i;
			printf("\n");
		} 
		else continue;
	}
	
    /*int i = Hashfunction(Trans(inputtelephone));  //计算输入名字的哈希值
	if(((telephonehash->elem)+i)->flag != 1)        //查无此人
	{
		printf("\n");
		printf("未找到该联系人！\n");     //加一个是否创建该联系人 
		printf("\n");
		return;
	} 
	if(((telephonehash->elem)+i)->flag == 1)   //如果该位置有人 
	{
		if((strcmp(inputtelephone, ((telephonehash->elem)+i)->telephone)) == 0)//如果就是这个人 
		{
			printf("查询结果：\n姓名：%s\n电话：%s\n地址：%s\n",((telephonehash->elem)+i)->name,((telephonehash->elem)+i)->telephone,((telephonehash->elem)+i)->address);  //显示查找结果 
			printf("\n");
			pnow = (telephonehash->elem)+i;
			printf("\n");
			printf("是否修改联系人信息？请按键实现功能：\n");   //修改联系人信息操作：先删除，再输入新的信息，再创建 
            printf("按1:是\n");
            printf("按2:否\n");
            printf("\n");
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //其中实参pnow是main函数中的变量 
	            	GetInfo(name, telephone, address);  //这三个实参都是main函数中的变量 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//后三个是main函数中的变量
	            }
	            case 2:
	            {
            		break;
            	}
            }
		}
		else 
		{
			while((strcmp(inputtelephone, ((telephonehash->elem)+i)->telephone)) != 0)  //如果不是这个 循环用冲突函数找i 直到找到这个人 
			{
				i = Conflict(i);
			}
			printf("查询结果：\n姓名：%s\n电话：%s\n地址：%s\n",((telephonehash->elem)+i)->name,((telephonehash->elem)+i)->telephone,((telephonehash->elem)+i)->address);  //显示查找结果 
		    pnow = (namehash->elem)+i;
		    printf("\n");
			printf("是否修改联系人信息？请按键实现功能：\n");   //修改联系人信息操作：先删除，再输入新的信息，再创建 
            printf("按1:是\n");
            printf("按2:否\n");
            printf("\n");
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //其中实参pnow是main函数中的变量 
	            	GetInfo(name, telephone, address);  //这三个实参都是main函数中的变量 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//后三个是main函数中的变量
	            }
	            case 2:
	            {
            		break;
            	}
            }
		}
	}*/     
	return; 
}

void PosiDeleteContact(char * inputname, Sqlist * namehash, Sqlist * telephonehash)
{
	int j = Hashfunction(Trans(inputname));  //计算输入名字的哈希值
	if( ((namehash->elem)+j)->flag != 1)        //查无此人
	{
		printf("未找到该联系人！\n");     //加一个是否创建该联系人 
		return;
	} 
	if( ((namehash->elem)+j)->flag == 1)   //如果该位置有人 
	{
		if((strcmp(inputname, ((namehash->elem)+j)->name)) == 0)//如果就是这个人
		{
			((namehash->elem)+j)->flag = 0;
			namehash->nn--;
		}
		else 
		{
			while((strcmp(inputname, ((namehash->elem)+j)->name)) != 0)  //如果不是这个 循环用冲突函数找i 直到找到这个人 
			{
				j = Conflict(j);
			}
			((namehash->elem)+j)->flag = 0;
			namehash->nn--;
		}
	}
	
	char *inputtelephone = ((namehash->elem)+j)->telephone;
	j = Hashfunction(Trans(inputtelephone));  //计算输入名字的哈希值
	if( ((telephonehash->elem)+j)->flag != 1)        //查无此人
	{
		printf("未找到该联系人！\n");     //加一个是否创建该联系人 
		return;
	} 
	if( ((telephonehash->elem)+j)->flag == 1)   //如果该位置有人 
	{
		if((strcmp(inputtelephone, ((telephonehash->elem)+j)->telephone)) == 0)//如果就是这个人
		{
			((telephonehash->elem)+j)->flag = 0;
			telephonehash->nn--;
			printf("\n");
			printf("删除成功！\n");
			printf("\n");
		}
		else 
		{
			while((strcmp(inputtelephone, ((telephonehash->elem)+j)->telephone)) != 0)  //如果不是这个 循环用冲突函数找i 直到找到这个人 
			{
				j = Conflict(j);
			}
			((namehash->elem)+j)->flag = 0;
			namehash->nn--;
			printf("\n");
			printf("删除成功！\n");
			printf("\n");
		}
	}
	return;   
}

