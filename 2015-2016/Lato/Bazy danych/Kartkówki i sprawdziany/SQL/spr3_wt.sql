-- Zadanie 1

SELECT b.name AS "odznaka", COUNT(*) AS "liczba"
FROM users u JOIN badges b ON b.userid = u.id 
	JOIN comments c ON c.userid = u.id
GROUP BY b.name
ORDER BY COUNT(*) DESC;


-- Zadanie 2

WITH postss AS
(
	SELECT p.id, COUNT(*) AS "ile"
	FROM posts p JOIN posts q ON p.id = q.parentid
	WHERE p.posttypeid = 1
	GROUP BY p.id
	ORDER BY COUNT(*) DESC
	LIMIT 1
)

SELECT p.id
FROM postss p
WHERE p.ile >= ALL (SELECT ile FROM postss);

-- Zadanie 3 (WERSJA BEZ PUSTYCH)

WITH myposts AS
(
	SELECT p.id
	FROM posts p JOIN badges b ON b.userid = p.owneruserid
	WHERE
	p.creationdate <= date '2010-09-08' AND b.name = 'Explainer'
),

res AS (
	SELECT p.id, COUNT(p.id) as "ile"
	FROM myposts p JOIN posts odp ON odp.parentid = p.id
	WHERE odp.posttypeid = 2
	GROUP BY p.id
	ORDER BY COUNT(p.id) ASC
)

SELECT AVG(r.ile) FROM res r;