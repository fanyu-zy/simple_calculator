#include <iostream>
#include <cctype> //isdigit()
#include <cstring>//strcpy() 
//基础定义，计算式暂定长度80
using std::cin;
using std::cout;
using std::endl;
using namespace std;
const int  MAX(80); 
 
//函数声明 
void delspaces(char*);		//删除空格的函数
char* pro_kh(char* str, int& index);//返回括号内字符串 
double get_tw(char* str, int& index);//括号处理 数值计算 
double calc(char* str);		// + - 
double get_cc(char* str, int& index);// * / 

int main()
{
	char expression[MAX] = {0};
	cout <<"\t简易计算器（simple calculator）\n"
		"----------------程序说明------------------\n"
		"     支持整数和小数混合运算，支持括号\n"
		"    支持加(+)减(-)乘(*)除(/)四则混合运算\n"
		"  注:负数请单独用()括起来，()请使用英文括号\n"
		"         输入错误表达式程序将退出\n"
		"      使用回车退出，仅支持"<<MAX<<"个字\n"
		"      输入范例：((-21)*3+23)/2+20.20-07.09\n" 
		"------------------------------------------"
		<<endl;
		
	for(;;)//循环读取，为空退出 
   {
   		cout<<"请输入算式（使用回车退出）："<<endl;
      	cin.getline(expression, sizeof expression);  
      	delspaces(expression);
 
     	if(!expression[0])
        	return 0;
 		cout<<"计算得："<<expression
		 <<" = " <<calc(expression)<<endl;
   }
	system("pause");
    return 0;
}
void delspaces(char* exp)//删除空格
{
	int i=0,j=0;//为空复制后一项，不为空往后走 
	while (*(exp+i) != '\0') 
	{
		*(exp + i) = *(exp + j++);
		if (*(exp + i) != ' ')
			i++;
	}
	return;
}
char* pro_kh(char* str, int& index)//拆括号 
{
	char buffer[MAX];//局部数组
	char* pstr(nullptr);
	int numcount=0,bufindex=index;//计数器(0结束1继续套娃) 起始位置 
	do//获取括号内字符串，直到最后一个字符 
	{
		buffer[index - bufindex] = *(str + index); 
		switch (buffer[index- bufindex])
		{
		case ')':
			if (0 == numcount)//到达最后一个右括号，创建新字符串返回 
			{
				buffer[index - bufindex] = '\0';
				++index;
				pstr = new char[index - bufindex];
				strcpy(pstr,buffer);
				return pstr;
			}
			else//未到底继续套娃 
			{
				numcount--;
				break;
			}
		case '(':
			numcount++;
			break;
		}
	} while (*(str + index++) != '\0');
}
double get_tw(char* str, int& index)//数值获取,套娃关键 
{//返回从当前操作符到下一个操作符之间的数字的值，并把index递增到下一个操作符的索引位置 
	double value=0.0;
	char opname[6];//定义操作符大小
	int ip = 0,k=0;
	while (isalpha(*(str+index))) 
		opname[ip++] = *(str + index++);
	opname[ip] = '\0';//添加结尾
	if (opname[0] != '\0')//套娃括号计算 ,注意指针有借有还 
	{
		char* numberexp = pro_kh(str, ++index);
		value = calc(numberexp);
		delete[] numberexp;
		return value;
	}
	if (*(str + index) == '(') //括号内容，如果是负数直接字符串转数字 
	{
		char* psubstr(nullptr);
		psubstr = pro_kh(str, ++index);
		if(psubstr[0]=='-')
		{
			value=atof(psubstr);	
		}
		else
			value = calc(psubstr);
		delete[]psubstr;
		return value;
		
	}
	if (isdigit(*(str + index))==false) 
	{
		exit(1); 
	}
	while (isdigit(*(str + index)))//数字处理，连续从左往右，有小数点自乘统一单位 
		value = value * 10 + (*(str + index++) - '0');
	if (*(str + index) != '.')
		return value;
	double tydw = 1.0;
	while (isdigit(*(str + (++index))))
	{
		tydw = tydw*0.1;
		value = value + (*(str + index) - '0')*tydw;
	}
	return value;
 }
double get_cc(char* str, int& index)//乘除项计算 
{ //处理后移动到下个运算操作符 
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
double calc(char* str)//基础项加减 
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


