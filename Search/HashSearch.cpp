#include "stdio.h"

#define SIZE 10

template <class T>
struct HashTable
{
	T key;        //关键字 
	int used;       //占用(冲突)标志，0表示没被占用，1表示被占用 
};

template <class T>
void CreateHashTable(HashTable<T> tbl[], T data[], int len)
{
	for(int  i = 0; i < len + 1; i++ ) //把哈希表被占用标志置为0 
	{
		tbl[i].used = 0;
	}
	for(int i=0; i < len; i++ )
	{
		T addr = data[i] % (SIZE + 1);// 除留余数法计算哈希地址 
		int k = 0;//记录冲突次数 
		while(k++ < SIZE + 1)
		{
			if(tbl[addr].used == 0 )
			{
				tbl[addr].used = 1;//表示该位置已经被占用 
				tbl[addr].key = data[i];
				break;
			}
			else
			{
				addr = (addr + 1) % (SIZE + 1); //处理冲突 
			}
		}	
	}
}

template <class T>
int HashSearch(HashTable<T> tbl[], T key, int len)
{
	T addr = key % (len + 1);//计算Hash地址 
	int loc = -1; 
	int k = 0;//记录冲突次数 
	while(k++ < len + 1)
	{
		if(tbl[addr].key == key )
		{
			loc = addr;
			break;
		}
		else
		{
			addr = (addr + 1) % (len + 1); //处理冲突 
		}	
	}
	return loc;
}


int main(int argc, char* argv[])
{
	HashTable<int> HashTbl[SIZE + 1];

	int data[SIZE] = { 10, 8, 14, 15, 20, 31 };
    printf( "Data：  \n" );
	for(int i = 0; i < SIZE; i++ )
	{
		printf("data[%d] = %5d\n", i, data[i] );
	}
	printf("\n");

	CreateHashTable(HashTbl, data, SIZE + 1);
	printf("HashTable：  \n" );
	for(int i = 0; i < SIZE + 1; i++)
	{
		printf("tbl[%d] = %5d\n", i, HashTbl[i].key);
	}
	printf("\n");

	for(int i = 0; i < SIZE; i++)
	{
		int loc = HashSearch<int>(HashTbl, data[i], SIZE + 1);
		printf("%5d 's loc = %5d\n", data[i], loc);
	}
	
	return 0;
}


