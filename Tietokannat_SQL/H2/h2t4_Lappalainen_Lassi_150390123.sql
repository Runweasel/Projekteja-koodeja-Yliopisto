-- h2t4
-- Lappalainen Lassi 150390123

SELECT a.artwork_id, a.artwork_name, a.technique   
FROM artwork a
JOIN displayed_at da ON a.artwork_id = da.artwork_id
JOIN exhibition e ON da.exhibition_id = e.exhibition_id
WHERE e.location = 'Museum of Modern Art'
ORDER BY a.artwork_id ASC;
