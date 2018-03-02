create table Acft_model(
	id integer primary key not null,
	name text,
	freq_max integer,
	nop integer,
	ntot integer
);

create table Pnt(
	id text primary key not null,
	role text check(role in ('cpt', 'fo', 'fe')),
	freq_max integer,
	acft_modelid integer,
	foreign key (acft_modelid) references Acft_model(id)
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
insert into Acft_model (id, name, freq_max, nop, ntot)
values (0, 'a', 2, 12, 15);
insert into Acft_model (id, name, freq_max, nop, ntot)
values (1, 'b', 6, 9, 10);
-- Add PNTs
insert into Pnt (id, role, freq_max, acft_modelid)
values ('ag', 'cpt', 2, 0);
insert into Pnt (id, role, freq_max, acft_modelid)
values ('cr', 'fo', 2, 0);
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
insert into Acft_model (id, name, freq_max, nop, ntot)
values (0, 'a', 2, 12, 15);

-- Pnts (captains)
insert into Pnt (id, role, freq_max, acft_modelid)
values ('aa', 'cpt', 0, 0);
insert into Pnt (id, role, freq_max, acft_modelid)
values ('ab', 'cpt', 0, 0);
insert into Pnt (id, role, freq_max, acft_modelid)
values ('ac', 'cpt', 0, 0);
insert into Pnt (id, role, freq_max, acft_modelid)
values ('ad', 'cpt', 0, 0);
insert into Pnt (id, role, freq_max, acft_modelid)
values ('ae', 'cpt', 0, 0);
insert into Pnt (id, role, freq_max, acft_modelid)
values ('af', 'cpt', 0, 0);
