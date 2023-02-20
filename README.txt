---------------------------------- Compiling instructions ------------------------------------------
run these commands from Project folder:

$ sh config.sh
$ make

----------------------------------------------------------------------------------------------------
Then you can edit the interface.idl file (or you can create you own .idl file)
where you define your needed interfaces following the below syntax:

----------------------------------------------------------------------
interface [interface name] 
{
	[methods list]
}
----------------------------------------------------------------------
-- syntax of an element in method list
[return type] [method name] ([comma separated type-name-pair argument list]);

note:	for now, the only supported type for both return statement and argument list
		is int.

----------------------------------------------------------------------------------------------------
Once you have your .idl file ready, you can lounch the parser, passing it the idl file as argument:

$ ./bin/parse [idl file]

This will generate, in Autogen folder, all the needed files to compile your interfaces.

To create your interface service you can edit the service header and cpp files located in
Autogen/inc and Autogen/imp folders respectively

note: in the test folder there are 2 example of service implementation relative to the
interfaces (Car and Plane) of the test

----------------------------------------------------------------------------------------------------
Once your services are ready, you can compile an interface running the below command
from Autogen folder:
$ make [interface name]

This will create one .so file named lib[interface name] in the lib folder

----------------------------------------------------------------------------------------------------
Now you can write two mains (one for the server side, one for the client side) in the
test folder, or you can edit the already present testServer and testClient, in the
same folder.

note: the two test files presents in the test folder show you the correct usage of the
ORB. In particular:
- testServer.cpp shows you how to deploy a service;
- testClient.cpp shows you how to use a service;

To compile these tests you need to tell the Makefile which are your test files,
editing the Makefile variables serverexe and clientexe and adding to LDFLAGS
one optioni -l[interface name] for each of your interface.
Then you can lounch:
$ make [test server file-name]
$ make [test client file-name]

--------------------------------- Running instructions ---------------------------------------------
run these commands in three separate terminal window:
				      (or)
1$ ./bin/NameServer			|	1$ sh runns.sh
					|
2$ export LD_LIBRARY_PATH=./lib		|	2$ sh runserver.sh
2$ ./bin/[server test fil-name]		|
					|
3$ export LD_LIBRARY_PATH=./lib		|	3$ sh runclient.sh
3$ ./bin/[client test fil-name]		|
					|
