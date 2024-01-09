-- h2t6
-- Lappalainen Lassi 150390123

SELECT DISTINCT a.artwork_id, a.artwork_name
FROM artwork a
JOIN displayed_at da ON a.artwork_id = da.artwork_id
GROUP BY a.artwork_id, a.artwork_name
HAVING COUNT(da.exhibition_id) >= 1
ORDER BY a.artwork_id ASC;
