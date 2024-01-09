-- Harjoitustyö Kysely 4A
-- Lappalainen Lassi 150390123

SELECT 
    tuote.tnimi,
    MIN(arviointi.arvosana) AS min_arvosana,
    MAX(arviointi.arvosana) AS max_arvosana,
    AVG(arviointi.arvosana) AS ka_arvosana,
    COUNT(arviointi.arvosana) AS lkm_arvosana
FROM tuote 
LEFT JOIN arviointi ON tuote.ttunnus = arviointi.ttunnus
GROUP BY tuote.tnimi
ORDER BY tuote.tnimi ASC;