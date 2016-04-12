SELECT imie || ' ' || nazwisko
FROM
	uzytkownik uz JOIN wybor w ON uz.kod_uz = w.kod_uz
	JOIN grupa g ON g.kod_grupy = w.kod_grupy
	JOIN przedmiot_semestr psem ON g.kod_przed_sem = psem.kod_przed_sem
	JOIN przedmiot p ON p.kod_przed = psem.kod_przed
WHERE
	p.nazwa = 'Matematyka dyskretna (M)' AND
	psem.semestr_id = 38 AND
	g.rodzaj_zajec = 'w'
ORDER BY w.data ASC
LIMIT 1;

/*  Damian Pabacki2569 */