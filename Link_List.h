#ifndef LINK_LIST_H
#define LINK_LIST_H

typedef int Element;
/* ֻҪ����ʽ�洢�����ľ��Ƕ���ڵ㣬ֻ��ͨ���ڵ�����ҵ�������
 * */
// �ڵ�����
typedef struct _link_node
{
	Element data;
	struct _link_node* next;
}link_node;

/* ��ͷ�ڵ�ı�ͷ�ṹ */
typedef struct
{
	link_node header;
	int num;
}LinkHeader;

//��ͷ��ʼ�����ͷ�
LinkHeader* createLinker();
void releaseLinker(LinkHeader* link);

// ���������ͷ�巨������λ�÷���β�巨����ǰ�ýڵ�
int header_insert01(LinkHeader* header, Element val);
int header_insertPos(LinkHeader* header, int pos, Element val);

// �鿴����Ԫ��
void show_headerLinker(LinkHeader* linkHeader);

// ɾ��ĳ��Ԫ��
int header_delete(LinkHeader* header, Element val);

#endif
