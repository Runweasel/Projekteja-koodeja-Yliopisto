-- h3t2
-- Lappalainen Lassi 150390123

SELECT b1.title, b2.title AS predecessor_title
FROM book b1
LEFT JOIN book b2 ON b1.predecessor_id = b2.id
ORDER BY b1.id ASC;
