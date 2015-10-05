1. The graph is represent by an adjacency list data structure.

2. The binary(graphs) reads  the no of nodes and the txt files as inputs.
   To run the code:
   	make clean && make
	./graphs 6 graph2_noloop.txt	

3. Representation of graphs as text files
	a. The no of rows in the files is the total number of nodes in the graph
	b. The first column is the node index, starting from index 0. for eg if there are five nodes in graph, it will be 0,1,2,3,4
	c. Next to the node index in each row, are the neighbors seperated(strictly) by a single space.
	d. To create new graphs, you can refer to examples present in the folder(graph1_noloop.txt  graph2_noloop.txt  graph3_loop.txt)
	
IMPORTANT: THE API TO READ THE GRAPH STRICTLY ASSUMES THAT NODES ARE SEPERATED BY SINGLE SPACES ONLY IN THE TEXT FILES
	   IF YOU ARE CREATING NEW GRAPHS TO TEST THE BINARY, PLEASE MAKE SURE THAT ALL THE INPUTS ARE SEPERATED BY SINGLE SPACE
	   WITH NO LEADING/TRAILING SPACES IN THE FILE.

4. Question 1 and 3 are taken care by function max_path_len_loop:graphs.c
   To view the difference in code for ques 1 and 3, compare the functions max_path_len_loop() and max_path_len_no_loop()

5. For Question 2 (review comments) , below would be my criteria before I approve the code for check-in

	 I would do a code-walkthrough checking for follwing
       		- core algo logic 
		   - would DFS work here? , Why not BFS ? etc
	           - Any corner cases that I might have missed?
		   - Problem statement/constraints 
		      	During the design phase itself , i would ask questions like
		        are -ve edge lengths allowed ?, can we have positive edge len other than 1? can we have -ve loops ?
			Is extra mem a concern? Between tradeoff of memory and speed, which one is critical for us going forward ?

		   - If the graphs has millions of nodes, then using recursion would BOMB the code.(basically 
		     stack overflow). This should be clarified right at the design phase. If we know in advance
		     there there is no limit to the number of nodes, then we have to go with application level
		     stacks instead of recursion.
		   - error checking with meaningful error messages.

		- readability and maintainibily
		   - Look for proper indentation/spacing
		   - appropraite variables/functions name
		   - adding appropriate comments(I personally consider this very important)
    		   - check if the coding convention used is consistent across files
		   - Language specific checks (eg in C): try to minimize use of externs(if uses), 
		   					  macros side effects, too many inline functions etc
		   - structure declaration/alignments in terms of space efficiency
		   - is the code modular? This is an important aspect of code maintainability.						  

    		- memory leaks
		   Though this is language dependent, being a systems programmer, i would try to 
		   throughly review the logic to check if there are memory leaks. Would do lot of
		   unit testing(if this is my code) using Valgrind to be 100% sure.


		- scalability 
	 	  - what if tommorrow we need to scale this code to support million of nodes( assuming 
	            today there is a limit to scalabilty aspect)? I would try to identify the pain points
		    while designing(apart from recursion). for eg
		  	- would I design data structures differenty? Like using some void * to allow more flexibility?
			 or declaring some function pointers to introduce callback/event based mechanisms later?
			- Do I need to declare variables differently? For eg: keeping in mind of int overflow.
	                - Are we segregating the core functionlity with the general utilities?For eg we can easily
			  enhance graph_utils.c further without touching the existing code(graphs.c).		

	        - optimization :
		  - would try to check if there is any scope for code optimization
		  	- Do we need to decalare int variables if we just do it with a bit?
			- Can we use Unions instead of structures?
			- Is there a dead or redundent code ? Can we club the code togther?
			- Can we modify our data structures to optimize the code ? for eg 
			  I have added "processed" and "dist" as part of node structure to 
			  avoid iteration.
			- Can we reduce the number of system calls() to reduce context switch ?
			 (Though this may not be applicable here)
    			- Deciding what task should be done on main thread and what task can be
			  offloaded to worker threads in case of multithreaded enviromment.



