SELECT x.nazwa, x.ile
FROM
(
	SELECT s.nazwa AS nazwa, COUNT(s.nazwa) AS ile
	FROM
		semestr s JOIN
		przedmiot_semestr psem ON psem.semestr_id = s.semestr_id JOIN
		przedmiot p ON p.kod_przed = psem.kod_przed
	WHERE
		p.rodzaj = 'o'
	GROUP BY
		s.nazwa
) x
ORDER BY ile DESC
LIMIT 1;

/*
          nazwa          | ile 
-------------------------+-----
 Semestr zimowy 2009/2010 |  11
*/