# simple_calculator  
## first week homework exercise（C++）  
### 简易计算器  
要求：  
（1）采用C++ 11标准编写  
（2）命令行界面交互  
（3）输入算式，回车后能够返回结果  
（4）支持加减乘除四则混合运算  
（5）支持括号  
（6）支持整数和小数混合运算

### 使用说明：

VS文件夹为Visual Studio 2019版本项目，本地测试正常，可直接解决方案使用  
dev_C++文件夹含在Dev-C++ 5.11版本下编译正常的单cpp文件与编译结果，可直接运行exe文件   
两版本中不同点只有字符串复制时，使用的函数不同，VS中使用strcpy_s()  

### 函数说明：
```
void delspaces(char*);//删除输入字符串中的空格  
char* pro_kh(char* str, int& index);//返回括号内字符串  
double get_tw(char* str, int& index);//读取字符，括号内容处理，数值计算  
double get_cc(char* str, int& index);//进行乘除运算  
double calc(char* str);		//进行加减运算  
```

### 整体思路：  

`读取字符串-除去空格-检查括号-先乘除再加减-结果输出`  

**处理方向**  

不需要处理复数，整数小数混合  
栈较为复杂，涉及小数处理代码较长  
需要拆分字符，不太适合string   
尝试char和循环套娃

**函数思考**  

函数一：删空格 delspaces   
函数二：拆括号得字符串 pro_kh 需要循环操作   
函数三：读取字符，尤其是操作符，方便后面套娃  
对小数负数括号进行处理，得到具体的值 get_tw  
函数四：乘除算式看成一个项，计算出具体项值 get_cc  
函数五：对项进行加减运算 calc   
套娃：五（四（三（二、五）））  
calc加减的是乘除项的值get_cc  
get_cc里乘除的是左右两项的值get_tw  
get_tw里计算数自身值和括号(看作一项)内加减乘除值   
