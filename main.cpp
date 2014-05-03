#include<iostream>
using namespace std;

#define MinTableSize 10

typedef int ElemType;
typedef unsigned int Index;

typedef struct ListNode
{
	ElemType element;
	struct ListNode *next;
} *List, *Position;

typedef struct HashTbl
{
	int TableSize;
	List*TheLists;
} Table;


class HashTable{
private:
	struct HashTbl *table;
	struct ListNode position;
	struct ListNode *list;
	

public:
	HashTable();
	HashTable(int TableSize);
	~HashTable();

	Index Hash(ElemType Key);
	
	Position Find(ElemType Key);
	void Insert(ElemType Key);
	void PrintHashTable();
};

HashTable::HashTable()
{
}

HashTable::HashTable(int TableSize)
{
	if(TableSize<MinTableSize)
	{
		printf("Table size too small!\n");
		return;
	}

	/*Allocate table*/
	table = new Table;
	if(NULL == table)
	{
		cout <<"Out of space!!\n"<<endl;
		return;
	}

	table->TableSize = TableSize;
	
	/*Allocate array of lists*/
	table->TheLists = new List[table->TableSize];
	if(NULL == table->TheLists)
	{
		cout <<"Out of space !!!\n" << endl;
		delete table;
		return;
	}

	for(int i = 0; i < table->TableSize; ++i)
	{
		table->TheLists[i] = NULL;
	}
}

HashTable::~HashTable()
{
	for(int i = 0; i < table->TableSize; i++)
	{
		Position p=table->TheLists[i];
		Position temp;

		while(p != NULL)
		{
			temp = p->next;
			delete p;
			p = temp;
		}
	}
	delete []table->TheLists;
	delete table;
}

Index HashTable::Hash(ElemType Key)
{
	return Key%table->TableSize;
}

Position HashTable::Find(ElemType Key)
{
	Position p;
	List L;

	L=table->TheLists[Hash(Key)];
	p=L;
	while(p!=NULL&&p->element!=Key)
		p=p->next;

	return p;
}

void HashTable::Insert(ElemType Key)
{
	Position pos,newCell;
	List L;

	pos=Find(Key);
	if(NULL==pos)/*Key is not found*/
	{
		newCell=new ListNode;
		
		if(NULL==newCell)
		{
		  printf("Out of space!!!");
		  return;
		}
		
		else
		{
			newCell->element=Key;
			newCell->next = NULL;
			int index = Hash(Key);
			if(table->TheLists[index] == NULL)
			{
				table->TheLists[index] = newCell;
			}
			else
			{
				L = table->TheLists[index];
				while(L->next)
				{
					L = L->next;
				}
				L->next = newCell;
			}
		}
	}
}

void HashTable::PrintHashTable()
{
	for(int i = 0; i < table->TableSize; ++i)
	{
		Position p=table->TheLists[i];
		while(p)
		{
			printf("address=%d value=%d\n",i,p->element);
			p=p->next;
		}	
	}
}

//test 

int main()
{
	int array[]={19,14,23,01,68,20,84,27,55,11,10,79};
	int len=sizeof(array)/sizeof(array[0]);
	
	HashTable hashtable(len);

	for(int i = 0; i < len; ++i)
	{
		hashtable.Insert(array[i]);
	}

	hashtable.PrintHashTable();
	cout << endl;

	int value;
	Position p= NULL;
	cout << "Please input the the value which need find:" << endl;
	cin>> value;
	p = hashtable.Find(value);
	if(p)
	{
		cout << p->element;
	}
	else
		cout <<"cannot find the value" << endl;

	return 0;
}
