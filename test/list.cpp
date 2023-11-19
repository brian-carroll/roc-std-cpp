#include "list.h"
#include "alloc.h"
#include "lib/simpletest.h"

/*

    #[test]
    fn reserve_small_list() {
        let mut roc_list = RocList::<RocStr>::empty();

        roc_list.reserve(42);

        assert_eq!(roc_list.capacity(), 42);
    }

    #[test]
    fn reserve_big_list() {
        let mut roc_list = RocList::<RocStr>::empty();

        roc_list.reserve(5000);

        assert_eq!(roc_list.capacity(), 5000);
    }

    #[test]
    #[cfg(feature = "serde")]
    fn short_list_roundtrip() {
        let items: [u8; 4] = [1, 3, 3, 7];
        let orig = RocList::from_slice(&items);

        let serialized = serde_json::to_string(&orig).expect("failed to serialize string");
        let deserialized =
            serde_json::from_str::<RocList<u8>>(&serialized).expect("failed to deserialize string");

        assert_eq!(orig, deserialized);
    }

    #[test]
    #[cfg(feature = "serde")]
    fn long_list_roundtrip() {
        let orig = RocList::from_iter(1..100);

        let serialized = serde_json::to_string(&orig).expect("failed to serialize string");
        let deserialized =
            serde_json::from_str::<RocList<u8>>(&serialized).expect("failed to deserialize string");

        assert_eq!(orig, deserialized);
    }

    #[test]
    fn list_from_iter() {
        let elems: [i64; 5] = [1, 2, 3, 4, 5];
        let from_slice = RocList::from_slice(&elems);
        let from_iter = RocList::from_iter(elems);
        assert_eq!(from_iter, from_slice);
        assert_eq!(from_iter.capacity(), from_slice.capacity());
    }

    #[test]
    fn list_from_iter_zero_size() {
        let elems: [(); 5] = [(), (), (), (), ()];
        let from_slice = RocList::from_slice(&elems);
        let from_iter = RocList::from_iter(elems);
        assert_eq!(from_iter, from_slice);
    }

    #[test]
    fn list_from_array() {
        let elems: [i64; 5] = [1, 2, 3, 4, 5];
        let from_slice = RocList::from_slice(&elems);
        let from_array = RocList::from(elems);
        assert_eq!(from_array, from_slice);
        assert_eq!(from_array.capacity(), from_slice.capacity());
    }

    #[test]
    fn list_from_array_zero_size() {
        let elems: [(); 5] = [(), (), (), (), ()];
        let from_slice = RocList::from_slice(&elems);
        let from_array = RocList::from(elems);
        assert_eq!(from_array, from_slice);
        assert_eq!(from_array.capacity(), from_slice.capacity());
    }
*/