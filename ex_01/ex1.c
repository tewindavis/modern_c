#include <stdio.h>
#include <stdlib.h>


// Going to skip ahead a bit and use an address pointer here __shrug__
// // this will allow us to be memory efficient and do everything in-place
void swap_ints( int* a, int* b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


void merge_sort( int* List, size_t list_size){
	if( list_size > 1){ 
		// split and merge_sort sublists
		size_t list_split_index = (list_size / 2);
		merge_sort( List, list_split_index ); // first half of list
		merge_sort( (List + list_split_index), list_size - list_split_index);  // second half of list
	
		// merge sublists
		size_t first_runner = 0;
		size_t second_runner = list_split_index;

		while( first_runner < list_split_index && second_runner < list_size ){
			/*
			 * Loop Invariant: the list below 'first_runner' is sorted
			 */
			
			if( List[first_runner] > List[second_runner] ){
				
				// if out of order, swap 'em
				for( size_t k = second_runner; k > (first_runner); k--){
					swap_ints( List+k, List+k-1);
				}
				// then increment the runners and the split
				first_runner++;
				second_runner++;
				list_split_index++;
			} else {
				first_runner++;
			}

		}
	}

	return;
}

void quick_sort( int* List, size_t list_size ){
	if( list_size > 1){
		printf("%ld\n", list_size);
		// TODO: abstract the split method to function that can be chosen at execution time
		size_t splitter_index = list_size / 2;

		// Move the splitter to the end
		int* end_ptr = List+list_size-1;
		swap_ints( List+splitter_index, List+list_size-1 );
		
		// create runners
		size_t left_runner = 0;
		size_t right_runner = list_size-2;

		while( left_runner < right_runner ){
			while( List[left_runner] <= *end_ptr ){
				left_runner++;
			}
			while( List[right_runner] > *end_ptr ){
				right_runner--;
			}
			if( left_runner >= right_runner ) break;

			swap_ints( List+left_runner, List+right_runner );

		}

		swap_ints( List+right_runner, end_ptr);

		quick_sort( List, right_runner);
		quick_sort( List+right_runner, list_size - right_runner);

	}

}


int verify( int* List, size_t list_size ){
	for(size_t i = 0; i < list_size-1; i++){
		if( List[i] > List[i+1] ) return 1;
	}
	return 0;
}



int main( int argc, char* argv[argc + 1]){

	int A[9] = {
		[0] = 34,
		[1] = 1,
		[2] = 520,
		[3] = -27,
		[5] = 2,
		[8] = -540,
	};

	//merge_sort( A, 9);
	quick_sort( A, 9);
	for(size_t i = 0; i < 9; i++){
		printf("%d\t", A[i]);
	}
	printf("\n");
}
