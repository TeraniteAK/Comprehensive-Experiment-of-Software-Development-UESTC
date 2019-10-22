#include <stdio.h>
#include "Contact.h"

int main()
{
	int a;   //ָ�����
	Sqlist telephonehash, namehash;   //����������ϣ�� 
	Sqlist * pt = &telephonehash;
	Sqlist * pn = &namehash;  //����������ϣ��ָ�벢�ֱ�ָ���ϣ���׵�ַ�����ں������� 
	int size = 200; //����绰������ 
	Contact * pnow;   //Contactָ����� ָ��ǰ��ϵ�� �涨��1.��������ϵ�˺�����ָ������������ϵ�� 
	int telnum;    //�洢��ǰ��ϵ����telephonehash�е��±� 
	int namenum;   //�洢��ǰ��ϵ����namehash�е��±� 
	char name[20], telephone[15], address[20];  //��¼���������name��telephone��address��Ϣ�������������½����ǲ��ң�
	
	InitialContact(size, pt, pn); //��ʼ������ 
	
	for(;;)
	{
		printf("��ӭʹ�õ绰���뱾,��ѡ���ܣ�\n");
        printf("��1:��������ϵ��\n");
        printf("��2:������������ϵ��\n");
        printf("��3:���绰���������ϵ��\n");
        printf("��4:�鿴��ǰ�绰���뱾״̬\n");
        printf("��5:ɾ����ϵ��\n");
        printf("��0:�˳�����\n");
        printf("\n");
        scanf("%d",&a);
	switch(a)
    {
    	case 0:
    	{
    		printf("��л����ʹ�ã�\0");
    		free(telephonehash.elem);
    		telephonehash.elem = NULL;
    		free(namehash.elem);
    		namehash.elem = NULL;
   	    	return 0;
	    }
	    case 1:
    	{
    		GetInfo(name, telephone, address);  //�Ȼ����Ϣ 
    		CreateContact(pt, pn, name, telephone, address);  //�ٴ��� 
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
    		printf("�Ƿ����\n");
    		printf("\n");
    		break;
    	}
    }
	}
}

/*����˵����
1.�����������������ڵ绰��������ֲ��Ҹ���ֻ���������һ����
2.��������ͬ�绰��������ڵ绰��������ֲ��Ҹ���ֻ���������һ����
3.����ʱ��������ȫ����ȫ�绰�������������
4.Ŀǰʱ�临�ӶȻ��������⣬��Ҫ���������ʱ��Ƚϳ������˾�����trans������ʱ��̫���ˣ���ʵ��hash�㷨û�й�ϵ��hash�㷨��û������ģ� 
*/
