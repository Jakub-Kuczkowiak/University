SELECT DISTINCT nazwisko
FROM
	semestr sem JOIN przedmiot_semestr przedsem ON sem.semestr_id = przedsem.semestr_id  
	JOIN przedmiot przed ON przed.kod_przed = przedsem.kod_przed 
	JOIN grupa gr ON gr.kod_przed_sem = przedsem.kod_przed_sem
	JOIN uzytkownik uz ON gr.kod_uz = uz.kod_uz
WHERE
	sem.nazwa = 'Semestr zimowy 2010/2011' AND
	przed.nazwa = 'Matematyka dyskretna (M)' AND
	gr.rodzaj_zajec = 'c' AND
	uz.semestr = 0
ORDER BY nazwisko ASC;

/*
 Bieńkowski
 Paluch
 Stachowiak
 Sysło
*/