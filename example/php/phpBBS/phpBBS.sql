use db_php;
create table topic(
id integer primary key,
creater varchar(16),
title varchar(64),
article blob
);

create table reply(
id integer primary key,
tid integer,
creater varchar(16),
title varchar(64),
article blob,
foreign key (tid) references topic(id)
);

#create index topic4reply on reply(tid);

insert into topic values(1,'simon','first','It\'s first reply'),(2,'a','sasaa','sadfsad');
insert into reply values(2,1,'simon','first reply','for myself');