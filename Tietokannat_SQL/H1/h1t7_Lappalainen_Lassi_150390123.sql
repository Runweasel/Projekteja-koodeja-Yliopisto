-- h1t7
-- Lappalainen Lassi 150390123

CREATE TABLE tea (
    id          INT,
    name        VARCHAR(50) NOT NULL,
    category    VARCHAR(30),
    price       DECIMAL(5,2),
    PRIMARY KEY (id),
    UNIQUE (name)
);


INSERT INTO tea
VALUES (1, 'Scottish Breakfast Premium', 'black', 6.50);  

INSERT INTO tea
VALUES (2, 'Lovely Lemon', 'black', 4.70);  

INSERT INTO tea
VALUES (3, 'Sources of Wisdom', 'green', 5.80);

INSERT INTO tea
VALUES (4, 'One True Love', 'green', 6.20);  

INSERT INTO tea
VALUES (5, 'Little Sour Face', 'white', 6.90);  

INSERT INTO tea
VALUES (6, 'Yellow Dragon', 'yellow', 6.20);

INSERT INTO tea
VALUES (7, 'Downhill', NULL, NULL);

INSERT INTO tea
 VALUES (8, 'Pale Flamingo', NULL, 6.75);