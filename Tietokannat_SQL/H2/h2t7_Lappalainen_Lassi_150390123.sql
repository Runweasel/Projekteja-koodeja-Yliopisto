-- h2t7
-- Lappalainen Lassi 150390123

SELECT ar.first_name, ar.last_name, ar.artist_id, a.artwork_id, a.artwork_name 
FROM artist ar
LEFT JOIN artwork a ON ar.artist_id = a.artist_id
ORDER BY ar.artist_id ASC, a.artwork_id ASC;
