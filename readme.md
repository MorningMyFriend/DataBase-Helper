# 数据库助手

## 1. 文件结构

- class: MySqlHelper

  实现数据库API一些基本操作的包装：链接数据库`Connect()`，执行SQL命令`ExeSQL()`，查询，更新等

- class: VsDatabaseHelper

  根据structure.h提供的三个子类结构，创建表`CreateTable()`

  根据三个类的实例对象插入数据库条目`Insert`

- 依赖库：

  ```
  // apt-get install mysql-server
  // apt-get install mysql-client
  // apt-get install libmysqlclient-dev
  // apt-get install libmysqlcppconn-dev
  ```



## 2. 测试

在终端查看插入是否成功，可能用到的命令：

```
 connect$: mysql -u root -p
// create database$: CREATE DATABASE dbname;
// show database$: show databases;
// enter database$: use dbname
// create table$: CREATE TABLE IF NOT EXISTS runoob_tbl (runoob_id INT UNSIGNED AUTO_INCREMENT,runoob_title VARCHAR(100) NOT NULL,count INT,PRIMARY KEY (runoob_id))ENGINE=InnoDB DEFAULT CHARSET=utf8;
// show tables $: show tables; 
// show table structrue$: desc tabel_name;
// show item in table$: select * from table_name;
```

# redis 使用

## 1. dependent libs
- sudo apt-get install hiredis-dev

## 1. ssh 链接服务器
- 在同一个路由器下： ssh root@116.62.174.64
- 密码： Cz2cpu789

## 2. redis 登录
- redis-cli -h 116.62.174.64 -p 6379 -a redisPSW0328
- 获取权限： AUTH redisPSW0328
- 查看任务数量： llen ocr_2001_list
- 查看任务字段值： lpop ocr_2001_list

# pqsql

## 1. dependent libs
- sudo apt-get install libpqxx-dev
- sudo apt-get install libpq-dev



