内容:用银行家算法避免死锁,实现系统合理分配资源,加深对进程同步及死锁理
解。

要求:
1. 假定系统有 3 类资源 A(10 个)、B(15 个)、C(12 个),系有 5 个进程并发执行,
进程调度采用时间片轮转调度算法。
2. 每个进程由一个进程控制块( PCB)表示,进程控制块可以包含如下信息:进程
名、需要的资源总数、已分配的资源数、进程状态。
3. 由程序自动生成进程(包括需要的数据,要注意数据的合理范围)
。
4. 进程在运行过程中会随机申请资源(随机生成请求的资源数)
,如果达到最大需求,
表示该进程可以完成;如果没有达到最大需求,则运行一个时间片后,调度其它进
程运行。资源分配采用银行家算法来避免死锁。
5. 每个进程的状态可以是就绪 W(Wait)、运行 R(Run)
、阻塞 B(Block)或完成 F
(Finish)状态之一。
6. 每进行一次调度,程序都要输出一次运行结果:正在运行的进程、就绪队列中的进
程、阻塞队列中的进程、完成的进程以及各个进程的 PCB,以便进行检查。
