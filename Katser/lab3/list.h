//----------------------------------------------------------------------------
#ifndef ListH
#define ListH
#include <iostream>
//----------------------------------------------------------------------------
/*
������ ������: ������� ������ �� ��������� ���� T.
*/
template <class T>
class List {

  private:

  // �������� ����������� ��������� "���� ������".
  // ���� ������.
  struct Node 
  {
	T Data;					// ������ (�������� ��-�� ������)
    Node *Prev, *Next;  // ��������� �� ���������� � ��������� ����

    // �������� ���������� ����.
    Node(const T& data) // ����������� ��� ��������
      : Data(data),		// �������� ������;
        Prev(NULL),	   // ����������� �
        Next(NULL)		// ������������ ����� ���
    {
    }

  };

  Node *Head,	// ������ ���� ������
       *Tail;    // ��������� ����

  // ������ ����������� ����������� � �������� ������������ ���������.
  List(const List&) { }
  void operator=(const List&) { }

  public:

  // �������� ����������� ������ "�������� ������".
  // �������� ������.
  class Iterator {
    // ����� ������ ����������� ������������� ��� ������� � ��������� �� ����.
    friend List<T>;

    Node* P;	// ��-�� �� ���� ������, ���������� �������� ��-��, �� ���-� ��������� ��������

    public:
    // ������� ��������, ����������� �� ��-� ������, ���������� � ���� �� ������ p.
    // �� ��������� �� �� ��� �� ���������. �. �. Node - �������� ��� ������ List,
    // �� �������� �� ��-� ����� ���� ������ ������ ���������-���������� List.
    Iterator(Node* p = NULL)
      : P(p)
    {
    }

    // �������� ��������������� ��� ������������ ���������.
    // ���������� ���������� ������ �� �������� ��-��.
    const T& operator *() const
    {
    	return P->Data;
    }
    

    // �������� ��������������� ��� �� ������������ ���������.
    // ���������� �� ������������ ������ �� �������� ��-��, �� �������
    // ��� ����� ���� ��������.
    T& operator *()
    {
    	return P->Data;
    }

    // ���������� �������� ����������. ���������� �������� � ���������� ��-�� ������.
    Iterator operator ++()
    {
    	P = P->Next;		// ��������� � ���������� ��-��
   		return *this;		// ���������� "�����������" ��������
    }

    // ����������� �������� ����������. ���������� �������� � ���������� ��-�� ������.
    // �������� ���� int ��������� �����������, ��� ������ �������-�������� operator ++
    // �������� �����������.
    Iterator operator ++(int)
    {
    	Iterator t(*this);	// ��������� "�� �����������" �������� ���������
    	P = P->Next;			// ��������� � ���������� ��-��
    	return t;				// ���������� "�� �����������" �������� ���������
    }

    // ���������� �������� ����������. ���������� �������� � ����������� ��-�� ������.
    Iterator operator --()
    {
    	P = P->Prev;     // ��������� � ����������� ��-��
    	return *this;		// ���������� "�����������" ��������
    }

    // ����������� �������� ����������. ���������� �������� � ����������� ��-�� ������.
    // �������� ���� int ��������� �����������, ��� ������ �������-�������� operator --
    // �������� �����������.
    Iterator operator --(int)
    {
    	Iterator t(*this);	// ��������� "�� �����������" �������� ���������
    	P = P->Prev;        // ��������� � ����������� ��-��
    	return t;				// ���������� "�� �����������" �������� ���������
    }

    // �������� ���������.
    friend bool operator ==(const Iterator& x,const Iterator& y)
    {
    	return y.P == x.P;
    }

    // �������� �����������.
    friend bool operator !=(const Iterator& x,const Iterator& y)
    {
    	return y.P != x.P;
    }
		
	};

  // ����������� ������� ������
  List()
    : Head(NULL), Tail(NULL)
  {
  }

  // ���������� (����������� ������).
  ~List()
  {
  Clear();
  }

  // ���������� ����������� �������� �� ������ ������� (��� ������������ ������).
  const Iterator Begin() const
  {
  		return Iterator(Head);
  }

  // ���������� �������� �� ������ ������� (��� �� ������������ ������).
  Iterator Begin()
  {
  		return Iterator(Head);
  }

  // ���������� ����������� �������� �� ��������� ������� (��� ������������ ������).
  const Iterator Last() const
  {
  		return Iterator(Tail);
  }

  // ���������� �������� �� ��������� ������� (��� �� ������������ ������).
  Iterator Last()
  {
  		return Iterator(Tail);
  }

  // ���������� ����������� �������� �� "�����" (��� ������������ ������).
  const Iterator End() const
  {
  		return Iterator(NULL);
  }

  // ���������� �������� �� "�����" (��� �� ������������ ������).
  Iterator End()
  {
  		return Iterator(NULL);
  }

  // �������� ������� ������.
  bool Empty() const
  {
  		return !Head;
  }

  // ��������� ������� � ������ ����� ���������, �� ������� ��������� �����.
  // ���� ������ ������, �� ��-� ����������� � ����� ������.
  void Insert(const int nomer, const T& data);

  // ������� ��-�, �� ������� ��������� �������� �����.
  // ���� ���� ������ ������, �� ��-� ��������� � ����� ������.
  void Delete(const int nomer);
  
  // ������� ��-�, �� ������� ��������� �������� iter.
  void Delete(const Iterator& iter);

  // ������� ��� ��-�� �� ������.
  void Clear();

  // ���������� ��-�� � ������ ������.
  void AddBegin(const T& data) ;

  // ���������� ��-�� � ����� ������.
  void AddEnd(const T& data) ;

  // �������� ������� ��-��.
  void DeleteFirst();

  // �������� ���������� ��-��.
  void DeleteLast();
  
  // �������� ������ ������ 
  show()
  {
	Iterator i;
	std::cout << '[';
	// ������� ��� �������� ����� ����������, �������� �� �������.
	for (i = Begin(); i != Last(); i++)
  		std::cout << *i << ", ";
	// ������� ��������� ������� (���� ������ �� ����).
	if (i != End()) std::cout << *i;
	std::cout << "]\n";
  }
  
};
//---------------------------------------------------------------------------
// ����������� �� ������������ �������-���������
//---------------------------------------------------------------------------
template <class T>
void List<T>::Insert(const int nomer, const T& data)
{
	// ���� ������ �� ����, ��
	if ((Head) && (nomer!=0))
	{
		int m;
		Iterator i;
		m=0;	
		i=Begin();
		// ���� ���� X, ����� ������� ����� ��������.
		while( (m<nomer) && (i!= End()) )
		{
			m++;
			i++;
		}
		// ���� iter ��������� �� "�����", �� ��������� ��-� � ����� ������.
		if (i==End())
		{
			AddEnd(data);
		}
		// ����� ��������� ��-� � "��������" ������.
		else
		{
			Node *t,
			 *n = new Node(data);		// ������� ��������� ����
			t = i.P->Prev;		// � t ������� �������������� X
    		t->Next = n;        // ��������� �������������� X � �����
    		n->Prev = t;		   // ��������� ����� � �������������� X
    		n->Next = i.P;	   // ��������� ����� � X
    		i.P->Prev = n;      // ��������� X � �����
		}
	}
	// ����� ��������� ��-� � ������
	else
	{
		AddBegin(data);
	}
}
//---------------------------------------------------------------------------
template <class T>
void List<T>::Delete(const int nomer)
{
// ���� ������ �� ����, ��
	if (Head)
	{
		int m=0;
		Iterator i;
		i=Begin();
		// ���� ���� X, ������� ����� �������.
		while( (m<nomer) && (i!= End()) )
		{
			m++;
			i++;
		}
		// ���� X ������.
		if (i == Begin())
		{
			DeleteFirst();
		}
		// �����, ���� X ���������.
		else if ((i==Last()) || (i==End()))
		{
			void DeleteLast();
		}
		// ����� X �������.
		else
		{
			Node *t, *pred, *sled;
			t=i.P;                     //��������� �������
			pred=t->Prev;			//����������
			sled=t->Next;			//��������
			pred->Next = t->Next;	// ��������� ���������� X �� ��������� �� X,
    		sled->Prev = t->Prev;  // ������� X �� ������
			delete t;				// �������  (���������� � ����������� ������).
		}
	}
}
//---------------------------------------------------------------------------
template <class T>
void List<T>::Delete(const Iterator& iter)
{
Node *t;
Iterator i;
// ���� ���� X, ���������� ��������� ��-�.
for (i = Begin(); i != End(); i++)
  if (i == iter) break;
// ���� �� ������, �� iter �� ���������: ������.
//assert(i != End());
t = i.P;
// ���� X ������.
if (i == Begin()) {
  // ������� ������ ���� �� ��������� �� ���.
  Head = t->Next;
  // ���� �� ����������, �� ������ ������� �� ������ ��-�� �
  // ����� �������� ��������� �� ���������.
  if (!Head) Tail = NULL;
  }
else
  // �����, ���� X ���������.
  if (i == Last()) {
    // ������� ��������� ���� �� ��� ��������������.
    Tail = t->Prev;
    // ���� �� ����������, �� ������ ������� �� ������ ��-�� �
    // ����� �������� ��������� �� ������.
    if (!Tail) Head = NULL;
    }
  else {
    // ����� X �������.
    t->Prev->Next = t->Next;	// ��������� ���������� X �� ��������� �� X,
    t->Next->Prev = t->Prev;  // ������� X �� ������
    }
// ������� X (���������� � ����������� ������).
delete t;
}



//---------------------------------------------------------------------------
template <class T>
void List<T>::Clear()
{
// ���� ������ �� ����.
if (!Empty()) {
  Node *n;
  Iterator i;
  // ������� ��� ����.
  for (i = Begin(); i != End(); ) {
    n = i.P;	// ��������� ����� ����
    i++;			// ��������� � ����������
    delete n;	// � ������� �������
    }
  // ���������� ��������� �� ������ � ���������.
  Head = Tail = NULL;
  }
}
//---------------------------------------------------------------------------
//���������� ��-�� � ������ ������.
template <class T>
void List<T>::AddBegin(const T& data)
{
	Node *n=new Node(data);		// ������� ��������� ����
	// ���� ������ �� ����, ��
    if (Head)
      // ��������� ������ ���� � �����;
      Head->Prev = n;
    else
      // ����� ����� ������ ���� �������� � ���������.
      Tail = n;
    // ��������� ����� ���� � ������,
    n->Next = Head;
    // � ������ ��� ������.
    Head = n;
}
//---------------------------------------------------------------------------
//���������� ��-�� � ����� ������.
template <class T>
void List<T>::AddEnd(const T& data)
{
	Node *n=new Node(data);		// ������� ��������� ����
	// ���� ������ �� ����, ��
  if (Head)
    // ��������� ��������� ���� � �����;
    Tail->Next = n;
  else
    // ����� ����� ��������� ���� �������� � ������.
    Head = n;
  // ��������� ����� ���� � ���������,
  n->Prev = Tail;
  // � ������ ����� ���������.
  Tail = n;
}
//---------------------------------------------------------------------------
// �������� ������� ��-��.
template <class T>
void List<T>::DeleteFirst()
{
	Node *t=Head;
	// ������� ������ ���� �� ��������� �� ���.
	Head = t->Next;
	// ���� �� ����������, �� ������ ������� �� ������ ��-�� �
	// ����� �������� ��������� �� ���������.
	if (!Head) Tail = NULL;
	// �������  (���������� � ����������� ������).
	delete t;
}
//---------------------------------------------------------------------------
// �������� ���������� ��-��.
template <class T>
void List<T>::DeleteLast()
{
	Node *t=Tail;
	// ������� ��������� ���� �� ��� ��������������.
    Tail = t->Prev;
    // ���� �� ����������, �� ������ ������� �� ������ ��-�� �
    // ����� �������� ��������� �� ������.
    if (!Tail) Head = NULL;
    // �������  (���������� � ����������� ������).
	delete t;
}
//---------------------------------------------------------------------------
#endif
