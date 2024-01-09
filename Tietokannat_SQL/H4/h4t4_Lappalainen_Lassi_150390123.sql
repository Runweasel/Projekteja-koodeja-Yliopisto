-- h4t4
-- Lappalainen Lassi 150390123

SELECT technique, artwork_name, last_name
FROM artwork, artist
WHERE artwork.artist_id = artist.artist_id AND (
technique='drawing' OR
technique = 'sculpture')
ORDER BY technique, artwork_name;
