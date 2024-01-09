-- Harjoitustyö Kysely 2A
-- Lappalainen Lassi 150390123

SELECT k.syntymavuosi, k.kanimi 
FROM kayttaja k
WHERE k.katunnus IN (
    SELECT a.katunnus
    FROM arviointi a
    JOIN tuote t ON a.ttunnus = t.ttunnus
    JOIN tuotemerkki tm ON t.tmtunnus = tm.tmtunnus
    WHERE tm.tmnimi = 'KooTek'
    INTERSECT
    SELECT a.katunnus
    FROM arviointi a
    JOIN tuote t ON a.ttunnus = t.ttunnus
    JOIN tuotemerkki tm ON t.tmtunnus = tm.tmtunnus
    WHERE tm.tmnimi = 'McCee'
)
ORDER BY k.syntymavuosi, k.kanimi;