### TODO

1. ~~去掉最外层大括号的限制~~

2. 实现函数闭包

### 需要提前安装的软件

1. Java 环境安装

   1. window下java环境配置过程略
   2. Ubuntu下java环境配置
      1. 直接使用PPA/源方式安装更方便
         1. 添加PPA
            - ```shell
              sudo add-apt-repository ppa:webupd8team/java
              sudo apt-get update
              ```
         2. 安装**oracle-java-installer**
            - ```shell
              sudo apt-get install oracle-java8-installer
              ```
         3. 关于服务条款直接ok，然后选择yes即可。然后等待安装结束
         4. 如果你因为防火墙或者其他原因,导致installer 下载速度很慢,可以中断操作.然后下载好相应jdk的tar.gz 包,放在:`/var/cache/oracle-jdk8-installer (jdk8)`下面,然后安装一次installer. installer 则会默认使用 你下载的tar.gz包
         5. 设置系统默认jdk
            - `sudo update-java-alternatives -s java-8-oracle`
         6. 如果系统中既有java7又有java8，可以利用下面命令切换
            - 切换至java7:`sudo update-java-alternatives -s java-7-oracle`
            - 切换至java8:`sudo update-java-alternatives -s java-8-oracle`
         7. 测试jdk是否安装成功
            - `java -version`

2. Antlr 安装方式
   1. 编译安装 C library 
      - ```shell
        wget http://www.antlr3.org/download/C/libantlr3c-3.4.tar.gz
        tar -xzvf ./libantlr3c-3.4.tar.gz
        ./configure --enable-64bit
        make
        sudo make install
        ```
   2. 下载 Antlr 3.4 jar包
         -  尽管我们安装了c library，但是从.g文件，到各种.h .c文件的过程，还是要依赖antlr java的。特别注意：必须要用3.4的jar包，我试了3.5.1，果断不行……
         -  ```shell
            wget http://www.antlr3.org/download/antlr-3.4-complete.jar
            ```

   ​
**构建程序（目前在Hython主文件夹下）**

  1. 在 ./thirdpart/libs 中编译安装 C library 
  2. 执行 make 命令
  3. 在 ./bin 下执行可执行文件 hy_run 来解析代码文件


======================

### 功能说明：

1. 增加 **代码块** `block` 的定义和变量作用域的实现
2. 增加 `if/ else` `for/ while/ do while` 程序流程控制方法
3. 调整程序架构，增加 `责任链模式` `抽象工厂模式` `单例模式` 等面向对象程序设计技巧
4. 完善 **条件表达式** `condition_expr` 的功能
5. 添加单独的 `Parameters` 类，管理变量作用域
6. 添加 `ProgramMaster` `IFMaster` `ExprMaster` `PrintMaster` 类，用来处理 **AST** 中不同的树型逻辑
7. 增加类型系统，支持三种类型：**Int、Float、String**
8. 增加 **DFA** 程序流程结构，完美支持 **break** 以及 **continue**
9. 增加 `switch/ case` 程序流程控制方法


