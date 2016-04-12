SELECT COUNT(*)
FROM
	przedmiot_semestr psem JOIN
	przedmiot p ON psem.kod_przed = p.kod_przed
	JOIN grupa g ON g.kod_przed_sem = psem.kod_przed_sem
WHERE
	p.rodzaj = 'o' AND
	g.rodzaj_zajec = 'e';

/* 40 */