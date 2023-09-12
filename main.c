#include <stdio.h>
#include "link_list.h"

/* 1. 为什么要有链式存储
 * 		顺序存储，要求内存是必须是连续的，如果用户需要存储大量的数据，但内存确没有连续的这么大的空间
 * 		就会导致无法操作。	malloc底层就是分配连续的空间，有可能malloc返回失败
 * 		内存连续，有时候是很苛刻的
 * 	为了能够在不连续的内存上，尽可能的来利用内存存储数据，发明了链式存储
 * 		数据当做一个个节点，每个节点里面包含下一个节点的信息
 * 		地下党接头  A --- B --- C ---- D
 * * 内存 ： 物理内存（嵌入式）   虚拟内存（OS）
 * 2. 单向链式存储的基本操作
 * 2.1 插入操作
 * 		单向链表的一个重要特性：开弓没有回头箭，一旦走到了A节点，就再也找不到原来的节点了
 * 		插入操作：在5号位置上插入，实际上应该让指针找到4号位置，才能在5号位置上插入
 * 2.2 删除操作
 *
 * 2.3 查找操作
 *
 * 2.4 更新操作
 *
 * 3. 链式存储的实现
 * 3.1 带头节点的链式表
 *
 * 3.2 带头指针的链式表
 *
 * */

int main(int argc, char* argv[]) {
	LinkHeader* linker = createLinker();
	if (linker == NULL) {
		return -1;
	}

	for (int i = 0; i < 5; ++i) {
		// 头插法就是逆序
		header_insert01(linker, i + 100);
	}
	printf("Table have %d node!\n", linker->num);
	// 显示链表结果
	show_headerLinker(linker);

	header_insertPos(linker, 6, 300);
	show_headerLinker(linker);

	header_delete(linker, 103);
	show_headerLinker(linker);

	releaseLinker(linker);
	return 0;
}

/* 1. 206 思考题，已经有一个带头节点的链表，我现在倒序他，如何编写
 * 2. 牛客 思考题，已经有一个带头指针的链表，我现在倒序他，如何编写
 * 提示：创建dummy节点 临时节点，充当头节点
 * 3. 21 思考题，链表归并排序，有两个带头指针的链表，这2个链表独立有序，完成2个链表的合并，实现一个有序链表
 * */