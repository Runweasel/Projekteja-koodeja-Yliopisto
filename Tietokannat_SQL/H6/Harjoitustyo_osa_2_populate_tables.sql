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

