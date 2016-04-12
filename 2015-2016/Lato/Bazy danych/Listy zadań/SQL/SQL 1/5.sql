SELECT COUNT(*)
FROM 
(
	SELECT DISTINCT(nazwisko)
	FROM 
		semestr s JOIN
		przedmiot_semestr psem ON psem.semestr_id = s.semestr_id
		JOIN przedmiot p ON p.kod_przed = psem.kod_przed
		JOIN grupa g ON g.kod_przed_sem = psem.kod_przed_sem
		JOIN uzytkownik u ON u.kod_uz = g.kod_uz

	WHERE 
		s.nazwa LIKE '%zimowy%' AND
		p.rodzaj = 'o' AND
		(g.rodzaj_zajec = 'c' OR g.rodzaj_zajec = 'C') AND
		u.semestr = 0
) x;