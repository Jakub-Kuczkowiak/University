SELECT u.kod_uz
FROM
	przedmiot p JOIN
	przedmiot_semestr psem ON psem.kod_przed = p.kod_przed JOIN
	grupa g ON g.kod_przed_sem = psem.kod_przed_sem JOIN
	uzytkownik u ON u.kod_uz = g.kod_uz
WHERE
	p.nazwa LIKE 'Bazy danych'
GROUP BY u.kod_uz
HAVING COUNT(semestr_id) = 2;

/* 2 */