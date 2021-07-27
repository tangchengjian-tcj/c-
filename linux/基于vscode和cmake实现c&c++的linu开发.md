## 开发环境安装
  * 安装gcc,g++ gdb：sudo apt install bulid-essential gdb
  * 安装cmake:sudo apt install cmake
## gcc编译器
  * vscode 是通过gcc编译器来实现c/c++的编译工作的
  
  **编译过程**
  
  * 1 预处理 -pre-processing
    * -E 选项指示编译器仅对输入文件进行预处理  
    * g++ -E test.cpp -o test.i   //i文件
  * 2 编译-compiling
    * -S 编译选项告诉g++在为c++代码产生了汇编语言文件后停止编译
    * g++产生的汇编语言文件的缺省扩展名是.s
    * g++ -S test.i -o test.s   //.s文件   
  * 3 汇编-assembling
    * -C选项告诉g++仅把源代码编译成机器语言的目标代码
    * 缺省时 g++建立的目标代码文件有一个.o的扩展名  
    * g++ -c test.s -o test.o    //.o文件   
  * 4 链接-linking
    * -o编译选项来为将产生的可执行文件用指定的文件名 
    * g++ test.o -o test   
  * 5.执行文件
    * ./test
  * **直接执行文件
    * g++ test.cpp -o test
    * ./test       

  **编译参数**
   
  * -g 选项告诉 GCC 产生能被 GNU 调试器使用的调试信息以便调试你的程序 
    * g++ -g test.cpp -o test
  * -o -O 选项告诉 GCC 对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。 -O2 选项告诉
  
         GCC 产生尽可能小和尽可能快的代码。 如-O2，-O3，-On（n 常为0--3）；
        -O  主要进行跳转和延迟退栈两种优化；
        -O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等。
        -O3 则包括循环展开和其他一些与处理特性相关的优化工作。
        选项将使编译的速度比使用 -O 时慢， 但通常产生的代码执行速度会更快。
        如：
          [root@localhost test]# gcc test.c -O3
          [root@localhost test]# gcc -O3 test.c
          [root@localhost test]# gcc -o tt test.c -O2
          [root@localhost test]# gcc -O2 -o tt test.c
  * -l和-L  -l参数就是用来指定程序要链接的库，-l参数紧接着就是库名，那么库名跟真正的库文件名有什么关系呢？ 就拿数学库来说，他的库名是m，他的库文件名是libm.so，很容易看出，把库文件名的头lib和尾.so去掉就是库名
    * g++ -L/home/bing/mytestibfloder -lmytest test.cpp 
  * -I ：指定文件搜索目录
  * -Wall ：打印警告信息
  * -w:关闭警告信息
  * -std=c++11 设置编译标准
  * -o 指定输出文件名
  * -D：定义宏 
