#include <stdio.h>
#include <stdlib.h>
#include "Link_List.h"

// ��ͷ��ʼ�����ͷ�
LinkHeader* createLinker()
{
	LinkHeader* res;
	// �����ͷ
	res = (LinkHeader*)malloc(sizeof(LinkHeader));
	if (res == NULL)	//-----------ע���жϱ�ͷ�Ƿ���ɹ�------------//
	{
		printf("linker malloc failed!\n");
		return NULL;
	}
	// ��ʼ����ͷ
	res->num = 0;
	res->header.data = 0;		// ���ݱ����������������
	res->header.next = NULL;	// һ��Ҫ��ʼ��ΪNULL����������ѭ��
	return res;
}

void releaseLinker01(LinkHeader* link)
{	// ���ͷ�����������Ľ�㣬������ͷű�ͷ
	if (link)
	{
		link_node* p = &link->header;
		if (link->header.next)
		{
			while (p->next)
			{
				link_node* tmp = p->next;
				p->next = tmp->next;
				free(tmp);
				link->num--;
			}
			printf("link have %d node!\n", link->num);
		}
		free(link);
	}
}

void releaseLinker(LinkHeader* link)
{
	if (link)
	{
		if (link->header.next)
		{
			link_node* p = link->header.next;
			while (p)
			{
				link_node* tmp = p;
				p = p->next;
				free(tmp);
				link->num--;
			}
			printf("link have %d node!\n", link->num);
		}
		free(link);
	}
}

// ���������ͷ�巨������λ�÷���β�巨����ǰ�ýڵ�
int header_insert01(LinkHeader* linkHeader, Element val)
{
	link_node* p = &linkHeader->header;		//------ע�����Ĺؼ�����ǰ�ý��------//
	// �����½�㣬��ʼ�����
	link_node* new_node = (link_node*)malloc(sizeof(link_node));
	if (new_node == NULL)
	{
		printf("insert malloc failed!\n");
		return NULL;
	}
	new_node->data = val;

	// �������Ͻ��
	new_node->next = p->next;
	p->next = new_node;
	linkHeader->num++;
	return 0;
}

/* posȡֵ��Сֵ��Χ�� [1....]  [0....]
 * posȡֵ���Χ�����ܴ���Ԫ�ظ���
 * */
int header_insertPos(LinkHeader* linkHeader, int pos, Element val)
{
	// pos�ĺϷ���
	if (pos<0 || pos>linkHeader->num)
	{
		printf("insert pos invalid!\n");
		return -1;
	}
	// ��ǰ�ý��
	link_node* p = &linkHeader->header;
	int index = -1;
	while (p && index < pos - 1)	//------����p->next����Ϊ����������β���룬��ʱp->nextΪNULL-----//
	{
		p = p->next;
		index++;	//-----ע��index++....----//
	}
	if (p)
	{
		// �����½�㣬��ʼ�����
		link_node* new_node = (link_node*)malloc(sizeof(link_node));
		if (new_node == NULL)	//------ÿ��malloc֮��ǵ��ж��Ƿ�ɹ�-----//
		{
			printf("insert malloc failed!\n");
			return -1;
		}
		new_node->data = val;

		// �������Ͻ��
		new_node->next = p->next;
		p->next = new_node;
		linkHeader->num++;
	}
	else
	{
		printf("linker number invalid!\n");
		return -1;
	}
	return 0;
}

// �鿴����Ԫ��
void show_headerLinker(LinkHeader* linkHeader)
{
	// ���븨��ָ�룬ָ���һ��Ԫ�أ�����
	link_node* p = linkHeader->header.next;		// ��ͷ���ı�����ʼ��

	// ��ʽ����ģ��
	while (p)
	{
		// ����ǰ����ָ�����ڽ��
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

// ɾ��ĳ��Ԫ��
int header_delete(LinkHeader* linkHeader, Element val)
{
	// ����ָ�룬ָ���ɾ���ڵ��ǰ�ýڵ�
	// link_node *p = linkHeader->header.next;		  ���󣬵�һ��Ԫ��û�а취��ǰ�ýڵ���
	link_node* p = &linkHeader->header;

	// ��ʽ���ҷ���������ģ�壬վ��p�����󿴣������Ԫ���������������˳�����������㣬������һ������������
	/*
	while (p->next) {
		if (p->next->data == val) {
			break;
		}
		p = p->next;
	}
	*/
	// 1. ����
	while (p->next && (p->next->data != val))
	{
		p = p->next;
	}
	
	// 2. ɾ�����Ƿ��ҵ���
	if (p->next)
	{
		// �ҵ�
		// 2.1 ��ɾ�����ı���
		link_node* tmp = p->next;
		p->next = tmp->next;
		free(tmp);
		linkHeader->num--;
	}
	else
	{
		// û���ҵ����Ԫ��
		printf("NO %d element!\n", val);
		return -1;
	}
	return 0;
}