-- h3t3
-- Lappalainen Lassi 150390123

SELECT b1.title, b2.title AS sequel_title
FROM book b1
LEFT JOIN book b2 ON b1.id = b2.predecessor_id
ORDER BY b1.id ASC;
