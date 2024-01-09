-- h2t8
-- Lappalainen Lassi 150390123

SELECT a.artwork_id, a.artwork_name, e.exhibition_id, e.exhibition_name, e.year
FROM artwork a
LEFT JOIN displayed_at da ON a.artwork_id = da.artwork_id
LEFT JOIN exhibition e ON da.exhibition_id = e.exhibition_id
ORDER BY a.artwork_id ASC, e.exhibition_id ASC;
