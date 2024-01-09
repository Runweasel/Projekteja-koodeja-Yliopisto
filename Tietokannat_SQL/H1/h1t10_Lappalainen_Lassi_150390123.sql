-- h1t10
-- Lappalainen Lassi 150390123

CREATE TABLE shoe (
    id INT NOT NULL,
    name VARCHAR(50) NOT NULL,
    type VARCHAR(50),
    price DECIMAL(8, 2),
    PRIMARY KEY (id),
    UNIQUE (name)
);

INSERT INTO shoe (id, name, type, price) VALUES (1, 'X 10', 'sprint', 79.95);
INSERT INTO shoe (id, name, type, price) VALUES (4, 'ABC 101', 'sprint', 124.95);
INSERT INTO shoe (id, name, type, price) VALUES (6, 'ABC 201', 'long jump', 159.00);
INSERT INTO shoe (id, name, type, price) VALUES (7, 'X 20', 'middle-distance', NULL);