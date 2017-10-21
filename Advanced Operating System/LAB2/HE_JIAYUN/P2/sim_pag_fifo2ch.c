/*
    sim_pag_fifo2ch.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sim_paging.h"

// Function that initialises the tables

void init_tables (ssystem * S)
{
    int i;

    // Reset pages
    memset (S->pgt, 0, sizeof(spage)*S->numpags);

    // Empty LRU stack
    S->lru = -1;

    // Reset LRU(t) time
    S->clock = 0;

    // Circular list of free frames
    for (i=0; i<S->numframes-1; i++)
    {
        S->frt[i].page = -1;
        S->frt[i].next = i+1;
    }

    S->frt[i].page = -1;    // Now i == numframes-1
    S->frt[i].next = 0;     // Close circular list
    S->listfree = i;        // Point to the last one

    // Empty circular list of occupied frames
    S->listoccupied = -1;
}

// Functions that simulate the hardware of the MMU

unsigned sim_mmu (ssystem * S, unsigned virtual_addr, char op)
{
    unsigned physical_addr;
    int page, frame, offset;
	
	page = virtual_addr / S->pagsz; //Quotient
	offset = virtual_addr % S->pagsz;
	if (page < 0 || page>=S->numpags)
	{
		S->numillegalrefs ++;
		return ~0U;
	}

	if(!S->pgt[page].present)
		handle_page_fault(S,virtual_addr);
	
	//Now is present 

	frame = S->pgt[page].frame;
	physical_addr = frame * S->pagsz+offset;

	reference_page(S,page,op);

	if(S->detailed)
		printf("\t%c %u==P%d(M%d)+%d\n",op,virtual_addr,page,frame,offset);

    return physical_addr;
}

void reference_page (ssystem * S, int page, char op)
{
    S->pgt[page].referenced = '1';       // set the reference bit to 1
    if (op=='R')                         // If it's a read,
        S->numrefsread ++;               // count it
    else if (op=='W')
    {                                    // If it's a write,
        S->pgt[page].modified = 1;       // count it and mark the
        S->numrefswrite ++;              // page 'modified'
    }
}

// Functions that simulate the operating system

void handle_page_fault (ssystem * S, unsigned virtual_addr)
{
    int page, victim, frame, last;

	S->numpagefaults++;
	page = virtual_addr / S->pagsz;

	if(S->detailed)
		printf("@ PAGE FAULT in P%d!\n",page);
	
	
	if(S->listfree!=-1) //If there are free frames
	{
		last = S->listfree;
		frame = S->frt[last].next; //allocate the first frame in the list

		if(frame == last){
			S->listfree = -1;
			S->frt[last].next = 0; //restore the pointer
		}

		else
			S->frt[last].next = S->frt[frame].next;

		occupy_free_frame(S,frame,page);
	}

	else
	{
		victim = choose_page_to_be_replaced(S);

		replace_page(S,victim,page);
	}

}

int choose_page_to_be_replaced (ssystem * S)
{
	int victim_frame, victim, tmpvictim; //
	while(1){
		//Begin traverse the list from the first element
		S->listoccupied = S->frt[S->listoccupied].next;
		tmpvictim = S->frt[S->listoccupied].page;
		//Pick the one as the victim if it's reference bit is 0
		if(S->pgt[tmpvictim].referenced != '1'){
			victim = tmpvictim;
			victim_frame = S->listoccupied;
			break;
		}
		//if not, set the refernce bit to 0.
		else{
			S->pgt[tmpvictim].referenced = '0';
			continue;
		}
	}
		
    	if (S->detailed)
        	printf ("@ Choosing (FIFO2ch) P%d of F%d to be " 	
            	        "replaced\n", victim, victim_frame);

    return victim;
}

void replace_page (ssystem * S, int victim, int newpage)
{
    int frame;

    frame = S->pgt[victim].frame;

    if (S->pgt[victim].modified)
    {
        if (S->detailed)
            printf ("@ Writing modified P%d back (to disc) to "
                    "replace it\n", victim);

        S->numpgwriteback ++;
    }

    if (S->detailed)
        printf ("@ Replacing victim P%d with P%d in F%d\n",
                victim, newpage, frame);

    S->pgt[victim].present = 0;

    S->pgt[newpage].present = 1;
    S->pgt[newpage].frame = frame;
    S->pgt[newpage].modified = 0;

    S->frt[frame].page = newpage;
}

void occupy_free_frame (ssystem * S, int frame, int page)
{
        if (S->detailed)
        printf ("@ Storing P%d in F%d\n", page, frame);
  	//At the beginning when there is no occupied frame
    	S->listoccupied = frame;  //set the listoccupied points to the new added element
	S->frt[frame].page = page;  //modifies the corresponding field in the newly 
	S->pgt[page].frame = frame; //occupied frame and in page table
	S->pgt[page].present = 1;

}  

// Functions that show results

void print_page_table (ssystem * S)
{
    int p;

    printf ("%10s %10s %10s   %s   %s\n",
            "PAGE", "Present", "Frame", "Modified", "Reference bit");

    for (p=0; p<S->numpags; p++)
        if (S->pgt[p].present)
            printf ("%8d   %6d     %8d   %6d    %10c\n", p,
                    S->pgt[p].present, S->pgt[p].frame,
                    S->pgt[p].modified,S->pgt[p].referenced);
        else
            printf ("%8d   %6d     %8s   %6s    %10s\n", p,
                    S->pgt[p].present, "-", "-","-");
}

void print_frames_table (ssystem * S)
{
    int p, f;

    printf ("%10s %10s %10s %10s %15s\n",
            "FRAME", "Page", "Present", "Modified","Reference bit");

    for (f=0; f<S->numframes; f++)
    {
        p = S->frt[f].page;

        if (p==-1)
            printf ("%8d   %8s   %6s   %s   %s\n", f, "-", "-", "-","-");
        else if (S->pgt[p].present)
            printf ("%8d   %8d   %6d     %6d   %10c\n", f, p,
                    S->pgt[p].present, S->pgt[p].modified, S->pgt[p].referenced);
        else
            printf ("%8d   %8d   %6d     %6s   ERROR!\n", f, p,
                    S->pgt[p].present, "-");
    }
}

void print_replacement_report (ssystem * S)
{
	int f,p;
	printf("%8s   %8s   %10s\n", "FRAME", "PAGE", "Reference bit");
	for (f = 0; f < S->numframes-1; f++){
		p = S->frt[f].page;
		printf("%8d   %8d   %10c\n", f, p, S->pgt[p].referenced);
	}
}


