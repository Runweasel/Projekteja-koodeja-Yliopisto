-- h5t2
-- Lappalainen Lassi 150390123

SELECT technique, COUNT(*) AS count
FROM artwork
GROUP BY technique
ORDER BY technique ASC;