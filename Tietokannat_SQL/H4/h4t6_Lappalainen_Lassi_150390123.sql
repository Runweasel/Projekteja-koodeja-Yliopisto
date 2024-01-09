-- h4t6
-- Lappalainen Lassi 150390123

SELECT DISTINCT a.artist_id, a.first_name
FROM artist a
JOIN artwork s ON a.artist_id = s.artist_id
JOIN artwork d ON a.artist_id = d.artist_id
WHERE s.technique='drawing' AND d.technique = 'painting'
ORDER BY a.artist_id;