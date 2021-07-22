### STL基本概念
* STL：标准模板库
* STL从广义上分为：容器，算法，迭代器
* 容器和算法之间通过迭代器进行无缝连接
* STL几乎所有代码都采用了模板类或者模板函数


### STL六大组件
 六大组件 分别是：容器，算法，迭代器，仿函数，适配器（配接器），空间配置器


* 容器：各种数据结构，如vector、list、deque、set、map等,用来存放数据。
* 算法：各种常用的算法，如sort、find、copy、for_each等
* 迭代器：扮演了容器与算法之间的胶合剂。
* 仿函数：行为类似函数，可作为算法的某种策略。
* 适配器：一种用来修饰容器或者仿函数或迭代器接口的东西。
* 空间配置器：负责空间的配置与管理。


### STL中容器，算法，迭代器
* 容器：
	* STL中容器就是将运用最广泛的一些数据结构实现出来
	* 容器分为：**序列式容器**和**并联式容器**两种
	* 序列式容器:强调值的排序，序列式容器中的每个元素均有固定的位置
	* 并联式容器：二叉树结构，各元素之间没有严格的物理上的顺序关系
* 算法
	* 算法分为**质变算法**和**非质变算法**
	* 质变算法：是指运算过程中会更改区间内的元素的内容，例如拷贝，替换等等
	* 非质变算法：是指运算过程中不会更改区间内的元素的内容，例如查找，计数等等
* 迭代器：
	* 提供一种方法，使之能够依序寻访某个容器所含的各个元素，而又无需暴露容器的内部表达方式


### vector
* 容器：vector
* 算法：for_each
* 迭代器：vector<int>::iterator
* vector构造函数
	* vector<T> v; //采用模板实现类实现，默认构造函数
	* vector(v.begin(), v.end()); //将v[begin(), end())区间中的元素拷贝给本身。
	* vector(n, elem); //构造函数将n个elem拷贝给本身。
	* vector(const vector &vec); //拷贝构造函数。
* vector赋值操作
	* vector& operator=(const vector &vec);//重载等号操作符
	* assign(beg, end); //将[beg, end)区间中的数据拷贝赋值给本身。
	* assign(n, elem); //将n个elem拷贝赋值给本身
* vector的大小和容量操作
	* empty(); //判断容器是否为空
	* capacity(); //容器的容量
	* size(); //返回容器中元素的个数
	* resize(int num); //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
	​ * //如果容器变短，则末尾超出容器长度的元素被删除。
	* resize(int num, elem); //重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
	​ * //如果容器变短，则末尾超出容器长度的元素被删除

### 常用容器
* string容器
* string构造函数
	* string(); //创建一个空的字符串 例如: string str; string(const char* s); //使用字符串s初始化
	* string(const string& str); //使用一个string对象初始化另一个string对象
	* string(int n, char c); //使用n个字符c初始化

* string赋值操作
	* string& operator=(const char* s); //char*类型字符串 赋值给当前的字符串
	* string& operator=(const string &s); //把字符串s赋给当前的字符串
	* string& operator=(char c); //字符赋值给当前的字符串
	* string& assign(const char *s); //把字符串s赋给当前的字符串
	* string& assign(const char *s, int n); //把字符串s的前n个字符赋给当前的字符串
	* string& assign(const string &s); //把字符串s赋给当前字符串
	* string& assign(int n, char c); //用n个字符c赋给当前字符串
* string字符串拼接
	* string& operator+=(const char* str); //重载+=操作符
	* string& operator+=(const char c); //重载+=操作符
	* string& operator+=(const string& str); //重载+=操作符
	* string& append(const char *s); //把字符串s连接到当前字符串结尾
	* string& append(const char *s, int n); //把字符串s的前n个字符连接到当前字符串结尾
	* string& append(const string &s); //同operator+=(const string& str)
	* string& append(const string &s, int pos, int n);//字符串s中从pos开始的n个字符连接到字符串结尾
* deque容器
	* 功能：双端数组，可以对头端进行插入删除操作
	* deque与vector的区别：
		* vector容器对于头部的插入删除效率低，数据量大，效率低
		* duque容器相对而言，对头部的插入删除速度比vector快
		* vector容器访问元素的速度会比deque快，这和两者内部实现有关


* stack容器
	* 概念：是一种先进后出的数据结构，只有一个出口
	* 栈
* queue容器
	* 概念：是一种先进先出的数据结构，有两个出口
	* 队列
* list容器
	* 概念：将数据进行链式存储
	* 链表
* set/multiset容器
	* 简介：所有元素都会在插入时自动排序
	* 本质：set/multiset属于关联式容器，底层是用二叉树实现的
	* set/multiset的区别
		* set不允许容器中有重复的元素， multiset允许容器中出现重复的元素
		* set插入数据的同时会返回插入结果，表示是否插入成功
		* multiset不会检测数据，因此可以插入重复数据
* pair对组创建
	* 功能描述：成对出现的数据，利用对组可以返回两个数据
	* 两种创建方式
		* pair<type,type> p(value1,value2);
		* pair<type,type> p = make_pair(value1,value2);
* map/ multimap容器
	* 简介：
		* map中元素都是pair
		* pair中第一个元素为key（键值），起索引作用，第二个元素是value
		* 所有元素都会根据元素的键值自动排序
		* map/multimap属于关联式容器，底层结构都是二叉树实现的
	* map/multimap的区别
		* map中不允许出现重复的键值对，multimap允许出现重复的键值对


### 函数对象
 * **一个函数对象，即一个重载了括号操作符的（）对象，当用该对象调用此操作符时，其表现形式如同普通函数调用一般，因此叫错函数对象。**
* 概念：
	* 重载函数调用操作符的类，其对象称为函数对象
	* 函数对象使用重载的()的时，行为类似函数调用，也叫仿函数
* 本质：函数对象（仿函数）是一个类，不是一个函数
* 谓词
	* 概念：	
		* 返回bool类型的仿函数称为谓词
		* 如果operator()接受一个参数，称为一元谓词
		* 如果operator()接受两个参数，称为二元谓词
* 内建函数对象
	* 分类
		* 算术仿函数
		* 关系仿函数
		* 逻辑仿函数
	* 用法
		* 这些仿函数所产生的对象，用法和一般函数完全相同
		* 使用内建函数对象，需要引入头文件#include<functional>
