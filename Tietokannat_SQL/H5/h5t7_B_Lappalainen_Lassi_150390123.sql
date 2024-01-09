-- h5t7
-- Lappalainen Lassi 150390123

SELECT artwork.artwork_id, artwork.artwork_name, artwork.technique
FROM artwork
INNER JOIN (
    SELECT artwork_id
    FROM displayed_at
    GROUP BY artwork_id
    HAVING COUNT(DISTINCT exhibition_id) = 1
) AS single_exhibition ON artwork.artwork_id = single_exhibition.artwork_id
ORDER BY artwork.artwork_id ASC;