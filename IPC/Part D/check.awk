BEGIN {
	customer_done = 0;
	occupied = 0;
	for(i = 0; i < CUSTOMER; i++)
		status[i] = 0; #not arrived
}

{
    if ($1 == "Customer" && $2 < CUSTOMER) {
    	if( $3 == "arrived"){
    		if(status[$2] == 0)
    			status[$2] = 1;	#arrived
    	}else if($4 == "waiting."){
    		if(status[$2] == 1){
    			status[$2] = 2; #waiting
				occupied++;
			}
		}else if($4 == "getting"){
			if(status[$2] == 2)
    			status[$2] = 3; #haircut
		}else if($4 == "leaving"){
			if(status[$2] == 3){
				status[$2] = 4; #done
				customer_done++;
				occupied--;
			}
		}
    }
    else if ($1 == "All" && $2 == "chairs" && $6 < CUSTOMER) {
		if(status[$6] == 1){
			customer_done++;
			status[$6] = 4;
		}
    }else if( $1 == "No" && occupied > 0){
		#customer_done = -1;
	}
    
}

END {
	for(i = 0; i < CUSTOMER; i++){
		if(status[i] != 4){
			printf("%d %d\n", CUSTOMER, CHAIR)
			printf("NOT LEFT %d %d\n", i, status[i]);
			exit(1);
		}
	}
	if (customer_done == CUSTOMER && occupied == 0) {
		printf("OK. All test cases passed!\n");
	}
	else {
		printf("Please check your code. %d customer is not done and %d occupied\n", CUSTOMER - customer_done, occupied);
	}
}
