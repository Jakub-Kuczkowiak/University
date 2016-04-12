SELECT COUNT(*)
FROM
	uzytkownik u JOIN grupa g ON g.kod_uz = u.kod_uz
WHERE
	u.imie = 'Przemysława'
	AND u.nazwisko = 'Kanarek'
	AND (g.rodzaj_zajec = 'r' OR g.rodzaj_zajec = 'R');

/* 4 */