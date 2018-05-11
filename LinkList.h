#ifndef _LINK_LIST_H
#define _LINK_LIST_H

template <typename T>
class CLinkList
{
private:
	struct _NODE
	{
		T _data;                           //数据
		_NODE* _pre;                       //前驱指针
		_NODE* _next;                      //后续指针
	};

	_NODE* m_Head;                         //头指针
	_NODE* m_Back;                         //缓冲头指针
	int m_Len;                             //数据数量
	int m_Size;                            //表容量

	_NODE* _GetIndex(int pos);             //得到指定位置的节点指针
	void ExpandCapacity();                 //扩充表的容量，扩充为原来的两倍

public:
	CLinkList();
	CLinkList(int size);
	CLinkList(CLinkList& that);
	CLinkList& operator =(CLinkList& that);
	~CLinkList();

	void Insert(T data, int pos);           //插入数据
	void PushBack(T data);                  //推入数据
	bool Erase(int pos);                    //删除数据
	void Clear();                           //清空表
	T* GetData(int pos);                    //获取数据
	int GetLength();                        //获取表中数据数量
};

//构造
template <typename T>
CLinkList<T>::CLinkList() {
	m_Head = new _NODE;
	m_Back = new _NODE;

	m_Head->_next = m_Head;
	m_Head->_pre = m_Head;

	m_Back->_next = m_Back;
	m_Back->_pre = m_Back;

	//缓冲链表的容量
	m_Size = 32;

	_NODE* p = m_Back;
	for (int i = 0; i < m_Size; ++i)
	{
		_NODE* n = new _NODE;
		p->_next = n;
		n->_pre = p;
		n->_next = m_Back;
		m_Back->_pre = n;
		p = p->_next;
	}

	m_Len = 0;
}

template<typename T>
CLinkList<T>::CLinkList(int size)
{
	m_Head = new _NODE;
	m_Back = new _NODE;

	m_Head->_next = m_Head;
	m_Head->_pre = m_Head;

	m_Back->_next = m_Back;
	m_Back->_pre = m_Back;

	//缓冲链表的容量
	if (size < 1) {
		size = 10;
	}
	m_Size = size;

	_NODE* p = m_Back;
	for (int i = 0; i < m_Size; ++i)
	{
		_NODE* n = new _NODE;
		p->_next = n;
		n->_pre = p;
		n->_next = m_Back;
		m_Back->_pre = n;
		p = p->_next;
	}

	m_Len = 0;
}
#endif