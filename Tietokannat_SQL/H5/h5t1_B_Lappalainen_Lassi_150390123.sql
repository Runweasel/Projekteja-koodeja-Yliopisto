-- h5t1
-- Lappalainen Lassi 150390123

SELECT COUNT(*) AS artwork_count, MIN(value) AS min_value, MAX(value) AS max_value
FROM artwork;