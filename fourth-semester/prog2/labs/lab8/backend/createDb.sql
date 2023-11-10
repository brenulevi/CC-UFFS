CREATE TABLE courses (
    cid integer not null,
    cname varchar(40) not null,
    descr text not null,
    constraint pk_courses primary key (cid)
);

CREATE TABLE ccrs (
    crid integer not null,
    crname varchar(40) not null,
    qtclass integer not null,
    cid integer not null,
    constraint pk_ccrs primary key (crid),
    constraint fk_ccrs_courses foreign key (cid) references courses(cid)
);