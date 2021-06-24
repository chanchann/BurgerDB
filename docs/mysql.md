## MySql基础

## 关系型数据库

Mysql，sqlite

sqlit是进程内的db

## 分布式db

ceph

## NoSql ： key - value

redis leveldb mongodb rocksdb

## 大数据分析 列式存储

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



