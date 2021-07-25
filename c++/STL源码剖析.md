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
