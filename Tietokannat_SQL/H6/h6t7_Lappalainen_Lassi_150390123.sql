-- h6t7
-- Lappalainen Lassi 150390123

SELECT artwork_name, value, year_created
FROM artwork
WHERE value = (
    SELECT MAX(value)
    FROM artwork
);