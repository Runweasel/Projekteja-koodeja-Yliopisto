-- h2t10
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

CREATE TABLE teekaupat (
    tunnus INT PRIMARY KEY,
    nimi VARCHAR(50) UNIQUE,
    osoite VARCHAR(100)
);

INSERT INTO teekaupat (tunnus, nimi, osoite)
VALUES (1, 'Tee mestari', 'Hervanta 1');

INSERT INTO teekaupat (tunnus, nimi, osoite)
VALUES (2, 'Kuppila', 'Hakametsa 2');

INSERT INTO teekaupat (tunnus, nimi, osoite)
VALUES (3, 'Tee paratiisi', 'Keskusta 3');

CREATE TABLE sells (
    tea_id INT,
    teekauppa_id INT,
    FOREIGN KEY (tea_id) REFERENCES tea (id),
    FOREIGN KEY (teekauppa_id) REFERENCES teekaupat (tunnus)
);

INSERT INTO sells (tea_id, teekauppa_id)
VALUES (1, 1);

INSERT INTO sells (tea_id, teekauppa_id)
VALUES (2, 1);

INSERT INTO sells (tea_id, teekauppa_id)
VALUES (3, 2);

INSERT INTO sells (tea_id, teekauppa_id)
VALUES (3, 3);