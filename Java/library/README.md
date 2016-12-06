# GDUT Digital Library System

## Framework:

- MariaDB (MySQL)
- SWT

## MariaDB/MySQL

```sql
CREATE USER 'dgeibi'@'localhost' IDENTIFIED BY '123456';
CREATE DATABASE keshe CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
GRANT ALL ON keshe.* TO 'dgeibi'@'localhost';
FLUSH PRIVILEGES;

use keshe;

CREATE TABLE admin                  -- 管理员
(
    id INT(10) unsigned NOT NULL,   -- 账号
    password VARCHAR(120) NOT NULL, -- 密码
    registerTime DATETIME NOT NULL, -- 注册时间
    username VARCHAR(120),          -- 用户名
    PRIMARY KEY (id)                -- 账号不可重复
);

CREATE TABLE customer               -- 消费者
(
    id INT(10) unsigned NOT NULL,   -- 账号
    password VARCHAR(120) NOT NULL, -- 密码
    registerTime DATETIME NOT NULL, -- 注册时间
    username VARCHAR(120),          -- 用户名
    PRIMARY KEY (id)                -- 账号不可重复
);

CREATE TABLE book                               -- 书
(
    id int NOT NULL AUTO_INCREMENT PRIMARY KEY, -- 编号，自动递增
    name   VARCHAR(50) NOT NULL,                -- 书名，不为NULL
    author VARCHAR(50),
    publishTime DATETIME                        -- 添加的时间
);

CREATE TABLE history                            -- 业务历史记录
(
    id int NOT NULL AUTO_INCREMENT PRIMARY KEY, -- 编号，自动递增
    bookID INT(10) unsigned NOT NULL,           -- 图书编号
    customerID INT(10) unsigned NOT NULL,       -- 消费者编号
    businessTime DATETIME,                      -- 借书时间
    returnTime DATETIME                         -- 归还时间(如果为空表示未归还)
);

-- 图书数据
INSERT INTO book (name,author, publishTime) VALUES ('黑客与画家', 'Paul',NOW());
INSERT INTO book (name, author, publishTime) VALUES ('Head First Java','Sierra & Bates', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('The Little Prince','‎Antoine de Saint-Exupéry', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('JavaScript 高级程序设计','Nicholas C.Zakas', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('SICP','Harold Abelson...', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('Compilers: Principles','Alfred V. Aho...', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('技巧','郝培强', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('ECMAScript','阮一峰', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('苏菲的世界','乔斯坦·贾德', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('算法导论','Thomas H.Cormen...', NOW());
```

## Thanks:

[SWT Snippets](http://www.eclipse.org/swt/snippets/)
