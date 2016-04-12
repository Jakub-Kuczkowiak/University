SELECT '(' || x.nazwa || '),'
FROM (
	SELECT DISTINCT p.nazwa AS nazwa
	FROM
		uzytkownik u JOIN
		grupa g ON u.kod_uz = g.kod_uz JOIN
		przedmiot_semestr psem ON psem.kod_przed_sem = g.kod_przed_sem JOIN
		przedmiot p ON p.kod_przed = psem.kod_przed
	WHERE
		u.semestr = 0 AND
		u.nazwisko = 'Urban'
	ORDER BY p.nazwa ASC
) x;

/*  (Analiza matematyczna), */