#include <stdio.h>
#include <stdlib.h>
#include "Link_List.h"

// 表头初始化和释放
LinkHeader* createLinker()
{
	LinkHeader* res;
	// 申请表头
	res = (LinkHeader*)malloc(sizeof(LinkHeader));
	if (res == NULL)	//-----------注意判断表头是否创造成功------------//
	{
		printf("linker malloc failed!\n");
		return NULL;
	}
	// 初始化表头
	res->num = 0;
	res->header.data = 0;		// 根据表的物理属性来决定
	res->header.next = NULL;	// 一定要初始化为NULL，否则导致死循环
	return res;
}

void releaseLinker01(LinkHeader* link)
{	// 先释放所有链表里的结点，最后再释放表头
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

// 插入操作（头插法、任意位置法、尾插法）找前置节点
int header_insert01(LinkHeader* linkHeader, Element val)
{
	link_node* p = &linkHeader->header;		//------注意插入的关键是找前置结点------//
	// 申请新结点，初始化结点
	link_node* new_node = (link_node*)malloc(sizeof(link_node));
	if (new_node == NULL)
	{
		printf("insert malloc failed!\n");
		return NULL;
	}
	new_node->data = val;

	// 处理新老结点
	new_node->next = p->next;
	p->next = new_node;
	linkHeader->num++;
	return 0;
}

/* pos取值最小值范围： [1....]  [0....]
 * pos取值最大范围：不能大于元素个数
 * */
int header_insertPos(LinkHeader* linkHeader, int pos, Element val)
{
	// pos的合法性
	if (pos<0 || pos>linkHeader->num)
	{
		printf("insert pos invalid!\n");
		return -1;
	}
	// 找前置结点
	link_node* p = &linkHeader->header;
	int index = -1;
	while (p && index < pos - 1)	//------不是p->next是因为可能在链表尾插入，此时p->next为NULL-----//
	{
		p = p->next;
		index++;	//-----注意index++....----//
	}
	if (p)
	{
		// 申请新结点，初始化结点
		link_node* new_node = (link_node*)malloc(sizeof(link_node));
		if (new_node == NULL)	//------每次malloc之后记得判断是否成功-----//
		{
			printf("insert malloc failed!\n");
			return -1;
		}
		new_node->data = val;

		// 处理新老结点
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

// 查看链表元素
void show_headerLinker(LinkHeader* linkHeader)
{
	// 引入辅助指针，指向第一个元素，遍历
	link_node* p = linkHeader->header.next;		// 带头结点的遍历初始化

	// 链式遍历模板
	while (p)
	{
		// 处理当前辅助指针所在结点
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

// 删除某个元素
int header_delete(LinkHeader* linkHeader, Element val)
{
	// 辅助指针，指向待删除节点的前置节点
	// link_node *p = linkHeader->header.next;		  错误，第一个元素没有办法找前置节点了
	link_node* p = &linkHeader->header;

	// 链式查找符合条件的模板，站在p点往后看，后面的元素满足条件，就退出，如果不满足，调到下一个继续看后面
	/*
	while (p->next) {
		if (p->next->data == val) {
			break;
		}
		p = p->next;
	}
	*/
	// 1. 查找
	while (p->next && (p->next->data != val))
	{
		p = p->next;
	}
	
	// 2. 删除（是否找到）
	if (p->next)
	{
		// 找到
		// 2.1 待删除结点的备份
		link_node* tmp = p->next;
		p->next = tmp->next;
		free(tmp);
		linkHeader->num--;
	}
	else
	{
		// 没有找到这个元素
		printf("NO %d element!\n", val);
		return -1;
	}
	return 0;
}