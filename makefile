assign : assign.c threads.c
	@gcc assign.c threads.c -g -o assign

clean: 
	@rm assign
