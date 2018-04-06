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
	foreign key (acft_modelname) references Acft_model(name)
);

create table Workday(
	workdate text,
	status text check(status in ('off', 'standby', 'office', 'v1', 'v2', 'v3')),
	pntid text,
	forced integer default 0,
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
values ('aa', 'afdas adfex', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ab', 'aerfds bfea', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ac', 'adfsdf cdfse', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ad', 'adfee dvcxz', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('ae', 'aefdfg edfse', 'cpt', 0, 'a');
insert into Pnt (id, name, role, maxfreq, acft_modelname)
values ('af', 'aefdfs fdsae', 'cpt', 0, 'a');
