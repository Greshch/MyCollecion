
	This app using for learning English language with view each lesson via sql query (SELECT * FROM A2 WHERE les_id=1). It's very comefortable.
It convert text file to sql script and it'll help to view different lesson via les_id.
Set sql query for insert into some table.

Example:

./cmake-build-debug/app input.txt 1 output.sql

It means that you have to execute your app with 3 arguments in cmd(for example linux terminal) 
	input.txt - text file for processing
	1 - lesson's id 
	output.sql - rsult - sql inserts.

store.sql - sql script for creating and inserting db A2.
