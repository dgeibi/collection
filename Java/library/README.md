# GDUT Digital Library System

## Framework:

- MariaDB (MySQL)
- SWT

## MariaDB

```sql
CREATE TABLE admin
(
    id INT(10) unsigned NOT NULL,
    password VARCHAR(120) NOT NULL,
    registerTime DATETIME NOT NULL,
    username VARCHAR(120),
    PRIMARY KEY (id)
);

CREATE TABLE user
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

CREATE TABLE business
(
    id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    bookid INT(10) unsigned NOT NULL,
    userid INT(10) unsigned NOT NULL,
    businessTime DATETIME
);
```

```sql
INSERT INTO book (name,author, publishTime) VALUES ('黑客与画家', 'Paul',NOW());
INSERT INTO book (name, author, publishTime) VALUES ('Head First Java','Sierra & Bates', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('The Little Prince','‎Antoine de Saint-Exupéry', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('JavaScript 高级程序设计','Nicholas C.Zakas', NOW());
INSERT INTO book (name, author, publishTime) VALUES ('SICP','Harold Abelson...', NOW());
```

## Thanks:

[SWT Snippets](http://www.eclipse.org/swt/snippets/)