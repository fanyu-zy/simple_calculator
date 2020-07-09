#include <iostream>
#include <cctype> //isdigit()
#include <cstring>//strcpy() 
//�������壬����ʽ�ݶ�����80
using std::cin;
using std::cout;
using std::endl;
using namespace std;
const int  MAX(80);

//�������� 
void delspaces(char* exp);		//ɾ���ո�ĺ���
char* pro_kh(char* str, int& index);//�����������ַ��� 
double get_tw(char* str, int& index);//���Ŵ��� ��ֵ���� 
double calc(char* str);		// + - 
double get_cc(char* str, int& index);// * / 

int main()
{
	char expression[MAX] = { 0 };
	cout << "\t���׼�������simple calculator��\n"
		"----------------����˵��------------------\n"
		"     ֧��������С��������㣬֧������\n"
		"    ֧�ּ�(+)��(-)��(*)��(/)����������\n"
		"  ע:�����뵥����()��������()��ʹ��Ӣ������\n"
		"         ���������ʽ�����˳�\n"
		"      ʹ�ûس��˳�����֧��" << MAX << "����\n"
		"      ���뷶����((-21)*3+23)/2+20.20-07.09\n"
		"------------------------------------------"
		<< endl;

	for (;;)//ѭ����ȡ��Ϊ���˳� 
	{
		cout << "��������ʽ��ʹ�ûس��˳�����" << endl;
		cin.getline(expression, sizeof expression);
		delspaces(expression);

		if (!expression[0])
			return 0;
		cout << "����ã�" << expression
			<< " = " << calc(expression) << endl;
	}
	system("pause");
	return 0;
}
void delspaces(char* exp)//ɾ���ո�
{
	int i = 0, j = 0;//Ϊ�ո��ƺ�һ���Ϊ�������� 
	while (*(exp + i) != '\0')
	{
		*(exp + i) = *(exp + j++);
		if (*(exp + i) != ' ')
			i++;
	}
	return;
}
char* pro_kh(char* str, int& index)//������ 
{
	char buffer[MAX];//�ֲ�����
	char* pstr(nullptr);
	int numcount = 0, bufindex = index;//������(0����1��������) ��ʼλ�� 
	do//��ȡ�������ַ�����ֱ�����һ���ַ� 
	{
		buffer[index - bufindex] = *(str + index);
		switch (buffer[index - bufindex])
		{
		case ')':
			if (0 == numcount)//�������һ�������ţ��������ַ������� 
			{
				buffer[index - bufindex] = '\0';
				++index;
				pstr = new char[index - bufindex];
				strcpy_s(pstr, index - bufindex, buffer);//strcpy(pstr, buffer);
				return pstr;
			}
			else//δ���׼������� 
			{
				numcount--;
				break;
			}
		case '(':
			numcount++;
			break;
		default:
			break;
		}
	} while (*(str + index++) != '\0');
	return pstr;
}
double get_tw(char* str, int& index)//��ֵ��ȡ,���޹ؼ� 
{//���شӵ�ǰ����������һ��������֮������ֵ�ֵ������index��������һ��������������λ�� 
	double value = 0.0;
	char czf[6],s;//�����������С
	int ip = 0, k = 0;
	while (isalpha(*(str + index)))
		czf[ip++] = *(str + index++);
	czf[ip] = '\0';//��ӽ�β
	if (czf[0] != '\0')//�������ż��� ,ע��ָ���н��л� 
	{
		char* cshstr = pro_kh(str, ++index);
		value = calc(cshstr);
		delete[] cshstr;
		return value;
	}
	if (*(str + index) == '(') //�������ݣ�����Ǹ���ֱ���ַ���ת���� 
	{
		char* psubstr(nullptr);
		psubstr = pro_kh(str, ++index);
		if (psubstr[0] == '-')
		{
			value = atof(psubstr);
		}
		else
			value = calc(psubstr);
		delete[]psubstr;
		return value;

	}
	if (isdigit(*(str + index)) == false)
	{
		exit(1);
	}
	while (isdigit(*(str + index)))//���ִ��������������ң���С�����Գ�ͳһ��λ
	{
		s = *(str + index++) - '0';
		value = value * 10 + s;
	}
	if (*(str + index) != '.')
		return value;
	double tydw = 1.0;
	while (isdigit(*(str + (++index))))
	{
		s = *(str + index) - '0';
		tydw = tydw * 0.1;
		value = value + s * tydw;
	}
	return value;
}
double get_cc(char* str, int& index)//�˳������ 
{ //������ƶ����¸���������� 
	double value(0.0);
	value = get_tw(str, index);
	while (true)
	{
		if (*(str + index) == '*')
			value *= get_tw(str, ++index);
		else if (*(str + index) == '/')
			value /= get_tw(str, ++index);
		else
			break;
	}
	return value;
}
double calc(char* str)//������Ӽ� 
{
	double value(0.0);
	int index = 0;
	value = get_cc(str, index);
	for (;;)
	{
		switch (*(str + index++))
		{
		case '+':
			value += get_cc(str, index);
			break;
		case '-':
			value -= get_cc(str, index);
			break;
		case '\0':
			return value;
		default:
			exit(1);
			break;
		}
	}
}