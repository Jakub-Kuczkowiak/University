-- Bartosz Bednarczyk (273 479) Kartkowka 1

-- Zad 1)

SELECT u.id, u.displayname
FROM 
	comments c JOIN
	users u ON u.id = c.userid JOIN
	posts p ON p.id = c.postid
WHERE
	c.score >= 12;

-- Zad 2


--- A)

SELECT p.title, p.answercount
FROM
	posts p
WHERE
	p.answercount IS NOT NULL AND
	p.title IS NOT NULL
ORDER BY p.answercount DESC
LIMIT 18;

--- B)

SELECT p.title, p.answercount
FROM
	posts p
WHERE
	p.answercount IS NOT NULL AND
	p.title IS NOT NULL
ORDER BY p.answercount ASC
LIMIT 9;

-- Zad 3

SELECT DISTINCT x 
FROM
(
	SELECT u.displayname, b.name, EXTRACT(month FROM b.date)
	FROM
		badges b JOIN
		users u ON u.id = b.userid JOIN
		comments c ON u.id = c.userid
	WHERE
		u.reputation > 20000 AND
		c.score < 1
	ORDER BY u.displayname
) x;

-- Zad 4

SELECT COUNT(*)
FROM users u
WHERE u.websiteurl LIKE '%google%';

