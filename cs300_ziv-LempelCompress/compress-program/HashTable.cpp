#include <vector>
#include <string>
		
//hash function for strings
template <class Value>
unsigned int Hash(const Value& s,int size) {
    // Initialize the hash value to a prime number

	
	unsigned int hash = 3;

	// Iterate through the characters in the string
	for(unsigned char c : s) {
		// Update the hash value using the current character  -Hashing with horner method
		hash = (hash * 31) + c;
	}
	// Return the final hash value
	hash = hash % size;
	return hash;
}
template <class Key, class Value>
        class HashTable
        {
          public:
            explicit HashTable( const Key & notFound, int size = 256 );

            HashTable( const HashTable & rhs ) : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ) { }

            const Key find( const Value & x ) const;

            void makeEmpty( );
            void insert(const Key  & , const Value & );
            void remove( const Value & );
			
            const HashTable & operator=( const HashTable & rhs );

            enum EntryType { ACTIVE, EMPTY, DELETED };
private:
            struct HashEntry
            {
                Key code;
                Value value;  
                EntryType info;

                HashEntry( Key c = Key(),const Value & v = Value(), EntryType i = EMPTY )
                  : code(c),value(v), info( i ) { }
            };
            const Key ITEM_NOT_FOUND;
            std::vector<HashEntry> array;
            

            bool isActive( int ) const;
            int findPos( const Value &  ) const;
         
        };
		/**
         * Construct the hash table.
         */
        template <class Key, class Value>
        HashTable<Key,Value>::HashTable( const Key & notFound, int size )
          : ITEM_NOT_FOUND( notFound ), array( size  )
        {
            makeEmpty( );
        }
/**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class Key, class Value>
        int HashTable<Key,Value>::findPos( const Value & x ) const
        {
               int i = 0;   // number of collusions
			   
		       unsigned int p = Hash(x,array.size()); // current position

               while( array[ p ].info != EMPTY && array[ p ].value != x ) {

                   p += 2 * ++i -1 ;// add the difference

                   if(p >= array.size()){// perform the mod
					   p -= array.size();// if necessary
				   }
			   }
			   return p;
		}
		/**
         * Return true if currentPos exists and is active.
         */
        template <class Key, class Value>
        bool HashTable<Key,Value>::isActive( int currentPos ) const
        {
            return array[ currentPos ].info == ACTIVE;
        }
/**
         * Remove item x from the hash table.
         *  x has to be in the table
         */
        template <class Key, class Value>
		void HashTable<Key,Value>::remove( const Value & val )
        {
            int currentPos = findPos( val );

            if( isActive( currentPos ) )
                array[ currentPos ].info = DELETED;
        }



/**
         * Make the hash table logically empty.
         */
        template <class Key, class Value>
        void HashTable<Key,Value>::makeEmpty( )
        {
            for(unsigned int i = 0; i < array.size(); i++ )
				array[i].info= EMPTY;
        }

		/**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class Key, class Value>
        const Key HashTable<Key,Value>::find( const Value & x ) const
        {
            int currentPos = findPos( x );

            if (isActive( currentPos )) 
               return array[ currentPos ].code; 
 
            return   ITEM_NOT_FOUND;
        }
/**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class Key, class Value>
        void HashTable<Key,Value>::insert( const Key & cod ,const Value & val)
        {
			// Insert x as active
            int currentPos = findPos( val );
			
			if( isActive( currentPos ))
				return;
			
			array[ currentPos ] = HashEntry(cod, val, ACTIVE );
			
		
	}
	