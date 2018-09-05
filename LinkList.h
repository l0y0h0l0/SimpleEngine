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
	void _ExpandCapacity();                 //扩充表的容量，扩充为原来的两倍

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

template<typename T>
CLinkList<T>::CLinkList(CLinkList& that)
{
	m_Head = new _NODE;
	m_Back = new _NODE;

	m_Head->_next = m_Head;
	m_Head->_pre = m_Head;

	m_Back->_next = m_Back;
	m_Back->_pre = m_Back;

	m_Len = that.m_len;

	m_Size = that.m_Size;

	_NODE* p = m_Head;

	for (int i = 0; i < m_Len; ++i)
	{
		_NODE* n = new _NODE;

		n->_data = *(that.GetData(i));

		n->_next = m_Head;
		n->_pre = p;
		p->_next = n;
		m_Head->_pre = n;

		p = n;

	}

	p = m_Back;
	for (int i = 0; i < m_Size - m_Len; ++i)
	{
		_NODE* n = new _NODE;
		n->_pre = p;
		n->_next = m_Back;
		p->_next = n;
		m_Back->_pre = n;

		p = n;
	}
}

template<typename T>
CLinkList<T>& CLinkList<T>:: operator=(CLinkList& that)
{
	Clear();
	m_Len = that.m_Len;

	for (int i = 0; i < m_Len; ++i)
	{
		PushBack(*(that.GetData(i)));
	}
	return *this;
}

template<typename T>
CLinkList<T>::~CLinkList()
{
	Clear();

	_NODE* p = m_Back->_next;

	for (int i = 0; i < m_Size; ++i)
	{
		_NODE* n = p->_next;
		delete p;
		p = n;
	}
	delete m_Head;
	delete m_Back;
}

template<typename T>
void CLinkList<T>::Insert(T data, int pos)
{
	if (pos ＞ m_Len)
		pos = m_Len;
	else if (pos < 0)
		pos = 0;

	_NODE* p = _GetIndex(pos);
	_NODE* q = p->_pre;

	_ExpandCapacity();

	_NODE* n = m_Back->_next;
	m_Back->_next = n->_next;
	n ->_next->_pre = m_Back;

	n->_data = data;

	n->_next = p;
	n->_pre = q;
	p->_pre = n;
	q->_next = n;

	++m_Len;
}

template<typename T>
void CLinkList<T>::PushBack(T data)
{
	_ExpandCapacity();

	_NODE* n = m_Back->_next;

	m_Back->_next = n->_next;
	n->_next->_pre = m_Back;

	n->_data = data;

	_NODE* p = m_Head->_pre;
	p->_next = n;
	n->_pre = p;
	n->_next = m_Head;
	m_Head->_pre = n;

	++m_Len;
}

template<typename T>
bool CLinkList<T>::Erase(int pos)
{
	_NODE* n = _GetIndex(pos);

	if (!n)
		return false;

	n->_pre->_next = n->_next;
	n->_next->_pre = n->_pre;

	m_Back->_next->_pre = n;
	n->_next = m_Back->_next;
	m_Back->_next = n;
	n->_pre = n;

	--m_Len;
	return true;
}

template<typename T>
void CLinkList<T>::Clear(){
	if (m_Len != 0)
	{
		_NODE* p = m_Head->_next;
		_NODE* q = m_Head->_pre;

		m_Head->_next = m_Head->_pre = m_Head;

		m_Back->_pre->_next = p;
		p->_pre = m_Back->_pre;
		q->_next = m_Back;
		m_Back->_pre = q;

		m_Len = 0;
	}
}

template<typename T>
T* CLinkList<T>::GetData(int pos)
{
	if (pos < 0 || pos >= m_Len)
		return 0;
	return &(_GetIndex(pos)->_data);
}

template<typename T>
typename CLinkList<T>::_NODE* CLinkList<T>::_GetIndex(int pos)
{
	if (pos < 0 || pos > m_Len)
		return 0;

	_NODE* p = m_Head;

	if (pos < m_Len / 2)
	{
		for (int i = 0; i <= pos; ++i)
		{
			p = p->_next;
		}
	}
	else
	{
		pos = m_Len - pos;
		for (int i = 0; i < pos; ++i)
		{
			p = p->_pre;
		}
	}
	return p;
}

template<typename T>
void CLinkList<T>::_ExpandCapacity()
{
	if (m_Len >= m_Size)
	{
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
		m_Size *= 2;
	}
}

template <typename T>
typename int CLinkList<T>::GetLength()
{
	return m_Len;
}
#endif