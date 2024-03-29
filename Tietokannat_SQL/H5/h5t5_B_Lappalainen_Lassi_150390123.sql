-- h5t5
-- Lappalainen Lassi 150390123

SELECT artist.artist_id, artist.first_name, artist.last_name, COUNT(artwork.artwork_id) AS artwork_count, MIN(artwork.value) AS min_value, MAX(artwork.value) AS max_value
FROM artist
LEFT JOIN artwork ON artist.artist_id = artwork.artist_id
GROUP BY artist.artist_id, artist.first_name, artist.last_name
ORDER BY artist.artist_id ASC;