create table Pnt(
	id integer primary key autoincrement not null,
	name text,
	role text check(role in ('cpt', 'fo', 'fe')),
	freq_max integer,
	foreign key (acft_modelid) references Acft_model(id)
);

create table Acft_model(
	id integer primary key autoincrement not null,
	name text,
	freq_max integer,
	nop integer,
	ntot integer,
);

create table Workday(
	id integer primary key autoincrement not null,
	workdate text,
	status text check(status in ('off', 'standby', 'office', 'v1', 'v2', 'v3')),
	foreign key (pntid) references Pnt(id)
);
