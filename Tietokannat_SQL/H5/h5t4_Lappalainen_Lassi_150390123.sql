-- h5t4
-- Lappalainen Lassi 150390123

SELECT artist.artist_id, artist.first_name, artist.last_name
FROM artist
WHERE artist.artist_id IN (
    SELECT artist_id
    FROM artwork
    WHERE technique = 'painting'
) AND artist.artist_id NOT IN (
    SELECT artist_id
    FROM artwork
    WHERE technique = 'drawing'
)
ORDER BY artist.artist_id ASC;