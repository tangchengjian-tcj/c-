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
* FIFO
  * 简介：被称为命名管道，管道（pipe）只能用于“有血缘关系”的进程间，但是FIFO可以实现无血缘关系间进程通信
  * 创建方式（创建一个管道的伪文件）
      * 创建命令：mkfifo 管道名
      * 也可以用函数创建： int mkfifo(const char* pathname,mode_t mode):成功：0，失败：-1
  * 内核会针对fifo文件开辟一个缓冲区，操作fifo文件，可以操作缓冲区，实现进程间通信，实际上就是文件的读写
* mmap映射
   * 存储映射I/O 使一个磁盘文件与存储空间中的一个缓冲区相映射。于是当从缓冲区中取数据，就相当于读文件中的相应字节，
   * 于此类推，将数据存入缓冲区，则相应的字节就自动写入文件。就可以在不适用read和write函数的情况下，使用地址（指针）完成i/o操作 
   * 函数    void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
      * 返回：成功  返回创建的映射区首地址，  失败：MAP_FAILED 宏
      * addr：建立映射区的首地址，由linux内核指定，使用时，直接传递NULL
      * length：欲创建的映射区大小
      * prot：映射区权限
      * flags：标志位参数（常用于设定更新物理区域，设置共享，创建匿名透射区）
         * MAP_AHSRED:会将映射区所做的操作反映到物理设备上
         * MAP_PRIVTE：映射区所作的修改不会反映到物理设备上
      * fd:用来建立映射区的文件描述符
      * offset：映射文件的偏移（4k的整数倍） 
   *  int munmap(void *addr, size_t length);释放映射空间：成功10，失败-1
## 信号
   * 信号的特点：简单，不能携带大量信息
   * 信号的机制：每个进程收到的所有信号，都是内核负责发送的
   * 递达：递送并且达到进程
   * 未决：产生和递达之间的状态，主要是由于阻塞（屏蔽）导致该状态
   * 信号处理方式：
      * 执行默认动作
      * 忽略（丢弃）
      * 捕获（调用用户处理函数） 
   * 信号四要素：
      * 编号
      * 事件
      * 名称
      * 默认处理动作   (man 7 signal:命令查看)
   * 阻塞信号集和未决信号集：
      * 阻塞信号集：将某些信号加入集合，对他们设置屏蔽，当屏蔽x信号后，该信号的处理将推后（解除屏蔽后）
      * 未决信号集：
         * 1。信号产生，未决信号集中描述该信号的位立刻翻转为1，表信号处于未决状态，当信号被处理对应位翻转为0,这一时刻往往非常短暂
         * 2，信号产生后，由于某些原因（主要是阻塞）不能抵达，这类信号的集合称为未决信号集，屏蔽解除前，信号一直处于未决状态  
   * 函数
      *  int kill(pid_t pid, int sig); 成功：0  失败：-1
         * pid>0：指定进程
         * pid=0：发送信号给与调用kill函数进程属于同一进程组的所有进程
         * pid<0：取 |pid|发给对应进程组
         * pid=-1：发送给进程有权限发送的系统中的所有进程
         * sig对应的信号，应该使用宏名
      * raise：给自己发送信号
      * int raise(int sig);
      * abort();直接杀掉自己
      * 时钟信号:unsigned int alarm(unsigned int seconds);
         * 返回值：返回0或者剩余的秒数，无失败 
         * 传入秒数，时间到后，会给当前进程发送14（SIGALRM）信号
      * int setitimer(int which, const struct itimerval *new_value,struct itimerval *old_value);
      * 参数：
         * which :指定定时方式
         * 1。自然定时：ITIMER_REAL  ----> 14（SIGLARM）  计算自然时间
         * 2。虚拟空间计时（用户空间）ITIMER_VIRTUAL----》26（SIGVTALRM）计算进程占用cpu时间
         * 3。运行时计时（用户+内核）ITIMER_PROF----》27（SIGPROF）计算占用cpu及执行系统调用的时间   
   
               
               new_value:要设置的闹钟时间
               old_value:传出的是上一个时钟的时间
                struct itimerval {
                     struct timeval it_interval; /* Interval for periodic timer */  周期性的时间设置
                     struct timeval it_value;    /* Time until next expiration */ 下次的闹钟时间
                 };

                 struct timeval {
                     time_t      tv_sec;         /* seconds */  秒
                     suseconds_t tv_usec;        /* microseconds */  微秒
                 };
        
   * 信号操作函数
      * 内核通过读取未决信号集来判断信号是否应被处理，信号屏蔽字mask可以影响未决信号集，而我们可以在应用程序中自定义set来改变mask，以达到屏蔽指定信号的目的
      * 信号集设定：
         
               int sigemptyset(sigset_t *set); 将某个信号集清0
               int sigfillset(sigset_t *set);将某个信号集置1
               int sigaddset(sigset_t *set, int signum);将某个信号集加入信号集
               int sigdelset(sigset_t *set, int signum);将某个信号清出信号集
               int sigismember(const sigset_t *set, int signum);判断某个信号是否在信号集
               int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);:设置阻塞或者解除阻塞信号集
                     参数：how：SIG_BLOCK：设置阻塞   SIG_UNBLOCK：解除阻塞   SIG_SETMASK：设置set为新的阻塞信号集
                           set：传入的信号集
                           oldset：旧的信号集，传出
               int sigpending(sigset_t *set);:获取未决信号集，，set，传出参数当前的未决信号集
   * 信号捕捉
      * typedef void (*sighandler_t)(int);       sighandler_t signal(int signum, sighandler_t handler);
          * signum:要捕捉的信号    handler：要执行的捕捉函数指针，函数应该要声明 void func(int) 
       * int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
         * signum:要捕捉的信号           act:要执行的程序       oldact:原动作
         
                 struct sigaction {
                     void     (*sa_handler)(int);//函数指针
                     void     (*sa_sigaction)(int, siginfo_t *, void *);//
                     sigset_t   sa_mask; // 执行捕捉函数的期间，临时屏蔽的信号集
                     int        sa_flags;//一般填0    0代表要执行第一个函数，，  sA_SIGNFO的执行第二个
                     void     (*sa_restorer)(void);//无效
                 };
  * 信号捕捉特性：
      * 1。进程正常运行的时候，默认PCB中有一个信号屏蔽字，当注册到某个信号捕捉函数时，捕捉到该信号时，调用该函数，这期间所屏蔽的信号由sa_mask指定，调用完函数后，再恢复默认屏蔽函数
      * 2。xxx信号捕捉函数执行期间，xxx信号自动被屏蔽
      * 3，阻塞的常规信号不支持排队，产生多次只记录一次   
       
  * SIGCHLD信号 
      * 产生条件
         * 子进程终止时
         * 子进程接收到SIGSTOP信号停止时
         * 子进程处于停止态，接受到SIGCONT后唤醒  
      

## 守护进程
   * 进程组：多个进程组对应一个会话
   * 创建会话：
      * 1。调用进程不能是进程组组长，该进程变成新绘画首进程
      * 2。该进程成为一个新进程组的组长进程
      * 3。需要root权限
      * 4。新会话丢弃原有的控制终端，该会话没有控制终端
      * 5。该调用进程是组长进程，则出错返回
      * 6。建立会话时，先调用fork，父进程终止，子进程调用setsid
   * pid_t setsid(void);(创建一个会话，并以自己的id设置进程组id，同时也是新会话的id)
   * 守护进程：就是liux中的后台服务进程，通称独立于控制终端并且周期性的执行某种任务或者等待处理某些发生的事件
      * 创建守护进程，最关键的一步就是调用setsid函数创建一个新的session，并成为session leader
      * 创建守护进程模型
         * 1。创建子进程，父进程退出  
         * 2。在子进程中创建新的会话  setsid()函数   使子进程完全独立出来
         * 3。改变当前目录为根目录 chdir（）函数  
         * 4。重设文件权限掩码   umask()  防止继承的文件创建屏蔽字拒绝某些权限
         * 5。关闭文件描述符 
         * 6。开始执行守护进程核心工作
         * 7。守护进程退出处理程序模型 
   * 守护进程拓展
      * 通过nohup指令也可以达到守护进程创建的效果
      * nohup cmd &
         * nohup指令会让cmd收不到SIGHUP信号
         * & 代表后台运行   
        
* 线程
   * 简介 
      *   线程是最小的执行单位   进程是最小的系统资源分配单位
      *   内核都是通过clone实现的
      *   ps -lf pid：查看指定线程的lwp号
   *   线程共享资源
      * 文件描述符
      * 各种信号的处理方式
      * 当前工作目录
      * 用户id和组id
      * 内存地址空间
   * 线程非共享资源
      * 线程id
      * 处理器现场和栈指针（内核栈）
      * 独立的栈空间
      * errno变量   
      * 信号屏蔽字
      * 调度优先级    
   * 创建一个线程
      * #include <pthread.h> 
      *  int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
      *  参数：
         * thread：线程id  传出参数
         * attr ：代表线程的属性
         * 第三个参数 函数指针  viod *func(void *)
         * arg:线程执行函数的参数
         * 返回值 成功返回0    失败返回errno
      * *编译的时候需要添加phtread库*
         * *gcc create_thread.c -lpthread* 
* 线程同步
* 锁（互斥量）
* 
