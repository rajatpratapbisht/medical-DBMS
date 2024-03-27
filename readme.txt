{PLEASE WATCH PRESENTAION's "CODE DEMO" part before using}


1a: download and install sqlite3 library into the include folder before compiling the code [help: https://www.tutorialspoint.com/sqlite/sqlite_installation.htm]

1b. compiling the files is simple. just use the following command:
	# make server
	# make client

2: [server] = main server
	#./server 1 
			: run server with unique id 1
3.[bkup1] => backup server 1
	#./server 2 
			:  run server with unique id 2

4.[bkup2] => backup server 2
	#./server 3 
			:  run server with unique id 3

5: client execution:
	a: [usage] ./client [IP] [port] [num_req] [table_type] [operation]
			--> IP = 127.0.0.1 or 127.0.0.2 or 127.0.0.3
			--> port = 2474
			--> num req is the id for data query from 1 to num_req
			--> table type = 1-hosp 2-doc 3-patient 4-pat_log
			--> operation = 1= read 3-update

