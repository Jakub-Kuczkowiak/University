SELECT COUNT(*)
FROM
	przedmiot p
WHERE
	p.rodzaj = 'k' AND
	p.kod_przed NOT IN(SELECT kod_przed FROM przedmiot_semestr);

/* 43 */