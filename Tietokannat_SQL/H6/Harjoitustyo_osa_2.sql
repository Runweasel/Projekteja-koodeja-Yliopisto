-- Harjoitustyö Tablet
-- Lappalainen Lassi 150390123

-- .open harkka.db

PRAGMA foreign_keys = ON;

--Create tuotemerkki table
CREATE TABLE tuotemerkki (
    tmtunnus INT PRIMARY KEY,
    tmnimi VARCHAR(255),
    maa VARCHAR(50)
);

--Create tuote table
CREATE TABLE tuote (
    ttunnus INT PRIMARY KEY,
    tnimi VARCHAR(100),
    kuvaus VARCHAR(255),
    hinta DECIMAL(10, 2),
    tmtunnus INT,
    FOREIGN KEY (tmtunnus) REFERENCES tuotemerkki(tmtunnus)
);

--Create arviointi table
CREATE TABLE arviointi (
    katunnus INT,
    ttunnus INT,
    paivamaara DATE,
    arvosana INT,
    arvio TEXT,
    PRIMARY KEY (katunnus, ttunnus, paivamaara),
    FOREIGN KEY (katunnus) REFERENCES kayttaja(katunnus),
    FOREIGN KEY (ttunnus) REFERENCES tuote(ttunnus)
);

--Create kayttaja displayed at exhibition
CREATE TABLE kayttaja (
    katunnus INT PRIMARY KEY,
    kanimi VARCHAR(100),
    syntymavuosi DATE
);

--Create sijoittuu displayed at exhibition
CREATE TABLE sijoittuu (
    ttunnus INT,
    ktunnus INT,
    PRIMARY KEY (ttunnus, ktunnus),
    FOREIGN KEY (ttunnus) REFERENCES tuote(ttunnus),
    FOREIGN KEY (ktunnus) REFERENCES kategoria(ktunnus)
);

--Create kategoria displayed at exhibition
CREATE TABLE kategoria (
    ktunnus INT PRIMARY KEY,
    knimi VARCHAR(100)
);

--------------

INSERT INTO kayttaja (katunnus, kanimi, syntymavuosi) VALUES
(1, 'Anni N', '1985-01-01'),
(2, 'Juuso K', '1990-01-01'),
(3, 'Eino U', '1940-01-01'),
(4, 'Aila J', '1953-01-01');

INSERT INTO kategoria (ktunnus, knimi) VALUES
(1, 'puutarha'),
(2, 'metsä'),
(3, 'lumityöt');

INSERT INTO tuotemerkki (tmtunnus, tmnimi, maa) VALUES
(1, 'McCee', 'Yhdysvallat'),
(2, 'KooTek', 'Suomi');

INSERT INTO tuote (ttunnus, tnimi, kuvaus, hinta, tmtunnus) VALUES
(1, 'Trimmeri TRCee', 'tehokas 4-tahtinen', 179.00, 1),
(2, 'Trimmerisiima Cee', 'laadukas siima', 6.99, 1),
(3, 'Moottorisaha MSCee RR', 'robusti ja raskas', 559.00, 1),
(4, 'Trimmerisiima Y', 'yleissiima', 3.99, 2),
(5, 'Lapio L', 'kevyt yleislapio', 23.95, 2);

INSERT INTO sijoittuu (ttunnus, ktunnus) VALUES
(1, 1),
(2, 1),
(3, 1),
(3, 2),
(4, 1),
(5, 1),
(5, 3);

INSERT INTO arviointi (katunnus, ttunnus, paivamaara, arvosana, arvio) VALUES
(1, 1, '2021-06-05', 3, NULL),
(1, 2, '2021-06-13', 2, NULL),
(1, 5, '2021-07-24', 3, NULL),
(1, 4, '2021-08-13', 4, 'luotettava ja toimiva kapistus'),
(1, 1, '2021-09-12', 5, 'luotettava ja toimiva kapistus'),
(3, 1, '2021-06-30', 5, 'loistava'),
(3, 2, '2021-07-02', 2, 'kohtalaisesti toimii'),
(2, 5, '2021-06-04', 1, 'rahastusta'),
(4, 5, '2021-08-11', 1, 'ei tee mitään');