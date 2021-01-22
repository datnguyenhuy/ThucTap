#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#pragma warning(disable:4996)
using namespace std;

struct Node {
	int MaNode;
	char TenNode[10];
	int soNutCon;
	struct Node* NodeCon[10];
	struct Node* next;
};

typedef struct Node* node;

string X, Y, Z;

node Search(node head, int numberParent) {
	node p;
	for (p = head; p != NULL; p = p->next) {
		if (p->MaNode== numberParent) {
			return p;
		}
	}
	return NULL;
}

node SearchByName(node head, string name) {
	node p;
	for (p = head; p != NULL; p = p->next) {
		if (p->TenNode == name) {
			return p;
		}
	}
	return NULL;
}

node CreateNode(node head,int number,int numberParent,char name[])
{
	node temp;
	temp = (node)malloc(sizeof(struct Node)); // Cấp phát vùng nhớ dùng malloc()
	temp->MaNode= number;
	strcpy(temp->TenNode,name);
	temp->next = NULL;
	node search = Search(head, numberParent);
	if (search != NULL)
	{
		if (search->soNutCon < 0) search->soNutCon = 0;
		search->NodeCon[search->soNutCon] = temp;
		search->soNutCon++;
	}
	return temp;//Trả về node mới đã có giá trị
}

node AddTail(node head, int number, int numberParent, char name[]) {
	node temp, p;// Khai báo 2 node tạm temp và p
	temp = CreateNode(head,number,numberParent,name);//Gọi hàm createNode để khởi tạo node temp có next trỏ tới NULL và giá trị là value
	if (head == NULL) {
		head = temp;     //Nếu linked list đang trống thì Node temp là head luôn
	}
	else {
		p = head;// Khởi tạo p trỏ tới head
		while (p->next != NULL) {
			p = p->next;//Duyệt danh sách liên kết đến cuối. Node cuối là node có next = NULL
		}
		p->next = temp;
	}
	return head;
}

node AddHead(node head, int number, int numberParent, char name[]) {
	node temp = CreateNode(head,number, numberParent, name);
	if (head == NULL) {
		head = temp; // //Nếu linked list đang trống thì Node temp là head luôn
	}
	else {
		temp->next = head; // Trỏ next của temp = head hiện tại
		head = temp; // Đổi head hiện tại = temp
	}
	return head;
}

char result[30][10];
int bienchay = 0;

bool Duyet(node head,string sta,string fin)
{
	for (int i = 0; i < head->soNutCon; i++)
	{
		if (head->NodeCon[i]->TenNode == fin)
			return true;
		else
		{
			if (Duyet(head->NodeCon[i], head->NodeCon[i]->TenNode, fin) == true)
			{
				for (int j = 0; j < 10; j++)
				{
					result[bienchay][j] = head->NodeCon[i]->TenNode[j];
				}
				bienchay++;
				return true;
			}
		}
	}
	return false;
}

void DuyetTatCa(node head)
{
	for (int i = 0; i < head->soNutCon; i++)
	{
		cout << head->NodeCon[i]->MaNode << " "<< head->NodeCon[i]->TenNode<<endl;
		if (head->NodeCon[i]->soNutCon == 0)
		{
			break;
		}
		else
		{
			DuyetTatCa(head->NodeCon[i]);
		}
	}
}


int main()
{
	node head = NULL;

	ifstream input("C:\\datnguyenhuy\\tree.txt");
	if (input.is_open())
	{
		int number, numberParent;
		char name[10];

		while ((input >> number >> numberParent >> name ))
		{
			if (number == 1)
			{
				head=AddHead(head, number, numberParent, name);
			}
			else
			{
				head= AddTail(head, number, numberParent, name);
			}
			cout << number << " " << numberParent << " " << name << "\n";
		}
	}

	cin >> X >> Y;

	node p = SearchByName(head, X);

	if (Duyet(p, X, Y) == true)
	{
		Duyet(p, X, Y);
		cout << X << "=>";
		for (int i = bienchay - 1; i >= bienchay / 2; i--)
		{
			cout << result[i] << "=>";
		}
		cout << Y << endl;
	}
	else {
		printf("X khong phai cha cua Y");
	}
	
	cin >> Z;
	node q = SearchByName(head, Z);
	if (q == NULL)
	{
		cout << "Khong co nut trong cay" << endl;
	}
	else {
		cout << endl << "Tat ca cac node cua " << Z << "la" << endl;
		DuyetTatCa(q);
	}

	return 0;
}