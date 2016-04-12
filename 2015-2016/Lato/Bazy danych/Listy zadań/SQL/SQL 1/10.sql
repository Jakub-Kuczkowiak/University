SELECT COUNT(*)
FROM
	semestr s JOIN
	przedmiot_semestr psem ON s.semestr_id = psem.semestr_id JOIN
	przedmiot p ON p.kod_przed = psem.kod_przed JOIN
	grupa g ON g.kod_przed_sem = psem.kod_przed_sem

WHERE
	s.nazwa = 'Semestr zimowy 2010/2011' AND
	p.nazwa LIKE 'Logika dla inf%' AND
	(g.rodzaj_zajec = 'c' OR g.rodzaj_zajec = 'C');

/* 10 */