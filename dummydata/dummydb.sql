create table Acft_model(
	name text primary key not null,
	maxfreq integer,
	crew integer,
	nop integer,
	ntot integer
);

create table Pnt(
	id text primary key not null,
	name text,
	role text check(role in ('cpt', 'fo', 'fe')),
	maxfreq integer,
	acft_modelname text,
	flightnb integer default 0,
	foreign key (acft_modelname) references Acft_model(name)
);

create table Workday(
	workdate text,
	status text check(status in ('off', 'standby', 'office', 'v1', 'v2', 'v3')),
	pntid text,
	foreign key (pntid) references Pnt(id),
	primary key(workdate, pntid)
);

-- Populate a bit
-- Add aircrafts
insert into Acft_model (name, crew, maxfreq, nop, ntot)
values ('b', 2, 6, 9, 10);
-- Add PNTs
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ag', 'Alfred Guimbert', 'cpt', 2, 'b');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('cr', 'Charles Ruin', 'fo', 2, 'b');
-- Add workdays
-- PNT 0
insert into Workday (workdate, status, pntid)
values ('2018-02-10', 'off', 'ag');
insert into Workday (workdate, status, pntid)
values ('2018-02-11', 'off', 'ag');
insert into Workday (workdate, status, pntid)
values ('2018-02-12', 'standby', 'ag');
-- PNT 1
insert into Workday (workdate, status, pntid)
values ('2018-02-10', 'off', 'cr');
insert into Workday (workdate, status, pntid)
values ('2018-02-11', 'office', 'cr');
insert into Workday (workdate, status, pntid)
values ('2018-02-12', 'v1', 'cr');


-- Data for a schedule (3 days)
-- Aircraft model
insert into Acft_model (name, maxfreq, nop, ntot)
values ('a', 2, 12, 15);

-- Pnts (captains)
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('aa', 'Afdas Adfex', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ab', 'Aerfds Bfea', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ac', 'Adfsdf Cdfse', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ad', 'Adfee Dvcxz', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ae', 'Aefdfg Edfse', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('af', 'Aefdfs Fdsae', 'cpt', 0, 'a');
