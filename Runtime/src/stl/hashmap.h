//
// Created by allos on 8/29/2024.
//

#ifndef CATOS_HASHMAP_H
#define CATOS_HASHMAP_H

namespace catos {

    //std::exception kiss my ass >:(
    struct no_item_found {
        const char* what() {
            return "No Item found with that key\n";
        }
    };

    struct key_not_found {
        const char* what() {
            return "No Bucket found with that key\n";
        }
    };




    template<typename K, typename V>
    class hashnode {
    public:

        hashnode(const K& key, const V& value) : key(key), value(value) {}


        K getKey() const {
            return key;
        }

        V getValue() const {
            return value;
        }

        hashnode* getNext() const{
            return next;
        }

        void setValue(V newVal) {
            value = newVal;
        }

        void setNext(hashnode* newNext) {
            next = newNext;
        }

    private:
        K key;
        V value;
        hashnode* next = nullptr;

    };

    template<typename K>
    struct HashFunc {
        size_t operator()(const K& key, int Size) const {
            return static_cast<size_t>(key) % Size;
        }
    };


    template<typename K, typename V, typename F = HashFunc<K>>
    class hashmap {

    public:

        hashmap(int startSize = 8) : maxSize(startSize) {
            buf = new hashnode<K, V> * [startSize]();
        }

        ~hashmap() {
            for (int i=0; i<maxSize; i++) {

                // get the first bucket for the key / index.
                auto entry = buf[i];

                // loop through all off the buckets with the same key
                while (entry != nullptr) {

                    auto prev = entry;

                    // set the entry to the next bucket of the same bucket.
                    entry = entry->getNext();

                    // delete this bucket
                    delete prev;
                }

                buf[i] = nullptr;
            }

            //destroy the allocated buffer;
            delete[] buf;
        }


        V get(const K& key) {

            unsigned int index = hashFunc(key, maxSize);
            auto entry = buf[index];

            // loop through all of the buckets with the same hash until we found the right key.
            while (entry != nullptr) {
                if (entry->getKey() == key) {
                    return entry->getValue();
                }
                entry = entry->getNext();
            }

            // could not find item based on given key
            throw no_item_found{};
        }

        void put(const K& key, const V& value) {

            size++;

            if (size >= maxSize) {
                // rehash
            }

            int index = hashFunc(key, maxSize);
            hashnode<K, V>* prev = nullptr;
            auto entry = buf[index];

            // find an empty bucket that doenst have the same key.
            while (entry != nullptr && entry->getKey() != key) {
                prev = entry;
                entry = entry->getNext();
            }

            if (entry == nullptr) {
                entry = new hashnode<K, V>(key, value);
                if (prev == nullptr) {
                    buf[index] = entry;
                } else {
                    prev->setNext(entry);
                }
            } else {
                // fallback
                entry->setValue(value);
            }
        }

        void remove(const K& key) {

            //  should we?
            size--;

            int index = hashFunc(key, maxSize);
            hashnode<K, V>* prev = nullptr;
            auto entry = buf[index];

            // search for the right bucket with the correct key.
            while(entry != nullptr && entry->getKey() != key) {
                prev = entry;
                entry = entry->getNext();
            }

            if (entry == nullptr) {
                throw key_not_found{};
            } else {
                if (prev == nullptr) {
                    // remove the first bucket.
                    buf[index] = entry->getNext();
                } else {
                    prev->setValue(entry->getNext());
                }

                delete entry;
            }
        }

    private:

        F hashFunc;

        hashnode<K, V>** buf; // just an array of pointers to hashnodes<K, V>
        int size = 0;
        // NOTE everytime the maxSize changes we have REHASH EVERYTHING!!
        int maxSize = 0;

    };

}



#endif //CATOS_HASHMAP_H
