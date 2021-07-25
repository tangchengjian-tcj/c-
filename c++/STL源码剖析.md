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
