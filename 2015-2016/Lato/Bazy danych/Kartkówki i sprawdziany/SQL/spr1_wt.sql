-- Zad 1

SELECT DISTINCT u.id, u.displayname
FROM users u JOIN posts p ON p.owneruserid = u.id
	JOIN comments c ON c.postid = p.id
WHERE
	c.score >= 12;

-- Zad 2a

SELECT p.title, p.answercount
FROM posts p
WHERE p.title IS NOT NULL
ORDER BY p.answercount DESC
LIMIT 18;

-- Zad 2b

SELECT p.title, p.answercount
FROM posts p
WHERE p.title IS NOT NULL
ORDER BY p.answercount ASC
LIMIT 9;

-- Zad 3

SELECT DISTINCT u.displayname, b.name, EXTRACT(month FROM b.date)
FROM users u JOIN badges b ON b.userid = u.id
	JOIN comments c ON c.userid = u.id
WHERE
	u.reputation > 20000 AND
	c.score < 1
ORDER BY u.displayname ASC;

-- Zad 4

SELECT COUNT(*)
FROM users u
WHERE u.websiteurl IS NOT NULL AND u.websiteurl LIKE '%google%';