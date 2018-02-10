create table Acft_model(
	id integer primary key not null,
	name text,
	freq_max integer,
	nop integer,
	ntot integer
);

create table Pnt(
	id integer primary key not null,
	name text,
	role text check(role in ('cpt', 'fo', 'fe')),
	freq_max integer,
	acft_modelid integer,
	foreign key (acft_modelid) references Acft_model(id)
);

create table Workday(
	workdate text,
	status text check(status in ('off', 'standby', 'office', 'v1', 'v2', 'v3')),
	pntid integer,
	foreign key (pntid) references Pnt(id),
	primary key(workdate, pntid)
);

-- Populate a bit
-- Add aricrafts
insert into Acft_model (id, name, freq_max, nop, ntot)
values (0, 'a', 4, 12, 15);
insert into Acft_model (id, name, freq_max, nop, ntot)
values (1, 'b', 6, 9, 10);
-- Add PNTs
insert into Pnt (id, name, role, freq_max, acft_modelid)
values (0, 'ag', 'cpt', 2, 0);
insert into Pnt (id, name, role, freq_max, acft_modelid)
values (1, 'cr', 'fo', 2, 0);
-- Add workdays
-- PNT 0
insert into Workday (workdate, status, pntid)
values ('2018-02-10', 'off', 0);
insert into Workday (workdate, status, pntid)
values ('2018-02-11', 'off', 0);
insert into Workday (workdate, status, pntid)
values ('2018-02-12', 'standby', 0);
-- PNT 1
insert into Workday (workdate, status, pntid)
values ('2018-02-10', 'off', 1);
insert into Workday (workdate, status, pntid)
values ('2018-02-11', 'office', 1);
insert into Workday (workdate, status, pntid)
values ('2018-02-12', 'v1', 1);
