# GDUT Digital Library System

## Framework:

- MariaDB (MySQL)
- SWT

## MariaDB

```sql
create database keshe;

CREATE USER 'dgeibi'@'localhost' IDENTIFIED BY '123456';
GRANT ALL ON keshe.* TO 'dgeibi'@'localhost';
FLUSH PRIVILEGES;

use keshe;

CREATE TABLE admin
(
    id INT(10) unsigned NOT NULL,
    password VARCHAR(120) NOT NULL,
    registerTime DATETIME NOT NULL,
    username VARCHAR(120),
    PRIMARY KEY (id)
);

CREATE TABLE customer
(
    id INT(10) unsigned NOT NULL,
    password VARCHAR(120) NOT NULL,
    registerTime DATETIME NOT NULL,
    username VARCHAR(120),
    PRIMARY KEY (id)
);

CREATE TABLE book
(
    id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name   VARCHAR(50) NOT NULL,
    author VARCHAR(50),
    publishTime DATETIME
);

CREATE TABLE history
(
    id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    bookID INT(10) unsigned NOT NULL,
    customerID INT(10) unsigned NOT NULL,
    businessTime DATETIME,
    returnTime DATETIME
);

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
