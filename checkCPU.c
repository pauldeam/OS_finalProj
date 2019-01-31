#include "checkCPU.h"
#include "insertNode.h"

//this is a function for checking if the CPU is busy
//if not it puts the it will put the process in

int checkCPU(node *n){
  if(CPU == NULL){
   cpuflag = 0;
   if(n->arrival > time) time = n->arrival; 
    
    CPU = n;
    if(checkDev(CPU) == 1){
	CPU = NULL;
    	cpuflag = 1;
        readyhead = n->next;
        if(readyhead != NULL)checkCPU(readyhead);
    	return 0;}
    //process is comlete, delete node from ready queue
    readyhead = n->next;
    n->next = NULL;
    if(n->run <= quantum){
      time+=n->run;
      n->run = 0;
      
      //printf("Job %d completed, time = %d\n", n->job, time);
      n->comptime = time;
      fflush(stdout);
      
      insertFin(n);
      
      currentmem += n->mem;
      if(hq1head != NULL){
        node *t = hq1head;
	while(t != NULL){
	    if(currentmem >= t->mem){
	         insertReady(t);
	         hq1head = t->next;
	         break;
	    }
	    t = t->next;
	}
      }
      else if(hq2head != NULL){
        node *l = hq2head;
	while(l != NULL){
	    if(currentmem >= l->mem){
	         insertReady(l);
	         hq2head = l->next;
	         break;
	    }
	    l= l->next;
	}
      }
      
      //readyhead = n->next;
      
      CPU=NULL;
      cpuflag = 1;
    }
    //process isn't complete, gets time on CPU
    else{
      
      n->run -= quantum; 
      time+=quantum;
      //printf("Job %d has %d s left, times = %d\n\n", n->job, n->run, time);
      fflush(stdout);
      CPU=NULL;
      //insertReady(n);
      node *tmp = readyhead;
      if(readyhead == NULL)readyhead = n;
      else{
          while(tmp->next != NULL){
	       tmp = tmp->next;  
          }
          tmp->next = n;
	  }
      cpuflag = 1;
      if(readyhead!=NULL)printQ(readyhead);
      return 1;
    } 
    return 1;
  }
  else{
    printf("CPU busy\n");
    return 1;
  }
}
int checkDev(node *n){

  //printQ(devqhead);
    node *fintmp = finished;
  if(fintmp != NULL){
  
  node *devtmp = devqhead;
  while(fintmp != NULL){
    while(devtmp != NULL){
  
	if((fintmp->job == devtmp->job)){ 
	    
	    int devarr = devtmp->arrival;
	    int check = fintmp->comptime - devarr; //finished comptime - dev arrival time
	    if((check <=quantum) && (check >= 0)){
		if(devtmp->instruction == 'Q'){
	        fintmp->run += check;
                time-=check;
                if(currentmem >= devtmp->device) currentmem -= devtmp->device;
		}
		else if(devtmp->instruction == 'L'){
	        fintmp->run += check;
                time-=check;
		currentmem += devtmp->device;
		}
		node *newtmp = readyhead;
                while(newtmp->next!=NULL){
		    newtmp = newtmp->next;
		}
                fintmp->next = NULL;
		newtmp->next = fintmp;
		//printf("process %d back on ready\n", fintmp->job);
		node *newnew = devqhead;
		while(newnew!=NULL){
		    
		    if(newnew->next->job == fintmp->job){
			
		    newnew->next = newnew->next->next;
		    }
		    newnew = newnew->next;
		}
		
                //checkCPU(readyhead);
                return 10;
	    }
	}
	devtmp = devtmp->next;
	}//end while fintmp
    
    fintmp = fintmp->next;
    }// end while devtmp
   }



  node *tmp = devqhead;
  while(tmp != NULL){
  
    if(tmp->job == n->job){
	
       // printf("job %d tmp ins = %c\n", tmp->job, tmp->instruction);
        fflush(stdout);
        
    	if(tmp->instruction == 'Q'){ //request for devices, job specific
	    
	    if(currentdev >= tmp->device){
                //printf("request for devices went through, tmp->max = %d\n", tmp->device);
		fflush(stdout);
		currentdev -= tmp->device;
	       // printf("devs = %d\n", currentdev);
		int checktime = (time+n->arrival);
	        checktime = (time+quantum)-checktime;
      	 	if((checktime <=quantum) && (checktime >= 0)){
		    //time = time-checktime;
		    //n->run = n->run+checktime;
   		    //printf("job %d = %d\n", n->job, n->run);
		}
                return 0;
	    }
	}
	if(tmp->instruction == 'L'){ //release devices, job specific
	    
	   
                //printf("request for devices went through, tmp->max = %d\n", tmp->device);
		fflush(stdout);
		currentdev += tmp->device;
	        printf("devs = %d\n", currentdev);
		int checktime = (time+n->arrival);
	        checktime = (time+quantum)-checktime;
      	 	if((checktime <=quantum) && (checktime >= 0)){
		    //time = time-checktime;
		    //n->run = n->run+checktime;
   		    //printf("job %d = %d\n", n->job, n->run);
		    
		}
                return 1;
	    }
	
    }
    tmp = tmp->next;
  }//end while
  

    
return 0;

}// end checkDev(node * n){}

