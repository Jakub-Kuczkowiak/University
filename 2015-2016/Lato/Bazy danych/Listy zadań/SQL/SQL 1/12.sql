SELECT COUNT(*)
FROM
(
	SELECT DISTINCT p.nazwa
	FROM przedmiot p
	WHERE p.nazwa LIKE '%(ang.)%'

) x;

/* 23. */