-- h2t2
-- Lappalainen Lassi 150390123

SELECT a.artwork_id, a.artwork_name, ar.first_name, ar.last_name, a.year_created
FROM artwork a
JOIN artist ar ON a.artist_id = ar.artist_id
ORDER BY a.artwork_id ASC;
