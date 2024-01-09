-- Harjoitustyö Kysely 5A
-- Lappalainen Lassi 150390123

SELECT kanimi
FROM kayttaja
WHERE NOT EXISTS (
    SELECT 1
    FROM tuote
    WHERE tuote.tmtunnus = (SELECT tmtunnus FROM tuotemerkki WHERE tmnimi = 'KooTek') 
    AND NOT EXISTS (
        SELECT 1 
        FROM arviointi 
        WHERE arviointi.ttunnus = tuote.ttunnus 
        AND arviointi.katunnus = kayttaja.katunnus)
)
ORDER BY kanimi ASC;