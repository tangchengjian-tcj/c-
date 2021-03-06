讲义：
  * linux系统介绍：https://mp.weixin.qq.com/s/cFZ9DJCROF51c6xbYXaYaA 
  * gcc编译器：https://mp.weixin.qq.com/s/UKz0XjFejT3eINgie_sc3w
  * GDB调试器：https://mp.weixin.qq.com/s/3uibMHewV-zGGAczlJq-pQ
  * vscode:https://mp.weixin.qq.com/s/Y1z4Og-BUluqTGMAM7DHhA
  * cmake：https://mp.weixin.qq.com/s/nmjQIezDb44a089YMQvNyw
  * 实战：https://mp.weixin.qq.com/s/Clq_DPLry9yijZPiCiVUXg

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


## GDB调试器
 **GDB主要功能**
   * 设置断点（断点可以是条件表达式）
   * 使程序在指定代码行上暂停执行，便于观察
   * 查看程序中变量值的执行环境
   * 动态改变程序的执行环境
   * 分析崩溃程序产生的core文件
 **常用的GDB调试命令参数**
   
   调试开始：执行 **gdb [exefilename] ** ，进入到gdb调试程序，其中exefilename为要调试的可执行文件名
   
   
   编译程序时需要加上-g，之后才能用gdb进行调试：gcc -g main.c -o main
   
   
   回车键：重复上一命令
   
          ## 以下命令后括号内为命令的简化使用，比如run（r），直接输入命令 r 就代表命令run
          $(gdb)help(h)        # 查看命令帮助，具体命令查询在gdb中输入help + 命令 
          $(gdb)run(r)         # 重新开始运行文件（run-text：加载文本文件，run-bin：加载二进制文件）
          $(gdb)start          # 单步执行，运行程序，停在第一行执行语句
          $(gdb)list(l)        # 查看原代码（list-n,从第n行开始查看代码。list+ 函数名：查看具体函数）
          $(gdb)set            # 设置变量的值
          $(gdb)next(n)        # 单步调试（逐过程，函数直接执行）
          $(gdb)step(s)        # 单步调试（逐语句：跳入自定义函数内部执行）
         $(gdb)backtrace(bt)  # 查看函数的调用的栈帧和层级关系
         $(gdb)frame(f)       # 切换函数的栈帧
         $(gdb)info(i)        # 查看函数内部局部变量的数值
         $(gdb)finish         # 结束当前函数，返回到函数调用点
         $(gdb)continue(c)    # 继续运行
         $(gdb)print(p)       # 打印值及地址
         $(gdb)quit(q)        # 退出gdb
         $(gdb)break+num(b)                 # 在第num行设置断点
         $(gdb)info breakpoints             # 查看当前设置的所有断点
         $(gdb)delete breakpoints num(d)    # 删除第num个断点
         $(gdb)display                      # 追踪查看具体变量值
         $(gdb)undisplay                    # 取消追踪观察变量
         $(gdb)watch                        # 被设置观察点的变量发生修改时，打印显示
         $(gdb)i watch                      # 显示观察点
         $(gdb)enable breakpoints           # 启用断点
         $(gdb)disable breakpoints          # 禁用断点
         $(gdb)x                            # 查看内存x/20xw 显示20个单元，16进制，4字节每单元
         $(gdb)run argv[1] argv[2]          # 调试时命令行传参
         $(gdb)set follow-fork-mode child   # Makefile项目管理：选择跟踪父子进程（fork()）
         
         
         
         
         
         
## cmake
 
 简介：
   
   * CMake是一个跨平台的安装编译工具，可以用简单的语句来描述所有平台的安装(编译过程)。
  
  
 语法特性：
      
   * 基本格式：指令（参数1 参数2）
     *  参数之间用空格或者分号分开，参数用括弧括起来
     *  指令的大小写是无关的，参数和变量大小写是相关的
     *  变量使用${}方式取值，但是在IF控制语句中直接使用变量名

   * 重要指令和cmake常用变量
     * cmake_minimum_required - 指定CMake的最小版本要求 
       * 语法：cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])
       * cmake_minimum_required(VERSION 2.8.3)
     * project - 定义工程名称，并可指定工程支持的语言  
       * project(HELLOWORLD)
       * project(projectname [CXX] [C] [Java])
     * set - 显式的定义变量  
       * set(SRC sayhello.cpp hello.cpp)
       * set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
     * include_directories - 向工程添加多个特定的头文件搜索路径  --->相当于指定g++编译器的-I参数
       * include_directories(/usr/include/myincludefolder ./include)
       * include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2 …)
     * 相关内容看链接



##  实战_完整项目开发
 
 案例
 
 * 需求
  * 士兵许三多有一把抢，叫做ak47
  * 士兵可以开火
  * 士兵可以装填子弹
  * 枪可以发射子弹
  * 枪可以装填子弹--添加子弹数量
 
 
 配置文件修改
 
 * 修改launch.json设置debug
   * 将launch.json中的program的内容改为当前项目的可执行文件路径
   * 然后F5进行debug
 * 修改task.json中的内容进行（修改内容不用重新make也可直接进行debugg）
   * 将preLaunchTask中的内容改为task.json中的label 
