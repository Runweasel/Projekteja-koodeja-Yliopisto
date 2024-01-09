-- h2t5
-- Lappalainen Lassi 150390123

SELECT e.year, e.exhibition_name, ar.first_name, ar.last_name, a.artwork_name
FROM artist ar
JOIN artwork a ON ar.artist_id = a.artist_id
JOIN displayed_at da ON a.artwork_id = da.artwork_id
JOIN exhibition e ON da.exhibition_id = e.exhibition_id
ORDER BY e.year ASC, ar.last_name ASC, a.artwork_name ASC;
