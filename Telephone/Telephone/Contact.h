//Contact.h                         //�绰���뱾�ṹ������� 

#include<stdlib.h>

 
#define p 199

typedef struct contact              //����ṹ����ϵ�� ����Ԫ�أ����� �绰 ��ַ��Ϊ�ַ������ͣ� ��־����int�ͱ�ʾ�ýڵ��Ƿ��Ѿ��������� 
{
	char name[20];
	char telephone[15];
	char address[20];
	int flag;                       //��־���� =0����δ��ֵʱ��ʾ�˴����� =1��ʾ�Ѿ����˴��������� 
}Contact;

typedef struct sqlist               //����ṹ��˳��� ������Contact��ָ������ָ���һ�� nn��ʾ����������ϵ�� mm��ʾ�绰��������� 
{
	Contact * elem;
	int nn;
	int mm;
}Sqlist;

void InitialContact(int size, Sqlist * telephonehash, Sqlist * namehash)         //Contact��ʼ������ �β�Ϊ���绰������size 
{ 
                                                                   //telephonehash��ʾ���绰����Ĺ�ϣ��namehash��ʾ�����ֲ��ҵĹ�ϣ�� 
    int i;
	telephonehash->elem = (Contact *)malloc(size*sizeof(Contact)); //��ʼ��telephonehash 
	if(telephonehash->elem == NULL)
	{
		printf("�ڴ�������\n");
		return;
	}
	telephonehash->nn = 0;
	telephonehash->mm = size;
	
	/*for(i=0;i<200;i++)        //���Ϊ�� 
	{
		((telephonehash->elem)+i)->flag == 0;
	}*/
	
	namehash->elem = (Contact *)malloc(size*sizeof(Contact));      //��ʼ��namehash 
	if(namehash->elem == NULL)
	{
		printf("�ڴ�������\n");
		return;
	}
	namehash->nn = 0;
	namehash->mm = size;
	
	/*for(i=0;i<200;i++)        //���Ϊ�� 
	{
		((namehash->elem)+i)->flag == 0;
	}*/
	
	
	return;
}

void TelephoneInfo(Sqlist telephonehash, Sqlist namehash)   //��ʾ��ǰ�绰������Ϣ 
{
    printf("\n");
	printf("��ǰ��ϵ��������%d\n",telephonehash.nn);
	printf("��ǰ�绰��������%d\n",telephonehash.mm);
	printf("\n");
	return;
}

int Hashfunction(int key)   //��ϣ�����������������ȡ�෨ 
{                         
	return key%p;    //���ع�ϣ����ֵ����Ϊ�����±�ʹ�ã� 
}

void strcpy( char *strDest, const char *strSrc ) 
{
  while( (*strDest++ = * strSrc++) != '\0');
}

int strcmp(const char *str1,const char *str2)    //���ַ�����ȣ�����0 ������0 
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

int Trans(char * a)  //���ַ���ת��Ϊ���Ͳ����ظ������� 
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

int Conflict(int i)  //��ͻ������ ��ʹ������̽����ɢ�еĿ��ŵ�ַ�� 
{
	i =  (i+1)%p;
	return i;        //����ֵΪ���ҵ��±�ֵ 
}

void GetInfo(char * inputname, char * inputtelephone, char * inputaddress)   //��ȡ��Ϣ����������������������ʾ�û�������Ϣ���ݸ���Ϣ���������� 
{
	printf("\n");
	printf("��������ϵ��������\n");
	scanf("%s", inputname);
	printf("��������ϵ�˵绰���룺\n");
	scanf("%s", inputtelephone);
	printf("��������ϵ�˵�ַ��\n");
	scanf("%s", inputaddress);
	return;
}

void GetName(char * inputname)
{
	printf("\n");
	printf("��������ϵ��������\n");
	scanf("%s", inputname);
	return;
}

void GetTelephone(char * inputtelephone)
{
	printf("\n");
	printf("��������ϵ�˵绰���룺\n");
	scanf("%s", inputtelephone);
	return;
}

void CreateContact(Sqlist * telephonehash, Sqlist * namehash, char newname[], char newtelephone[], char newaddress[])  //������ϵ�˲���,�β�Ϊ�������� �µ绰 �µ�ַ Sqlist���͵� 
{                                                                                                                 //������ϣ��
                                                                                                             
    int i =  Hashfunction(Trans(newtelephone));                  //���й�ϣ���㣬����±�ֵ���Ե绰������й�ϣ���㣩 
    int j =  Hashfunction(Trans(newname));                  //���й�ϣ���㣬����±�ֵ�����������й�ϣ���㣩
    
	if(telephonehash->nn >= telephonehash->mm)  //��������������ֵΪ0����ʾ����
	{
		printf("���������绰��������\n");     //��ʾ���������������� 
		return;   //���� 
	}
	 
	if(telephonehash->nn < telephonehash->mm)
	{
		
		while((telephonehash->elem+i)->flag == 1)                //�жϸ�λ���Ƿ����ˣ�����У�ʹ�ó�ͻ��������ֱ����λ��û���� 
		{
			i = Conflict(i);
		}
        strcpy( (telephonehash->elem+i)->name, newname);  //�����ָ�ֵ 
		strcpy( (telephonehash->elem+i)->telephone, newtelephone);  //���绰���븳ֵ
		strcpy( (telephonehash->elem+i)->address, newaddress);  //����ַ��ֵ
		(telephonehash->elem+i)->flag = 1;   //����־������ֵ����ʾ������ 
		telephonehash->nn++;      //����Ԫ������+1 
	}
	
	if(namehash->nn >= namehash->mm)  //��������������ֵΪ0����ʾ����
	{
		printf("���������绰��������\n");     //��ʾ���������������� 
		return;   //���� 
	}
	
	if(namehash->nn < namehash->mm)
	{
		 
		while((namehash->elem+j)->flag == 1)                     //�жϸ�λ���Ƿ����ˣ�����У�ʹ�ó�ͻ��������ֱ����λ��û���� 
		{
			j = Conflict(j);
		}
        strcpy( (namehash->elem+j)->name, newname);  //�����ָ�ֵ 
		strcpy( (namehash->elem+j)->telephone, newtelephone);  //���绰���븳ֵ
		strcpy( (namehash->elem+j)->address, newaddress);  //����ַ��ֵ
		(namehash->elem+j)->flag = 1;   //����־������ֵ����ʾ������
		namehash->nn++;      //����Ԫ������+1
		printf("\n");
		printf("�����ɹ�!\n");  //��ʾ����ϵ�˴����ɹ� 
		printf("\n");
		return;  //����
	}
}

void DeleteContact(Contact * now, Sqlist * namehash, Sqlist * telephonehash)     //ɾ����ϵ�˲��� 
{
	now->flag = 0;
	namehash->nn--;
	telephonehash->nn--;
	return;
}

void SearchName(char * inputname, Sqlist * namehash, Sqlist * telephonehash, Contact * pnow, char *name, char *telephone, char*address)    //�����ֲ��Ҳ���  �β� 1.��������� 2.��Ӧ��namehash��  3.namehash��Ӧ�±� 4.telephonehash��Ӧ�±� 
{
	int j = Hashfunction(Trans(inputname));  //�����������ֵĹ�ϣֵ
	if( ((namehash->elem)+j)->flag != 1)        //���޴���
	{
		printf("\n");
		printf("δ�ҵ�����ϵ�ˣ�\n");     //��һ���Ƿ񴴽�����ϵ�� 
		printf("\n");
		return;
	} 
	if( ((namehash->elem)+j)->flag == 1)   //�����λ������ 
	{
		if((strcmp(inputname, ((namehash->elem)+j)->name)) == 0)//������������
		{
			printf("��ѯ�����\n������%s\n�绰��%s\n��ַ��%s\n",((namehash->elem)+j)->name,((namehash->elem)+j)->telephone,((namehash->elem)+j)->address);  //��ʾ���ҽ�� 
			int i; //ָ����� 
			pnow = (namehash->elem)+j;
			printf("\n");
		    printf("�Ƿ��޸���ϵ����Ϣ���밴��ʵ�ֹ��ܣ�\n");   //�޸���ϵ����Ϣ��������ɾ�����������µ���Ϣ���ٴ��� 
            printf("��1:��\n");
            printf("��2:��\n");
            printf("\n");
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //����ʵ��pnow��main�����еı��� 
	            	GetInfo(name, telephone, address);  //������ʵ�ζ���main�����еı��� 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//��������main�����еı���
	            }
	            case 2:
	            {
            		break;
            	}
            	default:
            	{
	            	printf("�Ƿ����룡\n");
	            	printf("\n");
	            }
            }
		}
		else 
		{
			while((strcmp(inputname, ((namehash->elem)+j)->name)) != 0)  //���������� ѭ���ó�ͻ������i ֱ���ҵ������ 
			{
				j = Conflict(j);
			}
			printf("��ѯ�����\n������%s\n�绰��%s\n��ַ��%s\n",((namehash->elem)+j)->name,((namehash->elem)+j)->telephone,((namehash->elem)+j)->address);  //��ʾ���ҽ�� 
			pnow = (namehash->elem)+j;
			printf("\n");
		    printf("�Ƿ��޸���ϵ����Ϣ���밴��ʵ�ֹ��ܣ�\n");   //�޸���ϵ����Ϣ��������ɾ�����������µ���Ϣ���ٴ��� 
            printf("��1:��\n");
            printf("��2:��\n");
            printf("\n");
            int i;
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //����ʵ��pnow��main�����еı��� 
	            	GetInfo(name, telephone, address);  //������ʵ�ζ���main�����еı��� 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//��������main�����еı���
	            }
	            case 2:
	            {
            		break;
            	}
           		default:
            	{
	            	printf("�Ƿ����룡\n");
	            	printf("\n");
	            }
            }
		}
	}      
	return;   
}

void SearchTelephone(char * inputtelephone, Sqlist * telephonehash, Sqlist * namehash, Contact * pnow, char *name, char *telephone, char*address)   //���绰������Ҳ���  �β� 1.����ĵ绰���� 2.��Ӧ��telephonehash�� 
{
	int i;
	for(i=0;i<200;i++)
	{
		if(((telephonehash->elem)+i)->flag == 1)
		{
			printf("��ѯ�����\n������%s\n�绰��%s\n��ַ��%s\n",((telephonehash->elem)+i)->name,((telephonehash->elem)+i)->telephone,((telephonehash->elem)+i)->address);  //��ʾ���ҽ�� 
			printf("\n");
			pnow = (telephonehash->elem)+i;
			printf("\n");
		} 
		else continue;
	}
	
    /*int i = Hashfunction(Trans(inputtelephone));  //�����������ֵĹ�ϣֵ
	if(((telephonehash->elem)+i)->flag != 1)        //���޴���
	{
		printf("\n");
		printf("δ�ҵ�����ϵ�ˣ�\n");     //��һ���Ƿ񴴽�����ϵ�� 
		printf("\n");
		return;
	} 
	if(((telephonehash->elem)+i)->flag == 1)   //�����λ������ 
	{
		if((strcmp(inputtelephone, ((telephonehash->elem)+i)->telephone)) == 0)//������������ 
		{
			printf("��ѯ�����\n������%s\n�绰��%s\n��ַ��%s\n",((telephonehash->elem)+i)->name,((telephonehash->elem)+i)->telephone,((telephonehash->elem)+i)->address);  //��ʾ���ҽ�� 
			printf("\n");
			pnow = (telephonehash->elem)+i;
			printf("\n");
			printf("�Ƿ��޸���ϵ����Ϣ���밴��ʵ�ֹ��ܣ�\n");   //�޸���ϵ����Ϣ��������ɾ�����������µ���Ϣ���ٴ��� 
            printf("��1:��\n");
            printf("��2:��\n");
            printf("\n");
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //����ʵ��pnow��main�����еı��� 
	            	GetInfo(name, telephone, address);  //������ʵ�ζ���main�����еı��� 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//��������main�����еı���
	            }
	            case 2:
	            {
            		break;
            	}
            }
		}
		else 
		{
			while((strcmp(inputtelephone, ((telephonehash->elem)+i)->telephone)) != 0)  //���������� ѭ���ó�ͻ������i ֱ���ҵ������ 
			{
				i = Conflict(i);
			}
			printf("��ѯ�����\n������%s\n�绰��%s\n��ַ��%s\n",((telephonehash->elem)+i)->name,((telephonehash->elem)+i)->telephone,((telephonehash->elem)+i)->address);  //��ʾ���ҽ�� 
		    pnow = (namehash->elem)+i;
		    printf("\n");
			printf("�Ƿ��޸���ϵ����Ϣ���밴��ʵ�ֹ��ܣ�\n");   //�޸���ϵ����Ϣ��������ɾ�����������µ���Ϣ���ٴ��� 
            printf("��1:��\n");
            printf("��2:��\n");
            printf("\n");
            scanf("%d",&i);
            switch(i)
            {
            	case 1:
            	{
	            	DeleteContact(pnow, namehash, telephonehash);   //����ʵ��pnow��main�����еı��� 
	            	GetInfo(name, telephone, address);  //������ʵ�ζ���main�����еı��� 
	            	CreateContact(telephonehash, namehash, name, telephone, address);//��������main�����еı���
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
	int j = Hashfunction(Trans(inputname));  //�����������ֵĹ�ϣֵ
	if( ((namehash->elem)+j)->flag != 1)        //���޴���
	{
		printf("δ�ҵ�����ϵ�ˣ�\n");     //��һ���Ƿ񴴽�����ϵ�� 
		return;
	} 
	if( ((namehash->elem)+j)->flag == 1)   //�����λ������ 
	{
		if((strcmp(inputname, ((namehash->elem)+j)->name)) == 0)//������������
		{
			((namehash->elem)+j)->flag = 0;
			namehash->nn--;
		}
		else 
		{
			while((strcmp(inputname, ((namehash->elem)+j)->name)) != 0)  //���������� ѭ���ó�ͻ������i ֱ���ҵ������ 
			{
				j = Conflict(j);
			}
			((namehash->elem)+j)->flag = 0;
			namehash->nn--;
		}
	}
	
	char *inputtelephone = ((namehash->elem)+j)->telephone;
	j = Hashfunction(Trans(inputtelephone));  //�����������ֵĹ�ϣֵ
	if( ((telephonehash->elem)+j)->flag != 1)        //���޴���
	{
		printf("δ�ҵ�����ϵ�ˣ�\n");     //��һ���Ƿ񴴽�����ϵ�� 
		return;
	} 
	if( ((telephonehash->elem)+j)->flag == 1)   //�����λ������ 
	{
		if((strcmp(inputtelephone, ((telephonehash->elem)+j)->telephone)) == 0)//������������
		{
			((telephonehash->elem)+j)->flag = 0;
			telephonehash->nn--;
			printf("\n");
			printf("ɾ���ɹ���\n");
			printf("\n");
		}
		else 
		{
			while((strcmp(inputtelephone, ((telephonehash->elem)+j)->telephone)) != 0)  //���������� ѭ���ó�ͻ������i ֱ���ҵ������ 
			{
				j = Conflict(j);
			}
			((namehash->elem)+j)->flag = 0;
			namehash->nn--;
			printf("\n");
			printf("ɾ���ɹ���\n");
			printf("\n");
		}
	}
	return;   
}

