-- Zadanie 1

ALTER TABLE users ADD COLUMN posts integer NOT NULL DEFAULT 0;

UPDATE users u SET posts = (
	SELECT COUNT(*) FROM posts WHERE
	owneruserid = u.id
);

ALTER TABLE users DROP COLUMN posts;

-- Zadanie 2

CREATE TABLE Explainers(
   userid int PRIMARY KEY,
   displayname text,
   yearofbirth int);

INSERT INTO Explainers
SELECT b.userid, u.displayname, EXTRACT(year FROM current_date) - u.age
FROM badges b JOIN users u ON b.userid = u.id
WHERE b.name = 'Explainer';

ALTER TABLE users ADD CONSTRAINT exp_age
        CHECK (users.age IS NULL OR users.age BETWEEN 0 AND 120);

ALTER TABLE Explainers ADD CONSTRAINT exp_yearofbirth
        CHECK (Explainers.yearofbirth <= EXTRACT (year FROM current_date));

ALTER TABLE users DROP CONSTRAINT exp_age;
ALTER TABLE Explainers DROP CONSTRAINT exp_yearofbirth;

DROP TABLE Explainers;

-- Zadanie 3

DELETE FROM posts
WHERE owneruserid IS NULL OR owneruserid NOT IN (
	SELECT users.id FROM users);

ALTER TABLE posts ALTER COLUMN owneruserid SET NOT NULL;