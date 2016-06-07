-- Zad 1

SELECT COUNT(*)
FROM users u
WHERE u.id NOT IN (
		SELECT DISTINCT c.userid
		FROM 
			posts p JOIN comments c ON p.id = c.postid
		WHERE
			c.userid = p.owneruserid
	);

-- Zad 2

SELECT DISTINCT p
FROM
	posts p JOIN comments c ON c.postid = p.id
	JOIN users u ON u.id = c.userid
WHERE  (u.age IS NULL OR u.age >= 55) AND c.score = 1 AND p.title IS NOT NULL
GROUP BY p
HAVING COUNT(*) >= 2;
