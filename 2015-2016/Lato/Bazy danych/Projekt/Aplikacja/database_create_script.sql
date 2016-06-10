DROP DATABASE IF EXISTS bikerental;
DROP ROLE IF EXISTS servicemanrole;
DROP ROLE IF EXISTS usserrole;
DROP ROLE IF EXISTS adminrole;

CREATE DATABASE BikeRental
    OWNER vagrant
    ENCODING 'Unicode';

\connect bikerental

CREATE EXTENSION pgcrypto;

-- TABLES:

CREATE TABLE "service" (
  "id" SERIAL PRIMARY KEY,
  "address" TEXT NOT NULL,
  "longitude" DOUBLE PRECISION NOT NULL,
  "latitude" DOUBLE PRECISION NOT NULL
);

CREATE TABLE "serviceman" (
  "id" SERIAL PRIMARY KEY,
  "name" TEXT NOT NULL,
  "surname" TEXT NOT NULL,
  "email" TEXT NOT NULL,
  "phonenumber" TEXT NOT NULL
);

CREATE TABLE "station" (
  "id" SERIAL PRIMARY KEY,
  "address" TEXT NOT NULL,
  "numberoffreespaces" INTEGER NOT NULL,
  "service" INTEGER NOT NULL,
  "capacity" INTEGER NOT NULL,
  "longitude" DOUBLE PRECISION NOT NULL,
  "latitude" DOUBLE PRECISION NOT NULL
);

CREATE TABLE "serviceman_station" (
  "serviceman" INTEGER NOT NULL,
  "station" INTEGER NOT NULL,
  PRIMARY KEY ("serviceman", "station")
);

CREATE TABLE "usser" (
  "id" SERIAL PRIMARY KEY,
  "name" TEXT NOT NULL,
  "surname" TEXT NOT NULL,
  "address" TEXT,
  "pesel" CHAR(11) UNIQUE,
  "email" TEXT UNIQUE NOT NULL,
  "phonenumber" TEXT UNIQUE NOT NULL,
  "balance" DOUBLE PRECISION NOT NULL DEFAULT 0.0,
  "bike" INTEGER,
  "passwordhash" TEXT NOT NULL

  CHECK(balance >= 0.0)
);

CREATE TABLE "bike" (
  "id" SERIAL PRIMARY KEY,
  "color" TEXT,
  "thelastoverviewdate" TIMESTAMP,
  "isingoodcondition" BOOLEAN NOT NULL DEFAULT true,
  "station" INTEGER,
  "modelname" TEXT NOT NULL
);

CREATE TABLE "rent" (
  "id" SERIAL PRIMARY KEY,
  "startdate" TIMESTAMP NOT NULL,
  "enddate" TIMESTAMP,
  "bike" INTEGER NOT NULL,
  "usser" INTEGER NOT NULL

  CHECK(startdate < enddate)
);

CREATE TABLE "issue" (
  "id" SERIAL PRIMARY KEY,
  "reportdate" TIMESTAMP NOT NULL,
  "finishdate" TIMESTAMP,
  "reportedbyusser" INTEGER NOT NULL,
  "bike" INTEGER NOT NULL,
  "description" TEXT
);

CREATE TABLE "issue_serviceman" (
  "issue" INTEGER NOT NULL,
  "serviceman" INTEGER NOT NULL,
  PRIMARY KEY ("issue", "serviceman")
);

CREATE TABLE "payment" (
  "id" SERIAL PRIMARY KEY,
  "totalinpln" DOUBLE PRECISION NOT NULL,
  "paymentdate" TIMESTAMP NOT NULL,
  "rent" INTEGER NOT NULL

  CHECK (totalinpln >= 0.0)
);

CREATE TABLE "session" (
  "id" SERIAL PRIMARY KEY,
  "expiration_date" TEXT NOT NULL,
  "login" TEXT NOT NULL,
  "hash" TEXT NOT NULL
);

-- INDEXES:


CREATE INDEX "idx_station__service" ON "station" ("service");
CREATE INDEX "idx_serviceman_station" ON "serviceman_station" ("station");
CREATE INDEX "idx_bike__station" ON "bike" ("station");
CREATE INDEX "idx_issue__bike" ON "issue" ("bike");
CREATE INDEX "idx_issue__reportedbyusser" ON "issue" ("reportedbyusser");
CREATE INDEX "idx_issue_serviceman" ON "issue_serviceman" ("serviceman");
CREATE INDEX "idx_rent__bike" ON "rent" ("bike");
CREATE INDEX "idx_rent__usser" ON "rent" ("usser");
CREATE INDEX "idx_payment__rent" ON "payment" ("rent");

-- CONSTRAINTS :

ALTER TABLE "station" ADD CONSTRAINT "fk_station__service" FOREIGN KEY ("service") REFERENCES "service" ("id");
ALTER TABLE "serviceman_station" ADD CONSTRAINT "fk_serviceman_station__serviceman" FOREIGN KEY ("serviceman") REFERENCES "serviceman" ("id");
ALTER TABLE "serviceman_station" ADD CONSTRAINT "fk_serviceman_station__station" FOREIGN KEY ("station") REFERENCES "station" ("id");
ALTER TABLE "bike" ADD CONSTRAINT "fk_bike__station" FOREIGN KEY ("station") REFERENCES "station" ("id");
ALTER TABLE "issue" ADD CONSTRAINT "fk_issue__bike" FOREIGN KEY ("bike") REFERENCES "bike" ("id");
ALTER TABLE "issue" ADD CONSTRAINT "fk_issue__reportedbyusser" FOREIGN KEY ("reportedbyusser") REFERENCES "usser" ("id");
ALTER TABLE "issue_serviceman" ADD CONSTRAINT "fk_issue_serviceman__issue" FOREIGN KEY ("issue") REFERENCES "issue" ("id");
ALTER TABLE "issue_serviceman" ADD CONSTRAINT "fk_issue_serviceman__serviceman" FOREIGN KEY ("serviceman") REFERENCES "serviceman" ("id");
ALTER TABLE "rent" ADD CONSTRAINT "fk_rent__bike" FOREIGN KEY ("bike") REFERENCES "bike" ("id");
ALTER TABLE "rent" ADD CONSTRAINT "fk_rent__usser" FOREIGN KEY ("usser") REFERENCES "usser" ("id");
ALTER TABLE "payment" ADD CONSTRAINT "fk_payment__rent" FOREIGN KEY ("rent") REFERENCES "rent" ("id");

-- ROLES :

CREATE ROLE adminrole
    LOGIN
    PASSWORD 'adm';

GRANT ALL PRIVILEGES ON DATABASE bikerental TO adminrole;

CREATE ROLE usserrole
    LOGIN
    PASSWORD 'usser'
    ADMIN adminrole;

GRANT CONNECT ON DATABASE bikerental TO usserrole;

GRANT SELECT ON bike TO usserrole;
GRANT SELECT ON service TO usserrole;
GRANT INSERT ON payment TO usserrole;
GRANT INSERT ON issue TO usserrole;
GRANT INSERT ON rent TO usserrole;
GRANT UPDATE ON usser TO usserrole;
GRANT INSERT ON session TO usserrole;

CREATE ROLE servicemanrole
    LOGIN
    PASSWORD 'service'
    ADMIN adminrole;

GRANT CONNECT ON DATABASE bikerental TO servicemanrole;

GRANT INSERT ON session TO servicemanrole;
GRANT SELECT, INSERT, UPDATE ON bike TO servicemanrole;
GRANT SELECT, INSERT, UPDATE ON service TO servicemanrole;
GRANT SELECT, UPDATE ON issue TO servicemanrole;

--- Users:

INSERT INTO public.usser (id, name, surname, address, pesel, email, phonenumber, balance, bike, passwordhash) VALUES (1, 'Jan', 'Kowalski', 'Kochanowskiego 15', '12312312312', 'jan.kowalski@gmail.com', '123123123', 10.42, null, 'e99a18c428cb38d5f260853678922e03');
INSERT INTO public.usser (id, name, surname, address, pesel, email, phonenumber, balance, bike, passwordhash) VALUES (2, 'Marcin', 'Kowalski', 'Łódźka 20', '11122233312', 'marcin.kowalski@gmail.com', '123123', 999.99, null, 'ba3794af31d7915ad8d76d15256f6690');
INSERT INTO public.usser (id, name, surname, address, pesel, email, phonenumber, balance, bike, passwordhash) VALUES (3, 'Piotr', 'Bielak', 'Opolska 421', '99988877799', 'piotr.bielak@gmail.com', '666777888', 0, null, '273e748156cdd68c20b080a7d1208cf5');
INSERT INTO public.usser (id, name, surname, address, pesel, email, phonenumber, balance, bike, passwordhash) VALUES (4, 'Bartosz', 'Bednarczyk', 'Skłodowskiej 15/34', '95032006676', 'bartosz.bednarczyk@gmail.com', '510666842', 20, null, '802b3383a4369db9b2cae37ef54f587c');
INSERT INTO public.usser (id, name, surname, address, pesel, email, phonenumber, balance, bike, passwordhash) VALUES (5, 'Roman', 'Polański', 'Piotrkowo 3', '11111111111', 'fasjkfask@fsafsa.com', '999534218', 20, null, '1e9dc4fb01f42f8ed67078ad89292481');


-- Services:

INSERT INTO public.service (id, address, longitude, latitude) VALUES (1, 'Plac Nowy Targ', 51.111, 17.038);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (2, 'Mazowiecka', 51.106, 17.05);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (3, 'Powstańców Śląskich', 51.0914, 17.018);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (4, 'Piastowska', 51.113279, 17.060564);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (5, 'Ratusz', 51.110788, 17.031846);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (6, 'Renoma', 51.103610, 17.031351);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (7, 'Dworzec PKP', 51.098984, 17.035251);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (8, 'Skytower', 51.095016, 17.018328);
INSERT INTO public.service (id, address, longitude, latitude) VALUES (9, 'Ogród Japoński', 51.110013, 17.079844);

-- Stations:

INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (1, 'Szewska', 10, 1, 10, 51.111433, 17.035383);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (2, 'Traugutta', 20, 2, 20, 51.103049, 17.050165);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (3, 'Komandorska', 5, 3, 5, 51.0917, 17.025);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (4, 'Komandorska', 20, 4, 20, 51.112100, 17.062366);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (5, 'Szczytnicka', 20, 4, 20, 51.113386, 17.053787);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (6, 'Fryderyka Joliot-Curie', 10, 4, 10, 51.111386, 17.051620);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (7, 'Hala targowa', 10, 5, 10, 51.112583, 17.039647);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (8, 'Fryderyka Joliot-Curie', 10, 5, 10, 51.108397, 17.038424);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (9, 'Park wodny', 10, 8, 10, 51.091321, 17.031162);
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (10, 'Krucza', 10, 8, 10, 51.091321, 17.031162 );
INSERT INTO public.station (id, address, numberoffreespaces, service, capacity, longitude, latitude) VALUES (11, 'Ślężna', 10, 7, 10, 51.096530, 17.031769 );


-- Bikes:


INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (1, 'Niebieski', TIMESTAMP '2016-05-01 15:00:00', TRUE, 1, 'Romet VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (2, 'Czerwony', TIMESTAMP '2016-03-02 16:00:00', FALSE, 1, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (3, 'Zielony', TIMESTAMP '2016-05-01 13:00:00', TRUE, 1, 'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (4, 'Rozowy', TIMESTAMP '2016-03-02 18:00:00', TRUE, 2, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (5, 'Bialy', TIMESTAMP '2016-03-01 16:00:00', TRUE, 2, 'Romet VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (6, 'Czarny', TIMESTAMP '2016-01-01 11:00:00', TRUE, 2,  'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (7, 'Pomaranczowy', TIMESTAMP '2016-03-02 12:00:00', FALSE, 3, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (8, 'Turkusowy', TIMESTAMP '2016-02-01 13:00:00', TRUE, 3, 'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (9, 'Zloty', TIMESTAMP '2016-05-04 19:00:00', FALSE, 3, 'Romet LK70');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (10, 'Niebieski', TIMESTAMP '2016-05-01 15:00:00', TRUE, 1, '‎Kross W150');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (11, 'Zółty', TIMESTAMP '2016-05-01 15:00:00', TRUE, 1, 'Merida OF99');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (12, 'Zielony', TIMESTAMP '2016-05-01 15:00:00', TRUE, 1, 'Romet VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (13, 'Czerwony', TIMESTAMP '2016-05-01 15:00:00', TRUE, 4, 'Merida V30');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (14, 'Fioletowy', TIMESTAMP '2016-05-01 15:00:00', TRUE, 4, 'Schwinn VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (15, 'Niebieski', TIMESTAMP '2016-05-01 15:00:00', TRUE, 6, 'Wigry VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (16, 'Czerwony', TIMESTAMP '2016-03-02 16:00:00', FALSE, 6, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (17, 'Zielony', TIMESTAMP '2016-05-01 13:00:00', TRUE, 6, 'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (18, 'Rozowy', TIMESTAMP '2016-03-02 18:00:00', TRUE, 4, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (19, 'Bialy', TIMESTAMP '2016-03-01 16:00:00', TRUE, 5, 'Romet VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (20, 'Czarny', TIMESTAMP '2016-01-01 11:00:00', TRUE, 5,  'Wigry 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (21, 'Niebieski', TIMESTAMP '2016-05-01 15:00:00', TRUE, 4, 'Romet VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (22, 'Czerwony', TIMESTAMP '2016-03-02 16:00:00', FALSE, 5, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (23, 'Zielony', TIMESTAMP '2016-05-01 13:00:00', TRUE, 5, 'Schwinn 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (24, 'Zielony', TIMESTAMP '2016-05-01 13:00:00', TRUE, 11, 'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (25, 'Rozowy', TIMESTAMP '2016-03-02 18:00:00', TRUE, 11, 'Schwinn HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (26, 'Bialy', TIMESTAMP '2016-03-01 16:00:00', TRUE, 10, 'Romet VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (27, 'Czarny', TIMESTAMP '2016-01-01 11:00:00', TRUE, 10,  'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (28, 'Niebieski', TIMESTAMP '2016-05-01 15:00:00', TRUE, 9, 'Schwinn VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (29, 'Czerwony', TIMESTAMP '2016-03-02 16:00:00', FALSE, 9, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (30, 'Zielony', TIMESTAMP '2016-05-01 13:00:00', TRUE, 8, 'Loperdo 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (31, 'Niebieski', TIMESTAMP '2016-05-01 15:00:00', TRUE, 8, 'Schwinn VX50');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (32, 'Czerwony', TIMESTAMP '2016-03-02 16:00:00', FALSE, 7, 'Fakir HP23');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (33, 'Zielony', TIMESTAMP '2016-05-01 13:00:00', TRUE, 7, 'Wigry 4545');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (34, 'Czerwony', TIMESTAMP '2016-05-01 15:00:00', TRUE, 6, 'Schwinn V30');
INSERT INTO public.bike (id, color, thelastoverviewdate, isingoodcondition, station, modelname) VALUES (35, 'Fioletowy', TIMESTAMP '2016-05-01 15:00:00', TRUE, 6, 'Wigry VX50');
