SELECT MIN(data), MAX(data)
FROM
	przedmiot p JOIN
	przedmiot_semestr psem ON psem.kod_przed = p.kod_przed JOIN
	semestr s ON s.semestr_id = psem.semestr_id JOIN
	grupa g ON g.kod_przed_sem = psem.kod_przed_sem JOIN
	wybor w ON w.kod_grupy = g.kod_grupy
WHERE
	s.nazwa LIKE '%zimowy 2009%';

 /*
 od 2009-09-25 15:20:44.678879+02
 do 2010-01-19 12:09:48.523126+01
  */