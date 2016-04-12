SELECT COUNT(*)
FROM (
	SELECT DISTINCT(u.kod_uz)
	FROM
		przedmiot p JOIN
		przedmiot_semestr psem ON p.kod_przed = p.kod_przed JOIN
		grupa g ON g.kod_przed_sem = psem.kod_przed_sem JOIN
		uzytkownik u ON u.kod_uz = g.kod_uz
	WHERE
		p.nazwa = 'Algorytmy i struktury danych (M)'
	GROUP BY u.kod_uz, psem.semestr_id
	HAVING COUNT(psem.semestr_id) > 1
) x;