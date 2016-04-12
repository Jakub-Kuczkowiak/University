SELECT COUNT(*)
FROM
	uzytkownik u JOIN
	grupa g ON g.kod_uz = u.kod_uz JOIN
	przedmiot_semestr psem ON psem.kod_przed_sem = g.kod_przed_sem JOIN
	przedmiot p ON p.kod_przed = psem.kod_przed

WHERE
	u.imie = 'Witold' AND
	u.nazwisko = 'Charatonik' AND
	p.nazwa LIKE 'Logika dla inf%';

/* 12 */