#include <vector>
#include <string>

//hash f
template <class Key, class Value>
        class HashTable
        {
          public:
            explicit HashTable( const Value	& notFound, int size = 256 );

            HashTable( const HashTable & rhs ) : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ) { }

            const Value find( const Key & x ) const;

            void makeEmpty( );
            void insert(const Key  & , const Value & );
            void remove( const Key & );
			
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
            const Value ITEM_NOT_FOUND;
            std::vector<HashEntry> array;
            

            bool isActive( int ) const;
            int findPos( const Key &  ) const;
         
        };
		/**
         * Construct the hash table.
         */
        template <class Key, class Value>
        HashTable<Key,Value>::HashTable( const Value& notFound, int size )
          : ITEM_NOT_FOUND( notFound ), array( size  )
        {
            makeEmpty( );
        }
/**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class Key, class Value>
        int HashTable<Key,Value>::findPos( const Key & x ) const
        {
               int i = 0;   // number of collusions
			   
		       unsigned int p =  x % array.size();

               while( array[ p ].info != EMPTY && array[ p ].code!= x ) {

                   p += 2 * ++i -1 ;// add the difference

                   if(p >= array.size()){// perform the mod
					   p-= array.size();// if necessary
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
		void HashTable<Key,Value>::remove( const Key & cod)
        {
            int currentPos = findPos( cod );

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
        const Value HashTable<Key,Value>::find( const Key & x ) const
        {
            int currentPos = findPos( x );
            if (isActive( currentPos )) 
               return array[ currentPos ].value;
 
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
            int currentPos = findPos( cod );
			
			if( isActive( currentPos ))
				return;
			
			array[ currentPos ] = HashEntry(cod, val, ACTIVE );
			
		
	}