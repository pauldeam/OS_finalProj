#include "readFile.h"



int readFile(int argc, char *argv[]) {

  FILE *fp;
  cpuflag = 1;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
    return 1;
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    perror("fopen source-file");
    return 1;
  }
  flag = 1;

  while (fgets(buf, sizeof(buf), fp) != NULL) {

    char arr[10][20]; // used for getWord(buf, arr);
    getWords(buf, arr); //seperate each instruction line
    int arrival;
    arrival = atoi(arr[1]); // arrival time for each ins

    while (cpuflag == 0) {
    }
    buf[strlen(buf) - 1] = '\0'; // eat newline fgets() stores
    //printf("%s\n", buf);  //print instruction line

    if (buf[0] == 'A') {

      node *newnode = (node *)malloc(sizeof(struct node));
      newnode->instruction = buf[0];

      node *newnode2 = (node *)malloc(sizeof(struct node));
      newnode2->instruction = buf[0];

      newnode->arrival = arrival;
      // sets time equal to arrival-time when time is less than arrival-time
      newnode->job = getNum(arr[2]);
      newnode->mem = getNum(arr[3]);
      if (newnode->mem > totalmem)continue;
      newnode->max = getNum(arr[4]);
      if (newnode->max > totaldev)
        continue;
      newnode->run = getNum(arr[5]);
      newnode->pri = getNum(arr[6]);

      newnode2->arrival = arrival;

      newnode2->job = getNum(arr[2]);
      newnode2->mem = getNum(arr[3]);
      newnode2->max = getNum(arr[4]);
      newnode2->run = getNum(arr[5]);
      newnode2->pri = getNum(arr[6]);


      fflush(stdout);
      currentmem = (currentmem - newnode2->mem);
      
      
      fflush(stdout);

      // if theres enough resources in the system
      if ((currentmem >= 0)) { // insert into ready queue

        insertReady(newnode2);
        // checkCPU(newnode);

      } else {
        insertNode(newnode);
	currentmem += newnode->mem; // insert in hold queue
      }
	

    } // end 'A'

    if (buf[0] == 'C') {

      totalmem = getNum(arr[2]); // M
      totaldev = getNum(arr[3]); // S
      quantum = getNum(arr[4]);  // Q
      currentmem = totalmem;
      currentdev = totaldev;
      

      // initialize time
      time = 1;

    } // end 'C'

    if (buf[0] == 'Q') {

      node *newnode = (node *)malloc(sizeof(struct node));
      newnode->instruction = buf[0];

      newnode->arrival = arrival;

      newnode->job = getNum(arr[2]);
      newnode->device = getNum(arr[3]);
      insertdevnode(newnode);
      

    } // end 'Q'

    if (buf[0] == 'L') {

      node *newnode = (node *)malloc(sizeof(struct node));
      newnode->instruction = buf[0];

      newnode->arrival = arrival;

      newnode->job = getNum(arr[2]);
      newnode->device = getNum(arr[3]);
      insertdevnode(newnode);
      
      if (readyhead != NULL)
        checkCPU(readyhead);

    } // end 'L'
    if (buf[0] == 'D') {
	printf("%s\n", buf);
      node *newnode = (node *)malloc(sizeof(struct node));
      newnode->instruction = buf[0];
      
      if (arrival == 9999){
        flag = 0;
	checkCPU(readyhead);
	}
      else{
	    while(time < arrival){
		
	        if(readyhead!=NULL){
		
		checkCPU(readyhead);
	        
		}
		else if(readyhead==NULL){
		   // printf("broke\n");
		    break;
		}	    
	}
	printf("----------------------------------------------------------\n");
	
	/*Creating JSON files*/
	json_object *myObject;
	json_object *tmpArray;

	myObject = json_object_new_object();
	tmpArray = json_object_new_array();


	//ready queue status
	node *rtmp = readyhead;
	while(rtmp != NULL){
	    printf("Job %d in ready queue, %d time left\n", rtmp->job, rtmp->run);
	    json_object_object_add(myObject, "readyq", json_object_new_int(rtmp->job));
	    json_object_object_add(myObject, "remaining_time", json_object_new_int(rtmp->run));
	    rtmp = rtmp->next;
	}
        
	//cpu status
	if(CPU!=NULL){
		printf("job %d on cpu, %d time left\n",CPU->job, CPU->run);
		json_object_object_add(myObject, "running", json_object_new_int(CPU->job));
		json_object_object_add(myObject, "remaining_time", json_object_new_int(CPU->run));
	        

	}
	
	//hold queue 1 status
	node *h1tmp = hq1head;
	while(h1tmp != NULL){
	    printf("Job %d in hold queue 1, %d time left\n", h1tmp->job, h1tmp->run);
	    json_object_object_add(myObject, "holdq1", json_object_new_int(h1tmp->job));
	    json_object_object_add(myObject, "remaining_time", json_object_new_int(h1tmp->run));
	    h1tmp = h1tmp->next;   
	}


	//hold 2 queue
	node *h2tmp = hq2head;
	while(h2tmp != NULL){
	    printf("Job %d in hold queue 2, %d time left\n", h2tmp->job, h2tmp->run);
	    json_object_object_add(myObject, "holdq2", json_object_new_int(h2tmp->job));
	    json_object_object_add(myObject, "remaining_time", json_object_new_int(h2tmp->run));
	    h2tmp = h2tmp->next;   
	}

	
	//finished queue status
	node *fin = finished;
	while(fin != NULL){
	    int c = fin->comptime-arrival;
	    if((c <=quantum) && (c >= 0)){
	    printf("job %d on CPU, %d time left\n", fin->job, c);
	    json_object_object_add(myObject, "running", json_object_new_int(fin->job));
	    json_object_object_add(myObject, "remaining_time", json_object_new_int(c));
	    //for json, add fin->job to ready q json object with c as its runtime left
	    currentmem -= fin->mem;
	    m = fin->mem;
	    fin = fin->next; 
	    continue;
	    }
	    printf("Job %d finished at time %d \n", fin->job, fin->comptime);
	    json_object_array_add(tmpArray, json_object_new_int(fin->job));
	    json_object_object_add(myObject, "remaining_time", json_object_new_int(fin->comptime));
	    fin = fin->next; 
	}

	json_object_object_add(myObject, "completeq", tmpArray);

	json_object_object_add(myObject, "current_time", json_object_new_int(arrival));
	json_object_object_add(myObject, "total_memory", json_object_new_int(totalmem));
	json_object_object_add(myObject, "available_memory", json_object_new_int(currentmem));
	json_object_object_add(myObject, "total_devices", json_object_new_int(totaldev));
	json_object_object_add(myObject, "available_devices", json_object_new_int(currentdev));
	json_object_object_add(myObject, "quantum", json_object_new_int(quantum));

	printf("currentime = %d\n", arrival);
	printf("totalmem = %d\n", totalmem);
	printf("currentmem = %d\n", currentmem);
	printf("totaldev = %d\n", totaldev);
	printf("currentdev = %d\n", currentdev);
	printf("quantum = %d\n", quantum);
	currentmem += m;


	//outputing JSON file
	FILE * output = fopen("output.json", "w");
	fputs(json_object_to_json_string(myObject), output);
	fclose(output);

	json_object_put(outputArray);
	json_object_put(myObject);


	printf("------------------------------------------------------------\n");
	}
	
      }
      

    // sleep(1);
    //printf("TIME = %d \n", time);

  } // while

  fclose(fp);
  return 0;

} // end readFile
