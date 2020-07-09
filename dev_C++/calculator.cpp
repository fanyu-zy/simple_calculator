#include <iostream>
#include <cctype> //isdigit()
#include <cstring>//strcpy() 
//»ù´¡¶¨Òå£¬¼ÆËãÊ½Ôİ¶¨³¤¶È80
using std::cin;
using std::cout;
using std::endl;
using namespace std;
const int  MAX(80); 
 
//º¯ÊıÉùÃ÷ char* ×Ö·û´® int&ÒıÓÃ±äÁ¿
void delspaces(char* exp);		//É¾³ı¿Õ¸ñµÄº¯Êı
char* pro_kh(char* str, int& index);//·µ»ØÀ¨ºÅÄÚ×Ö·û´® 
double get_tw(char* str, int& index);//À¨ºÅ´¦Àí ÊıÖµ¼ÆËã 
double calc(char* str);		// + - 
double get_cc(char* str, int& index);// * / 

int main()
{
	char expression[MAX] = {0};
	cout <<"\t¼òÒ×¼ÆËãÆ÷£¨simple calculator£©\n"
		"----------------³ÌĞòËµÃ÷------------------\n"
		"     Ö§³ÖÕûÊıºÍĞ¡Êı»ìºÏÔËËã£¬Ö§³ÖÀ¨ºÅ\n"
		"    Ö§³Ö¼Ó(+)¼õ(-)³Ë(*)³ı(/)ËÄÔò»ìºÏÔËËã\n"
		"  ×¢:¸ºÊıÇëµ¥¶ÀÓÃ()À¨ÆğÀ´£¬()ÇëÊ¹ÓÃÓ¢ÎÄÀ¨ºÅ\n"
		"         ÊäÈë´íÎó±í´ïÊ½³ÌĞò½«ÍË³ö\n"
		"      Ê¹ÓÃ»Ø³µÍË³ö£¬½öÖ§³Ö"<<MAX<<"¸ö×Ö\n"
		"     ÊäÈë·¶Àı£º((-21)*3+23)/2+20.20-07.09\n" 
		"------------------------------------------"
		<<endl;
		
	for(;;)//å¾ªç¯è¯»å–ï¼Œä¸ºç©ºé€€å‡º 
   {
   		cout<<"ÇëÊäÈëËãÊ½£¨Ê¹ÓÃ»Ø³µÍË³ö£©£º"<<endl;
      	cin.getline(expression, sizeof expression);  
      	delspaces(expression);
 
     	if(!expression[0])
        	return 0;
 		cout<<"¼ÆËãµÃ£º"<<expression
		 <<" = " <<calc(expression)<<endl;
   }
	system("pause");
    return 0;
}
void delspaces(char* exp)//É¾³ı¿Õ¸ñ
{
	int i=0,j=0;//Îª¿Õ¸´ÖÆºóÒ»Ïî£¬²»Îª¿ÕÍùºó×ß
	while (*(exp+i) != '\0') 
	{
		*(exp + i) = *(exp + j++);
		if (*(exp + i) != ' ')
			i++;
	}
	return;
}
char* pro_kh(char* str, int& index)//²ğÀ¨ºÅ 
{
	char buffer[MAX];//¾Ö²¿Êı×é
	char* pstr(nullptr);
	int numcount=0,bufindex=index;//¼ÆÊıÆ÷(0½áÊø1¼ÌĞøÌ×ÍŞ) ÆğÊ¼Î»ÖÃ 
	do//»ñÈ¡À¨ºÅÄÚ×Ö·û´®£¬Ö±µ½×îºóÒ»¸ö×Ö·û
	{
		buffer[index - bufindex] = *(str + index); 
		switch (buffer[index- bufindex])
		{
		case ')':
			if (0 == numcount)//µ½´ï×îºóÒ»¸öÓÒÀ¨ºÅ£¬´´½¨ĞÂ×Ö·û´®·µ»Ø 
			{
				buffer[index - bufindex] = '\0';
				++index;
				pstr = new char[index - bufindex];
				strcpy(pstr,buffer);
				return pstr;
			}
			else//Î´µ½µ×¼ÌĞøÌ×ÍŞ 
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
double get_tw(char* str, int& index)//ÊıÖµ»ñÈ¡,Ì×ÍŞ¹Ø¼ü 
{//·µ»Ø´Óµ±Ç°²Ù×÷·ûµ½ÏÂÒ»¸ö²Ù×÷·ûÖ®¼äµÄÊı×ÖµÄÖµ£¬²¢°ÑindexµİÔöµ½ÏÂÒ»¸ö²Ù×÷·ûµÄË÷ÒıÎ»ÖÃ 
	double value=0.0;
	char czf[6];//¶¨Òå²Ù×÷·û´óĞ¡
	int ip = 0,k=0;
	while (isalpha(*(str+index))) 
		czf[ip++] = *(str + index++);
	czf[ip] = '\0';//Ìí¼Ó½áÎ²
	if (czf[0] != '\0')//Ì×ÍŞÀ¨ºÅ¼ÆËã ,×¢ÒâÖ¸ÕëÓĞ½èÓĞ»¹ 
	{
		char* cshstr = pro_kh(str, ++index);
		value = calc(cshstr);
		delete[] cshstr;
		return value;
	}
	if (*(str + index) == '(') //À¨ºÅÄÚÈİ£¬Èç¹ûÊÇ¸ºÊıÖ±½Ó×Ö·û´®×ªÊı×Ö 
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
	while (isdigit(*(str + index)))//Êı×Ö´¦Àí£¬Á¬Ğø´Ó×óÍùÓÒ£¬ÓĞĞ¡Êıµã×Ô³ËÍ³Ò»µ¥Î» 
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
double get_cc(char* str, int& index)//³Ë³ıÏî¼ÆËã 
{ //´¦ÀíºóÒÆ¶¯µ½ÏÂ¸öÔËËã²Ù×÷·û 
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
double calc(char* str)//»ù´¡Ïî¼Ó¼õ 
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


