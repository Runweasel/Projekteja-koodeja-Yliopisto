-- h5t6
-- Lappalainen Lassi 150390123

SELECT artwork.artwork_id, artwork.artwork_name, COUNT(displayed_at.exhibition_id) AS exhibition_count
FROM artwork
LEFT JOIN displayed_at ON artwork.artwork_id = displayed_at.artwork_id
GROUP BY artwork.artwork_id, artwork.artwork_name
ORDER BY artwork.artwork_id ASC;