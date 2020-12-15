/* An element of a doubly linked list
 */
template <class T>
class DLListElement {
	public:
		/* Creates a doubly linked list element with the previous and next elements set
		 */
		DLListElement(T v, DLListElement<T>* p, DLListElement<T>* n) {
			value = v;
			previous = p;
			next = n;
		}
		
		/* Creates a doubly linked list element without the previous and next elements set
         */
		DLListElement(T v) {
			value = v;
			previous = NULL;
			next = NULL;
		}
		
		/* Sets the next element of the list element
		 */
		void set_next(DLListElement<T>* n) {
			next = n;
		}
		
		/* Returns the next element of the list element
		 */
		DLListElement<T>* get_next() {
			return next;
		}
		
		/* Sets the previous element of the list element
		 */
		void set_previous(DLListElement<T>* p) {
			previous = p;
		}
		
		/* Returns the previous element of the list element
		 */
		DLListElement<T>* get_previous() {
			return previous;
		}
		
		/* Sets the value of the list element
		 */
		void set_value(T v) {
			value = v;
		}
		
		/* Returns the list element's value
		 */
		T get_value() {
			return value;
		}
	
	private:
		DLListElement<T>* previous;
		DLListElement<T>* next;
		T value;
};

/* A doubly linked list
   Contains doubly linked list elements
 */
template <class T>
class DoublyLinkedList {
	public:
		/* Creates a doubly linked list containing the elements in the array
		 */
		DoublyLinkedList(T values[], int length) {
			first = NULL;
			last = NULL;
			iterator = NULL;
			size = 0;
			
			for (int i = 0; i < length; i++) {
				append(values[i]);
			}
		}
		
		/* Creates a singleton doubly linked list
		 */
		DoublyLinkedList(T value) {
			first = new DLListElement<T>(value);
			last = first;
			iterator = NULL;
			size = 1;
		}
		
	    /* Creates an empty doubly linked list
		 */
		DoublyLinkedList() {
			first = NULL;
			last = NULL;
			iterator = NULL;
			size = 0;
		}
		
		/* Deallocates the memory for each doubly linked list element before destruction
		 */
		~DoublyLinkedList() {
			remove_all();
		}
		
		/* Inserts a value at the end of the list
		 */
		void append(T value) {
			if (size) {
				last->set_next(new DLListElement<T>(value, last, NULL));
				last = last->get_next();
				size++;
			}
			
			else {
				first = new DLListElement<T>(value);
				last = first;
				size++;
			}
		}
		
		/* Inserts a value at the start of the list
		 */
		void prepend(T value) {
			if (size) {
				first->set_previous(new DLListElement<T>(value, NULL, first));
				first = first->get_previous();
				size++;
			}
			
			else {
				first = new DLListElement<T>(value);
				last = first;
				size++;
			}
		}
		
		/* Inserts a value at the desired index
		   Indices that are out of range prepend or append the value
		 */
		void insert(T value, int index) {
			// An index of zero or less prepends
			if (index < 1) {
				prepend(value);
			}
			
			// An index of size or greater appends
			else if (index >= size) {
				append(value);
			}
			
			// The elements either side of the new element are found
			// Iterates from the start for small indices
			else if (index < size / 2) {
				DLListElement<T>* previous = first;
				
				for (int i = 0; i < index - 1; i++) {
					previous = previous->get_next();
				}
				
				DLListElement<T>* next = previous->get_next();
				previous->set_next(new DLListElement<T>(value, previous, next));
				next->set_previous(previous->get_next());
				size++;
			}
			
			// Iterates from the end for large indices
			else {
				DLListElement<T>* next = last;
				
				for (int i = size - 1; i > index; i--) {
					next = next->get_previous();
				}
				
				DLListElement<T>* previous = next->get_previous();
				next->set_previous(new DLListElement<T>(value, previous, next));
				previous->set_next(next->get_previous());
				size++;
			}
		}
		
		/* Removes the value at the desired index
		   Removal indices that are out of range are ignored
		   Returns the value removed
		 */
		T remove(int index) {
			if (index > -1 && index < size) {
				T removed;
				
				// The second element becomes the first and the first is removed
				if (index == 0) {
					removed = first->get_value();
					
					// If the list is to be emptied, a different procedure is followed
					if (size == 1) {
						delete first;
						first = NULL;
						last = NULL;
					}
					
					else {
						first = first->get_next();
						delete first->get_previous();
						first->set_previous(NULL);
					}
				}
				
				// The second last element becomes the last and the last is removed
				else if (index == size - 1) {
					removed = last->get_value();
					last = last->get_previous();
					delete last->get_next();
					last->set_next(NULL);
				}
				
				// The elements either side of the removed element are found
				// Iterates from the start for small indices
				else if (index < size / 2) {
					DLListElement<T>* previous = first;
					
					for (int i = 0; i < index - 1; i++) {
						previous = previous->get_next();
					}
					
					DLListElement<T>* next = previous->get_next()->get_next();
					removed = previous->get_next()->get_value();
					delete previous->get_next();
					previous->set_next(next);
					next->set_previous(previous);
				}
				
				// Iterates from the end for large indices
				else {
					DLListElement<T>* next = last;
					
					for (int i = size - 1; i > index + 1; i--) {
						next = next->get_previous();
					}
					
					DLListElement<T>* previous = next->get_previous()->get_previous();
					removed = previous->get_next()->get_value();
					delete next->get_previous();
					next->set_previous(previous);
					previous->set_next(next);
				}
				
				size--;
				return removed;
			}
		}
		
		/* Empties the list
		 */
		void remove_all() {
			while (size) {
				remove(0);
			}
		}
		
		/* Returns a value in the list, starting from the first.
		   The next time this method is called, the next value in the list is returned.
		   If the last value in the list is returned, the next call will return
		     the first element.
		   Should not be used when the list is empty.
	     */
		T iterate() {
			if (size) {
				if (iterator == NULL) {
					iterator = first;
				}
				
				T value = iterator->get_value();
				iterator = iterator->get_next();
				
				return value;
			}
		}
		
		/* Sets the iterator to NULL
		   This allows the iterate() method to be started from the first element
		     the next time it is called
		   Note that this it the first element from the point where iterate() is called,
		     not when reset_iterator() was called
		 */
		void reset_iterator() {
			iterator = NULL;
		}
		
	private:
		DLListElement<T>* first;
		DLListElement<T>* last;
		DLListElement<T>* iterator;
		int size;
};