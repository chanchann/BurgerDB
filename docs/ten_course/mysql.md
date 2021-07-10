## MySql基础补充笔记

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

## 关系型数据库范式

### 好处

### 各种范式及例子 todo

## 库操作

## 表操作

创建表 : primary key / unique  / not null / auto increment / default

## CRUD 操作

### insert

此处主要，auto_increment id 一直增长而不会找开头空闲的id

假如 id 越界，改int 为 bigint，改大范围  或者 重置表

```sql
insert into user(nickname, name, age, sex) values('HW tiancai', 'mitsk', 22,
'M');
insert into user(nickname, name, age, sex) values('BD tiancai', 'lighao', 24,
'M');


insert into user(nickname, name, age, sex) values('HW tiancai', 'mitsk', 22,
'M'),('BD tiancai', 'lighao', 24,'M');

// 两种哪种效率高
// 下面这种，只用发送一次请求连接
// --> 数据库连接池项目
```

mysql client <-----> mysql server

1. tcp三次握手

2. client发送sql到server接收并处理，返回处理结果 

3. 交互完成，四次挥手

### update / delete

### select 

业务上开发尽量少写 * ，尽量写明要选择的列

回表是什么?

注意:

between 是 [] 包含

不是 = null; 而是 is (not) null;

- 去重 distinct

- 空值查询

- union 合并查询  -- 注意不是联合

- 带in 子查询

- 分页查询limit

limit是否提升了我们查询的效率？

可以，满足了limit就停止

所以善于利用limit去提升性能 (前提是没有索引)

利用**explain** 查看SQL语句的执行计划

看rows，扫了多少行

注意 : 而limit的mysql优化，explain显示不出来，所以这的rows是有问题的(只是大略)

拓展阅读 : 索引优化

https://zhuanlan.zhihu.com/p/61687047

- 再探 limit 提升例子

```sql
pagenum = 20 每页显示20个

select * from user limit (pageno - 1) * pagenum, pagenum;
// 效率低，低在offset 这里(pageno - 1) * pagenum 前面全部都要遍历一下
// 比如 limit 10000, 20; 前面10000行都要经过查询
// 改进 : 用id(索引)作为一个参照
// 
select * from user where id > 上一页最后一条数据的id值 limit 20;
```
### order by


```sql
explain select * from user order by name;
// extra : Using filesort
// 当内存装不下排序的数据，会用一些外排序方法，比如filesort(有磁盘IO，效率低，要考虑优化)

explain select name from user by name;
// 优化了 : extra : Using Index
```

## group by

分组 -- 一般结合统计操作

```sql
select age, count(age) from user group by age;

select age, sum(age) from user group by age having age > 20;  // 注意这里having而不是where

// or
select age, sum(age) from user where age > 20 group by age;

// 也可用多个字段group by

count(*) 会优化，用主键，相当于求行数
```

关于group by优化

如果不是索引的话，也是 Using filesort, 要排序， Using temporary 建立临时表

## 笔试实践题

```sql
select count(serno), sum(amount) from bank_bill;

select brno, date, sum(amount) as money from bank_bill group by brno, date order by brno, money desc;
```

## 连接查询

一次查询多张表，增加效率

### 内连接查询

查询两张表之间的交集 inner join

### 外连接查询

left/right [outer] join

不区分大小表，哪边连接就算全表扫描

1. left连接查询

左表特有的数据

把left的表所有的数据显示出来，在右表中不存在相应数据 则显示NULL

查找没有可以用外连接

```sql
// 查找没有考试的人
select * from student where uid not in (select distinct uid from exam);

// left join 写法 -- 利用null
select a.* from student a left join exam b on a.uid=b.uid where b.cid is null;
```

2. right连接查询

右表特有的数据

### 场景1 

```sql
student:
uid name age sex

course:
cid cname credit

exam:
uid cid time score
```

```sql
create table student(
uid int unsigned primary key not null auto_increment,
name varchar(50) not null,
age tinyint unsigned not null,
sex ENUM('M', 'W') not null
);

create table course(
cid int unsigned primary key not null auto_increment,
cname varchar(50) not null,
credit tinyint unsigned not null
);

create table exam(
uid int unsigned not null,
cid int unsigned not null,
time date not null,
score float not null
-- 联合主键
primary key(uid, cid) 
);
```

```sql
// 查看ligh某一门课的成绩
// 预置条件 uid : 1 cid : 2
select score from exam where uid = 1 and cid = 2; 

// 先写两张表的查询， 命名表
select a.uid, a.name, a.age, a.sex from student a where a.uid = 1;

select c.scrore from exam c where c.uid = 1 and c.cid = 2;

// 合并后
// inner join 是join的默认
// on a.uid = c.uid 通过uid连接，区分大表和小表，按照数据量区分大小
// 小表永远是整表扫描(所以给小表建索引没用), 然后去大表搜索
// 从student小表中取出所有的a.uid, 然后拿着这些uid去exam大表中搜索
select a.uid, a.name, a.age, a.sex, c.score from student from student a inner join exam c on a.uid = c.uid where c.uid = 1 and c.cid = 2;
// 这里为什么不是a.uid = 1?  因为小表是整表扫描
```

// 其他例子见pdf

### limit 和 inner join 的优化

```sql
select * from user limit 1500000, 10;

// 相对于选取所有列，效率提升
select id from user limit 1500000, 10;

// 如果就要选择很多列，如何提升?
// 1. 通过添加索引字段快速过滤
select * from user where id > xx limit 10;

// 2. 生成临时表
select a.id, a.email, a.password from user a inner join (select id from user limit 1500000, 10) b on a.id = b.id;
```

notes:

- 对于如何查询多表过程，通过explain去查看过程

- 看谁先查，谁后查，谁是全表扫描，谁用到了索引

- 如果有where，先去过滤，这样可能导致大小表关系的逆转

- 如果是联合主键，用到后面的字段是不会产生索引优化的

- not in 有个天然不好的地方在于，对于索引的命中比较低

一些地方说not in 用不到索引 -- 不准确

```sql
select * from student where uid not in (select distinct uid from exam);

select distinct uid from exam 会产生一张中间表存储结果供外面的sql来查询
```

- 对于inner join内连接，过滤条件写在where的后面和on连接条件里面效果是一样的。

- 对比outer join 则效果不一样

对于左连接，肯定要先去扫左表

所以一般来说，我们把限制条件放在on里，把null 条件放where中

## Mysql 存储引擎

```sql
create table xx {
表的结构
数据
索引
}

存储引擎直接影响上面内容的存储方式
```

```sql
show engines; // 查看

mysql创建的表在 /var/lib/mysql中
```

## 各存储引擎区别

MyISAM 将数据和索引分别存放成.MYD, MYI

InnoDB 将数据和索引一起存放到 .ibd

MyISAM 表锁，粒度太大

InnoDB 行锁，粒度小

等等

## Mysql 索引

核心 : 提升查询速度

索引就是一个数据结构

但是索引存储成索引文件，涉及磁盘IO，所以索引也不是越多越好

## 索引分类

### 物理上 

1. 聚集索引

2. 非聚集索引

见后

### 逻辑上

1. 普通索引(二级索引)

2. 唯一性索引

3. 主键索引

MyISAM 引擎中，没有添加主键，不会自动添加。因为索引和数据是分开存放的，有就有，没有就没有。

而InnoDB会自动增加一个整形最为主键，因为数据和索引存在一个文件，必须建一个索引树，在索引树上存数据。

4. 单列索引

5. 多列索引

多列索引必须使用到第一个列才用到多列索引，否则索引用不上

uid + cid

uid 可

uid+ cid 可

cid 不可

6. 全文索引

针对字符串搜索

用的比较少，真实项目支持专门的搜索功能。

会给后台服务器增加专门的搜索引擎支持高效的搜索 elasticsearch (es) c++ sougou workflow

## 索引创建和删除

一定要善于运用exaplain 查看是否运用对了索引

- 如果增加了索引，用where做过滤，不一定能够用到此索引，mysql会做优化

- 对于字符串，建议去定义length，通过前面这么多length就可区分，没必要全部字符串去建索引

CREATE [UNIQUE] INDEX 索引名 ON 表名 （属性名 （length）  [ASC | DESC]);

- 对于where过滤条件，如果索引涉及到类型强转 or mysql函数，就无法利用索引

## 通过explain查看索引的执行过程

## 索引的实现原理

### B树

B 是 balance , 所有的叶子结点都在同一层

数据，索引 放在 磁盘

MySQL server 数据 访问数据，先把数据，索引读到内存中(花费磁盘IO，按块读取，块一般16k, 是页面的整数倍)

对比 malloc / new 分配四个字节，并不是只申请4个字节，内存管理 按 页 为单位(一般4k)

向kernel申请，按页面分配，4k-4 这么多空闲的， 交给libc++.so 库的malloc 实现ptmalloc和tcmalloc来管理。(实现缓存) 提高效率

假设2000w的数据进行读取。 如果是平衡二叉树存储(一个结点，一个数据，两个指针)

log2000w 层高 : 25层

一次磁盘IO读取数据，放在一个结点上

最坏的情况下，读取一个索引，要花费25次磁盘IO

而b树是m阶的平衡树，m 取 300 - 500 最佳

如果m = 500 

一个结点有500个指针域，499个数据域

log_500 (2000w) = 2.7 最多3层，最多花费3次磁盘IO

- 流程

```sql
uid    name    age    sex
5      ligh    23     M
```

select * from student where uid = 5;

uid有索引 --> 存储引擎 --> kernel --> 磁盘IO(读索引文件) --> 读到内存上 --> 用索引的数据构建B树加速搜索

可看图，每一个紫色的都是key，是值, 比如这里的uid 5，黄色的data是那一行其他数据, 比如ligh, 23, M。

那么问题: data 存储的是数据本身内容，还是磁盘上的地址？

那就得看存储引擎了，如果是MyISAM, 索引和数据是分开的，构建的只是索引树，所以data指向的是磁盘上的地址

InnoDB, 同理，data就是存的数据本身(数据就是索引树上放的)

最终是通过二分搜索 logn, 好处就是非常少的磁盘IO

如果没有索引，就整表搜索，如果有索引，就通过索引树进行搜索

## B+树

问题 : 为什么MySQL(MyISAM 和 InnoDB) 索引底层选择B+树而不是B树呢?

1. 对比数据结构

索引+数据内容分散在不同的节点上，离root结点近，搜索就快，离根节点远，搜索就慢

花费的磁盘IO次数不平均，每一行数据搜索花费的时间也不平均

2. 每一个非叶子结点上，不仅仅要存储索引(key) 还要存储索引值所在哪一行的data数据

16k，全部存索引 vs 既存储索引又存储数据(这样能存放的key少了)

3. 这个树不方便做范围搜索，整表遍历(树结构没有 数组 or 链表 那么方便)

- 所以我们解决这三个问题，运用B+树

1. 每一个非叶子结点，只存放key, 不存储data，那么一个结点存放的key更多

B+树理论上来说，层数会更低一些，搜索效率会更好一点

因为如果B树一个结点存10个，B+树一个结点存20个，B+数这个节点命中概率会大一些

数据都存在叶子结点

非叶子结点的key值，最终会在叶子结点中再出现

2. 所以搜索每一个索引对应的data，都需要跑到叶子结点上，这样，每一行记录搜索的时间是非常平均的

3. 叶子结点被串成一个有序链表，因此做整表遍历和区间查找是非常容易的。

### todo : 总结索引的原理

## InnoDB的主键和二级索引树

```
mysql> select * from student;

uid name age sex
1   ligh 12  M
2   sk   13  M
3   fang 20  W

```

数据和索引存储在一块

student.frm 

student.ibd (数据和索引文件)

### 场景1 ：uid是主键


```sql
select * from student;  // 搜索的是整个索引树(叶子结点的有序链表)

select * from student where uid = 5; // 等值查询

select * from student where uid < 5;  // 范围查询 (直接在叶子结点的有序链表)

select * from student where name = 'fang'; // 整表扫描(直接在叶子结点的有序链表)
```

### 场景二 : uid是主键， name创建了普通索引(二级索引)

主键索引树 / 辅助索引树(二级索引树)

注意这里辅助索引树中，key是辅助索引的值，data是所在记录仪行的主键值

```sql
select name from student where name = 'fang';   // 1

select uid, name from student where name = 'fang';  // 2. 同1，因为他key对应的data是uid

select * from student where name = 'fang';  // 回表！！！
// 因为我key对应的data是uid，并没有存age,sex,name等信息
// 所以我们在拿uid **回表** 在 主键索引树上 搜索这个uid的 那一行的记录
// 所以无脑 * 可能导致回表，更多的查询和磁盘IO
```

```sql
select * from student where age = 20 order by name; 
// 如果只给age加索引，行不行？
// 不行，如果只有age 索引，会有filesort，因为还要靠name去排序
// filesort 一定要优化
// 我们此处要利用 多列索引 (联合索引) 先按age排序，再按name排序，age相同，再按name进行排序。
// 再次强调这里，先按age排序，再按name排序，所以如果我们只用name作为索引，没办法去匹配。

```

## 聚集和非聚集索引


## ref











