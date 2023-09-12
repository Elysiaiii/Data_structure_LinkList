#ifndef LINK_LIST_H
#define LINK_LIST_H

typedef int Element;
/* 只要是链式存储，核心就是定义节点，只有通过节点才能找到其他人
 * */
// 节点类型
typedef struct _link_node
{
	Element data;
	struct _link_node* next;
}link_node;

/* 带头节点的表头结构 */
typedef struct
{
	link_node header;
	int num;
}LinkHeader;

//表头初始化和释放
LinkHeader* createLinker();
void releaseLinker(LinkHeader* link);

// 插入操作（头插法、任意位置法、尾插法）找前置节点
int header_insert01(LinkHeader* header, Element val);
int header_insertPos(LinkHeader* header, int pos, Element val);

// 查看链表元素
void show_headerLinker(LinkHeader* linkHeader);

// 删除某个元素
int header_delete(LinkHeader* header, Element val);

#endif
