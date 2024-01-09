-- Harjoitustyö Kysely 1A
-- Lappalainen Lassi 150390123

SELECT tuotemerkki.tmnimi, tuote.tnimi, arviointi.paivamaara, arviointi.arvosana
FROM arviointi
JOIN tuote ON arviointi.ttunnus = tuote.ttunnus
JOIN tuotemerkki ON tuote.tmtunnus = tuotemerkki.tmtunnus
ORDER BY tuotemerkki.tmnimi ASC, tuote.tnimi ASC, arviointi.paivamaara DESC;