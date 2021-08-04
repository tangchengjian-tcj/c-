## 进程相关概念

 * 程序和进程
    * 程序：是指编译好的二进制文件，在磁盘上，不占用系统资源
    * 进程：分配系统资源的基本单位 
 * 主要用来管理虚拟存储器、物理存储器的控制线路，同时也负责**虚拟地址映射为物理地址**，以及提供硬件机制的**内存访问授权**、多任务多进程操作系统。 
 * 进程控制块
    * 在linux中找到struct task_struct结构体的定义，内部成员有很多，重点关注以下部分就可以了
        * 进程id
        * 进程状态
        * 进程切换时需要保存和恢复的一些cpu寄存器
        * 描述虚拟地址空间的信息
        * 描述控制终端的细腻县
        * 当前工作目录
        * umask掩码
        * 文件描述表，包含了很多指向file结构体的指针
        * 和信号相关的信息
        * 用户id和组id
        * 会话（session）和进程组
        * 进程可以使用的资源上限
* 环境变量
  * 查看命令 env
  * 常用环境变量
    * PATH
    * SHELL
    * TERM
    * HOME
  * 环境配置
    * .bashrc文件中 export key=value 
* 进程控制
  * fork函数，创建子进程 
  * pid_t fork(void);
    * 返回值：成功则返回  1.父进程返回子进程的id，2.子进程返回0
    * 其中fork函数调用会产生两个返回值，一个进程会变成两个进程，然后父子进程会各自返回一个 
  * getpid:返回i当前进程id
  * getppid：返回当前进程的父进程id
  * 创建多个子进程
* 父子进程共享的内容（父子进程之间在fork后）
  * 相同处：
      * 全局变量，data,text,栈，堆，环境变量，用户ID，宿主目录，进程工作目录，信号处理方式
  * 不同处：
      * 进程ID，frok返回值，进程运行时间，定时器，未决信号集   
      * 父子进程之间遵循读时共享，写时复制的原则。
* exec函数族
  *  fork创建子进程之后执行的是和父进程相同的程序(但可能执行不同的代码分支)，子进程往往要调用exec函数以执行另一种程序，当进程调用一种exec函数时，改进程的用户空间代码和数据完全被新程序替换，从新程序的启动例程开始执行，调用exec并不创建新进程，所以调用exec前后进程的id并未改变
  *  int execl(const char *path, const char *arg, ... /* (char  *) NULL */);
      * 执行程序的时候，使用PATH环境变量，执行的程序时候可以不加用路径  
  * int execlp(const char *file, const char *arg, ... /* (char  *) NULL */);
  * int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
  * int execv(const char *path, char *const argv[]);
  * int execvp(const char *file, char *const argv[]);
  * int execvpe(const char *file, char *const argv[], char *const envp[]);

   ！[exec的用法](https://github.com/tangchengjian-tcj/c-/blob/master/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/%E5%9B%BE%E7%89%87/exec.jpg)

* 孤儿进程：父亲死了，子进程被init进程领养,负责回收进程
* 僵尸进程：子进程死了，父进程没有回收子进程的资源
* 子进程回收
   * wait和waitpid一次只能清理一个子进程,清理多个子进程应使用循环 
   * 作用:
      1.阻塞等待
      2.回收子进程资源
      3.查看死亡原因
   * wait函数:pid_t wait(int *wstatus);
      * wstatus:传输函数
      * pid_t:成功:返回清理掉的子进程id,失败:返回-1   
   * waitpid函数:pid_t waitpid(pid_t pid, int *wstatus, int options);
      * 成功:返回清理调的子进程id  失败:-1(无子进程) 
      * pid:
         1.>0回收指定id的子进程
         2.-1 回收任意子进程,相当于wait
         3.回收和当前调用waitpid一个组的所有子进程
         4.<-1 回收指定进程组内的任意子进程
      * options 0:和wait相同,也会阻塞  WNOHANG:如果当前没有子进程,会立刻返回
      * 返回值:如果设置了WNOHANG,且子进程正在运行中会返回0
## 进程之间的通信
* ipc方法
   
   简介:linux环境下,进程地址空间相互独立,每个进程各自都有不同的用户地址空间,任何一个进程的全局变量在另一个进程中都看不见,所以进程和进程之间不能相互访问,要交换数据必须通过内核,在内核中开辟一块缓冲区,进程1把数据从用户空间拷到内核缓冲区,进程2再次从内核缓冲区把数据读走,内核提供的这种机制称为进程间通信(ipc)
   
   * 通信方式:单工(广播),半双工(对讲机),全双工(打电话)
   * ipc通信方式
      * pipe 管道--最简单
      * fifo 有名管道
      * mmap 文件映射共享io  速度最快
      * 本地socket 最稳定
      * 信号  携带信息量最小
      * 共享内存
      * 消息队列
* 管道
   * 半双工通信 
   * 管道函数:int pipe(int pipefd[2]);
      * pipefd读写文件描述符:0代表读,1代表写
   * 读管道:
      * 写端全部关闭---read读到0,相当于读到文件末尾
      * 写端没有全部关闭--read阻塞,fcntl函数可以更改非阻塞
   * 写管道
      * 读端全部关闭---程序异常终止
      * 读端没有全部关闭 ---管道满了  write阻塞     ---管道每满   write正常写入    
      * 返回值:失败返回-1,成功返回0
