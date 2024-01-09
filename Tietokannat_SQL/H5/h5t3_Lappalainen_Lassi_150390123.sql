-- h5t3
-- Lappalainen Lassi 150390123

SELECT artist.artist_id, artist.first_name, artist.last_name
FROM artist
INNER JOIN artwork ON artist.artist_id = artwork.artist_id
WHERE artwork.technique IN ('painting', 'drawing')
GROUP BY artist.artist_id, artist.first_name, artist.last_name
HAVING COUNT(DISTINCT artwork.technique) = 2
ORDER BY artist.artist_id ASC;