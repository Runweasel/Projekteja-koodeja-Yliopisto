-- h6t3
-- Lappalainen Lassi 150390123

SELECT artwork_id, artwork_name
FROM artwork
WHERE EXISTS (
    SELECT *
    FROM displayed_at
    WHERE displayed_at.artwork_id = artwork.artwork_id
)
ORDER BY artwork_id ASC;