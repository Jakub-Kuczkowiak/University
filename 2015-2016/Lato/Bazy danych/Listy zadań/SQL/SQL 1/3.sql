SELECT MAX(w.data) - MIN(w.data)
FROM
	grupa g
	JOIN przedmiot_semestr psem ON g.kod_przed_sem = psem.kod_przed_sem
	JOIN przedmiot p ON p.kod_przed = psem.kod_przed
	JOIN wybor w ON g.kod_grupy = w.kod_grupy
WHERE
	semestr_id = 38 AND
	rodzaj_zajec = 'w' AND
	nazwa = 'Matematyka dyskretna (M)';

/*
 21 days 08:01:19.774472
 Razem : 22 dni
 */