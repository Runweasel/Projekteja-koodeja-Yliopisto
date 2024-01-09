-- h6t5
-- Lappalainen Lassi 150390123

SELECT artist.artist_id, artist.first_name, artist.last_name
FROM artist
INNER JOIN (
    SELECT artist_id
    FROM artwork
    WHERE technique IN ('painting', 'drawing')
    GROUP BY artist_id
    HAVING COUNT(DISTINCT technique) = 2
) AS artist_techniques ON artist.artist_id = artist_techniques.artist_id
ORDER BY artist.artist_id ASC;