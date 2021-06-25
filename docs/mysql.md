## MySql基础

- 关系型数据库

Mysql，sqlite

sqlit是进程内的db

- 分布式db

ceph

- NoSql ： key - value

redis leveldb mongodb rocksdb

- 大数据分析 列式存储

Hbase

## mysql用select + 线程池

因为数据库涉及磁盘IO慢，需要匹配网络IO，没必要用那么快速的模型

## 一些概念

RDBMS : 关系型数据库管理系统

RDB : 关系型数据库

table : 二位表(行：记录 列: 字段/属性)

## 配置文件

```
// 数据文件
cd /var/lib/mysql
ls
cd mysql
ls

// 配置文件
/etc/mysql/my.cnf

```

## 设置支持ip远程连接

# 数值类型

```sql
// 完整性约束条件
create table user(age TINYINT unsinged not null default 0)

age INT(9)
// 这里的(9)是什么意思

整形占用的内存的大小是固定的，和具体的类型是强相关的，(M)只是代表证书显示的宽度

char(12)  存入"hello",还是12
varchar(12)  存入"hello",自适应长度

```

## mysql运算

double，float乘 越界不会报错，我们需要注意

## 约束

unique可以为空

notes : 

现在的后台开发中

外键，存储函数，存储过程，触发器基本不用了

让mysql做更多的核心逻辑，而不是做限制逻辑

应该在服务层/业务层(mysql client/mysql API) 去控制

## 关系型数据库表设计

### 一对一

User - Info 

```
// 被依赖 父表
User 
uid    uname    age    sex
1000   zhang    20     M
1020   liu      21     W
2010   wang     22     M

// 子表
Info
uid    cardId    addrinfo
1000    1122233   aaa
1020    3123123   bbb
2010    1231231   ccc

// 增加了个uid就将两张表关联了起来
// 子表的外键，关联了父表的主键
```

### 一对多 and 多对多

情景: 电商系统 User Product Order

User - Product 无关系

User - Order 一对多   --> 子表增加一列关联父表的主键

Product - Order 多对多  --> 增加一个中间表

```
User 
uid    uname    age    sex
1000   zhang    20     M
1020   liu      21     W
2010   wang     22     M

Product
pid    pname    price    amount
1      phone    600      100
2      computer 2000     50
3      battery  10       1000

Order 
orderid    uid    pid    number    money    totalprice    addrinfo
O1000      1000   1      1         600.0    4640.0        Mars
O1000      1000   2      2         4000.0   4640.0        Mars
O1000      1000   3      4         40.0     4640.0        Mars
O2000      2010   2      1         2000.0   2000.0        Earth
// 一对一和一对多处理一样
// 这里增加了uid这一列，关联上User表
// 冗余略多，Product 和 Order 之间 增加一个中间表OrderList来处理

// Order 优化后变成
orderid    uid     totalprice    addrinfo
O1000      1000    4640.0        Mars
O2000      2010    2000.0        Earth

OrderList
orderid    pid    number    money
O1000      1      1         600.0
O1000      2      2         4000.0
O1000      3      4         40.0
O2000      2      1         2000.0
// orderid 可重复， pid可重复
// orderid 和 pid这两个字段来共同创建一个联合的索引
```

设计的时候，一定要考虑约束条件，表与表之间的关系