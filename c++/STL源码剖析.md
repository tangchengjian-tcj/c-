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
### STL概论
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
* 
