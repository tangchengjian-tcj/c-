#### 基础知识补充
### 转换构造函数和隐士转换函数
  * 转换构造函数
    * 转换构造函数的作用就是将一个其他类型的数据转换成一个类的对象，(当一个构造参数只有一个参数，而且该参数又不是本类的const引用时，这种构造函数称为转换构造函数)
    
    ```
    class Complex  
    {  
      public:  
        Complex():real(0),imag(0){};  
        Complex(double r, double i):real(r),imag(i){};  
        Complex(double r):real(r),imag(0){};  // 定义转换构造函数  
        
      private:  
        double real;  
        double imag;  
    };  
    ```
    
    * 注意：
      * 用转换构造函数可以将一个指定类型的数据转换为类的对象｡但是不能反过来将一个类的对象转换为一个其他类型的数据(例如将一个Complex类对象转换成double类型数据)。
      * 如果不想让转换构造函数生效，也就是拒绝其它类型通过转换构造函数转换为本类型，可以在转换构造函数前面加上explicit！  
      ```
      
        class Complex  
        {  
        public:  
            Complex():real(0),imag(0){};  
            Complex(double r, double i):real(r),imag(i){};  
            explicit Complex(double r):real(r),imag(0){};  // explicit禁止构造函数的转换功能  

            void Print(){  
                cout<<"real = " << real <<" image = "<<imag<<endl;  
            }  
        private:  
            double real;  
            double imag;  
        };  

        int main(int argc, _TCHAR* argv[])  
        {  
            Complex c1(1.2, 2.3), c2;  
            double d;  
            d = c1 + 1.1; // 调用类型转换函数将c1转换为double，编译出错！  
            cout<<d<<endl;  

            return 0;  
        }
      
      ```
      
  * 类型转换函数
    * 作用：类型转换函数的作用是将一个类的对象转换成另一类型的数据｡
    * 一般形式
    
      ···
      
          operator 类型名( )
          {
                 实现转换的语句
          }
      ···
      
    * 注意：
      *  在函数名前面 不能指定函数类型,函数没有参数｡
      * 2.其 返回值的类型是由函数名中指定的类型名来确定的｡
      * 3.类型转换函数 只能作为成员函数,因为转换的主体是本类的对象， 不能作为友元函数或普通函数｡
      * 4.从函数形式可以看到,它与运算符重载函数相似,都是用关键字operator开头,只是被重载的是类型名｡double类型经过重载后,除了原有的含义外,还获得新的含义(将一个Complex类对象转换为double类型数据,并指定了转换方法)｡这样, 编译系统不仅能识别原有的double型数据,而且还会把Complex类对象作为double型数据处理｡

####  源码剖析
## STL概论
  STL六大组件
  

  * 容器：containers
  * 算法：algorithms
  * 迭代器：iterators
  * 仿函数：functions
  * 配接器：adapters
  * 配置器：allocators
    
    
  六大组件的交互关系：container通过allocators取得数据存储空间，algorithm通过iterator存储continers内容，functor 可以协助algorithm完成不同的策略，adapter可以修饰或者套接functor
  
  
  * **SGI SRL文件分布与简介**
    * c++标准规范下的c头文件(无拓展名)，例如，cstdio,cstdlib,cstring
    * c++标准程序库中不属于STL范畴者，例如，stream,string文件
    * STL标准头文件(无拓展名)，例如vector,deque,list。。。
    * c++standard定案前，HP所规范的STL头文件，例如，vector.h,deque.h
    * SGI STL内部文件（STL真正实现于此)，例如，stl_vector.h,stl_deque.h....

## 空间配置器

   ```
    
    首先介绍了SGI STL的配置器alloc,然后介绍构造内存alloc::allocate() 和分配对象 ::construct() ，释放内存alloc::deallocate()和解析对象::destroy()  ,并介绍函数中内容
    其中对于内存的创建和释放，采用了双层配置器机制
    双层配置器机制：
        第一级配置器直接使用malloc(),free(),realloc()等C函数执行实际的内存配置、释放、重配置操作，并实现出类似C++ new handler机制（意思是可以要求系统在配置需求无法被满足时，调用一个你所指定的函数，这里之所以说类似是因为SGI没有new operator，不能直接使用对应的handler）。
         第二层配置器：
                如果要分配的区块大于128bytes，则移交给第一级配置器处理。
                如果要分配的区块小于128bytes，则以内存池管理（memory pool），又称之次层配置）：每次配置一大块内存，并维护对应的自由链表（free-list）。下次若有相同大小的内存需求，则直接从free-list中取。如果有小额区块被释放，则由配置器回收到free-list中。

  
  ```
  
   ### https://wendeng.github.io/2019/05/13/c++%E5%9F%BA%E7%A1%80/%E3%80%8ASTL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90%E3%80%8B%E7%AC%AC2%E7%AB%A0%20%E7%A9%BA%E9%97%B4%E9%85%8D%E7%BD%AE%E5%99%A8/
   ### SGI STL配置器简介
   * SGI STL的配置器与众不同，也与标准规范不同，其名称是 alloc 而非 allocator ,而且不接受任何参数。如果要在程序中明确使用SGI配置器，那么应该这样写：
      

         vector<int,std::alloc> iv; //而不是vector<int,std::allocator<int> > iv;

   * 标准配置器的名字是allocator，而且可以接受参数。SGI STL的每一个容器都已经指定了缺省配置器：alloc。我们很少需要自己去指定空间配置器。比如vector容器的声明：
       ···
       
             template <class T, class Alloc = alloc>  // 预设使用alloc为配置器
             class vector {
             //...
             }
             
   * 其实SGI也定义了一个符合部分标准，名为allocator的配置器，但是它自己不使用，也不建议我们使用，主要原因是效率不佳。它只是把C++的操作符::operator new和::operator delete做了一层简单的封装而已，可以用但是不建议我们使用。

  ### SGI特殊的空间配置器alloc
  
   我们所习惯的c++内存配置操作和释放操作如下：
   
           class Foo { ... };
           Foo* pf = new Foo; // 配置内存，然后构造对象
           delete pf; // 将对象析构，然后释放内存
    
   这其中的new操作符（new operator）包含两阶段操作
   
      * （1）调用operator new 配置内存
      * （2）调用FOO::FOO（）构造函数构造对象内容
      
   这其中的delete操作符也包含两阶段操作
   
      * （1）调用Foo::~Foo( )析构函数将对象析构。
      * （2）调用operator delete释放内存
    
    
## 迭代器
**https://wendeng.github.io/2019/05/15/c++%E5%9F%BA%E7%A1%80/%E3%80%8ASTL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90%E3%80%8B%E7%AC%AC3%E7%AB%A0%20%E8%BF%AD%E4%BB%A3%E5%99%A8%E4%B8%8Etraits%E7%BC%96%E7%A8%8B%E6%8A%80%E6%B3%95/**
* 实际上迭代器是一种智能指针，是一种行为类似指针的对象，它内部封装了一个原始指针，并重载了operator*() 和operator->()等操作。
* 迭代器在这里使用的好处主要有：
    * (1) 不用担心内存泄漏（类似智能指针，析构函数释放内存）；
    * (2) 对于list，取下一个元素不是通过自增而是通过next指针来取，这样子暴露了太多东西，使用智能指针可以对自增进行重载，从而提供统一接口。
* 迭代器相应型别 
  * 利用function template的参数推导机制
  * partial specialization（偏特化）的意义  
    *  便特化的目的主要是为了防止传递过来的时候不是一个迭代器而是一个原生指针
  *  偏特化的简介：
    *   如果class template拥有一个以上的tempate参数，提供另一份template定义式，而本身仍为templatized
    *   针对（任何）template参数更进一步的条件限制所设计的一个特化版本。
    *   下面的class template 专门用来“萃取”迭代器的特性
          
          ···
               
               即保证了无论是原指针（func(int *)）还是迭代器iterator都可以进行执行
              template <class I>
              struct iterator_traits{
                   typedef typename I ::value_type value_type;
               }
               template<class Iterator>
               typename iterator_traits<Iterator>::value_type func(Iterator iter){return *iter;}

           ···
   
 * 迭代器相应类型
   *  1.value_type:指的是迭代器所指对象的型别
   *  2.difference_type：用来表示两个迭代器之间的距离
   *  3.refrence_type：指迭代器所指对象的类型的引用
   *  4.pointer_type：相应的指针类型
   *  5.iterator_category：标识迭代器的移动特性和可以对迭代器执行的操作


## 序列式容器
 * 简介：所谓序列式容器，其中元素都可有序，但未必有序
 
 序列式容器简介
 
 * vector容器
   * vector的实现技术，关键在于其对大小的控制以及重新配置时的数据移动效率  
   * vector的空间配置策略是：
     * 当插入元素的时候，如果配置的空间不足，则扩充空间到当前的两倍，如果仍然不足则扩充到所需的空间
     * 空间的扩张必须经历“重新配置，元素移动，释放原空间的副哦从”  
* list容器
  * list是一个环状双向链表，list不能以原生指针作为迭代器，需要定义特定的iterator类
* deque容器
  * deque与vector容器的差异
    * 一是在于deque允许常数时间内对头端进行元素的插入或移除操作
    * 二是在于deque没有所谓的容量概念，因为它是动态的以分段连续空间组合而成，随时可以增加一段新的空间并连接起来。
  * deque采用的是一种分段连续空间存储结构，采用一个mao来管理这些空间段，这里所谓map是一小块连续空间，其中每个元素哦都市指针，指向另外一段较大的连续线性空间，成为缓冲区，缓冲区才是deque的存储空间主体，SGI STL允许我们指定缓冲区大小，默认值0表示使用512bytes缓冲区。
* stack容器
  * 是一种先进后出的数据结构，只有一个出口
  * stack没有迭代器
* queue容器
  * 是一种先进先出的数据结构，有两个出口
  * 没有迭代器
* heap（堆）
  * heap并不属于STL容器组件，扮演priority queue的助手，主要分为max heap 和min heap,在缺省的情况下，max heap是priority queue的底层实现机制
  * 以array表达tree的方法，这样可以使用一个array表示出一颗完全二叉树。array的缺点是无法动态改变大小，所以实际实现机制中的max heap实际上以一个vector表现的完全二叉树
  * heap没有迭代器     
* slist是一个单向链表
  * 迭代器属于单向的Forward iterator   

## 关联式容器
 
 概念： 每笔数据都有一个键值和一个实值，当元素被插入到关联式容器中时，以某种特定规则将这个元素放置于适当位置。关联式容器没有所谓头尾（只有最大元素和最小元素）
 
 STL关联容器分为set和map两大类，这些容器的底层机制都以R-B-tree实现，R-B-tree也是一个独立容器，但是不开放使用

* 二叉搜索树：任何节点的键值（key）一定大于其左子树中的每一个节点的键值，并小于其右子树中的每一个节点的键值。
* 红黑树必须满足以下规则：
  * 每一个节点不是黑色就是红色
  * 根结点为黑色
  * 如果节点为红，其子节点就必须为黑
  * 任一节点至该节点的子孙节点的任何路径，所含之黑节点树必须相同
* 根据规则四，新增节点必须为红，根据规则三，新增节点的父节点必须为黑节点
