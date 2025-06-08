#include "Hash.h"
#include <iostream>

// ���-������� � �������������� ������ ���������
int HashFunction(int key, int size, int p)
{
	// ��������� �� ������������ ����������� ��� ������ ������� 2^k
	const uint32_t A = 2654435769; // (sqrt(5)-1)/2 * 2^32
	const uint32_t BITS = 32;

	// ��������� �� ��������� � ������ ������� �����
	uint32_t hash = (uint32_t)key * A;
	hash >>= (BITS - (int)log2(size)); // ���������� log2 ��� ��� size=2^k

	// ��������� ������������ ������������
	return (hash + p + p * p) % size;
}
//-------------------------------
// ������� ���������� �������� (������������ ������������)
int Next_hash(int hash, int size, int p)
{
	return (hash + p + p*p) % size; // ������������ ������������������
}
//-------------------------------
// ��������� ����� �������� �������
Object create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey));
}
//-------------------------------
// ����������� ������� �������
Object::Object(int size, int(*getkey)(void*))
{
	N = 0;                // ������������� �������� ���������
	this->size = size;    // ��������� ������� �������
	this->getKey = getkey;// ���������� ������� ��������� �����
	this->data = new void* [size]; // ��������� ������
	for (int i = 0; i < size; ++i)
		data[i] = NULL;   // ������������� �����
}
//-------------------------------
// ����� ������� ��������
bool Object::insert(void* d)
{
	bool b = false;
	if (N != size) // �������� �� ������������
		// ���� ������������ � �������������� ���-�������
		for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0);
			i != size && !b;
			j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL) // ����� ��������� ������
			{
				data[j] = d;  // ������� ��������
				N++;          // ���������� ��������
				b = true;     // ���� �������� �������
			}
	return b;
}
//-------------------------------
// ����� ������� �������� �� �����
int Object::searchInd(int key)
{
	int t = -1; // ������ �� ������
	bool b = false;
	if (N != 0) // �������� �� ������ �������
		// ���� ������������ � ������� ������������
		for (int i = 0, j = HashFunction(key, size, 0);
			data[j] != NULL && i != size && !b;
			j = HashFunction(key, size, ++i))
			if (data[j] != DEL) // ������� ��������� ���������
				if (getKey(data[j]) == key) // �������� ���������� �����
				{
					t = j; b = true; // ��������� ������
				}
	return t;
}
//-------------------------------
// ����� �������� �� ����� � ����������� ��� ������
void* Object::search(int key)
{
	int t = searchInd(key); // �������� ������ ����� searchInd
	return(t >= 0) ? (data[t]) : (NULL); // ���������� ������ ��� NULL
}
//-------------------------------
// �������� �������� �� ����� (���������� ��������)
void* Object::deleteByKey(int key)
{
	int i = searchInd(key); // ����� ������� ��������
	void* t = data[i]; // ���������� ��������� �� ������
	if (t != NULL)
	{
		data[i] = DEL; // �������� ������ ��� ���������
		N--; // ��������� ������� ���������
	}
	return t; // ���������� ��������� ������ (��� NULL)
}
//-------------------------------
// �������� �������� �� ��������
bool Object::deleteByValue(void* d)
{
	// ���������� deleteByKey, ���������� �������� � ����
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------
// ����� ����������� ������� � ���������������� ���������������
void Object::scan(void(*f)(void*))
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << " ������� " << i;
		// ��������� ���� ��������� ������:
		if ((this->data)[i] == NULL)
			std::cout << "  �����" << std::endl; // ������ ������
		else if ((this->data)[i] == DEL)
			std::cout << "  ������" << std::endl; // ��������� �������
		else
			f((this->data)[i]); // ����� ���������������� ������� ������
	}
}