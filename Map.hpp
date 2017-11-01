#pragma once
#include <vector>
#include <stdexcept>

namespace util
{
	template <typename KeyType, typename ValueType>
	class Map
	{

	public:
		class Wrapper
		{
		public:
			//this is a type cast operator that can be used to cast an object
			//of type Wrapper to an object of type ValueType
			operator ValueType&();
			ValueType* operator &();
			const ValueType& operator =(const ValueType& rValue);

		private:
			Wrapper(Map &map, const KeyType &key);
			Wrapper(const Wrapper & value);
			Map& map;
			KeyType key;
			ValueType* value;

			friend class Map;
		};

		Wrapper operator[](const KeyType& key);
		unsigned size();

		class Iterator
		{
			public:
				void operator++();
				Iterator operator++(int);
				void operator--();
				Iterator operator--(int);
				ValueType& operator*();
			private:
				Iterator(Map&);
				Map& map;
				int index;
				
				friend class Map;
		};

		class IVisitor
		{
			public:
				virtual void visit(KeyType&, ValueType&) = 0;
		};
		Iterator getIterator(KeyType);
		void visit(IVisitor&);
	private:
		std::vector<KeyType> keys;
		std::vector<ValueType> values;

		ValueType* find(const KeyType &key);
		ValueType* set(const KeyType &key, const ValueType &value);
	};

	/*==========================================================================
	* Map class methods
	*/

	template <typename KeyType, typename ValueType>
	typename Map<KeyType, ValueType>::Wrapper Map<KeyType, ValueType>::operator[](const KeyType& key)
	{
		Wrapper wrapper(*this, key);
		return wrapper;
	}

	template <typename KeyType, typename ValueType>
	unsigned Map<KeyType, ValueType>::size()
	{
		return keys.size();
	}

	template <typename KeyType, typename ValueType>
	ValueType* Map<KeyType, ValueType>::find(const KeyType &key)
	{
		bool keyInList = false;
		int keyIndex = 0;
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				keyInList = true;
				keyIndex = i;
			}
		}

		ValueType* result = NULL;
		if (keyInList)
		{
			result = &values[keyIndex];
		}
		return result;
	}

	template <typename KeyType, typename ValueType>
	ValueType* Map<KeyType, ValueType>::set(const KeyType &key, const ValueType &value)
	{
		bool keyInList = false;
		int keyIndex = 0;
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				keyInList = true;
				keyIndex = i;
			}
		}
		
		ValueType* valueAddress;
		if (keyInList)
		{
			values[keyIndex] = value;
			valueAddress = &(values[keyIndex]);
		}
		else
		{
			keys.push_back(key);
			values.push_back(value);
			valueAddress = &(values[values.size() - 1]);
		}

		return valueAddress;
	}

	template <typename KeyType, typename ValueType>
	typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::getIterator(KeyType key)
	{
		if (this->find(key))
		{
			Iterator iterator(*this);
			int keyIndex;
			for (int i = 0; i < keys.size(); i++)
			{
				if (keys[i] == key)
				{
					keyIndex = i;
				}
			}
			iterator.index = keyIndex;
			return iterator;
		}
		else
		{
			throw std::range_error("Key not found in map");
		}
	}

	template <typename KeyType, typename ValueType>
	void Map<KeyType, ValueType>::visit(IVisitor& visitor)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			visitor.visit(keys[i], values[i]);
		}
	}

	/*==========================================================================
	* Wrapper methods
	*/

	template <typename KeyType, typename ValueType>
	Map<KeyType, ValueType>::Wrapper::Wrapper(Map &map, const KeyType &key) : map(map), key(key)
	{
		value = map.find(key);
	}

	//Copy constructor
	template <typename KeyType, typename ValueType>
	Map<KeyType, ValueType>::Wrapper::Wrapper(const Wrapper& rValue) : map(rValue.map), key(rValue.key), value(rValue.value)
	{
		//in the member initialization list - set the map, the key, and the value
		//members to the values passed to the constructor
	}

	//conversion operator, from a Wrapper to a ValueType
	template <typename KeyType, typename ValueType>
	Map<KeyType, ValueType>::Wrapper::operator ValueType&()
	{
		if (value == NULL)
		{
			throw std::range_error("Key not found in map");
		}
		else
		{
			return *value;
		}
	}

	//address of operator. This is used when the programmer tries to 
	//find the address of a Wrapper object.  We return the address of the
	//value inside the wrapper instead.
	template <typename KeyType, typename ValueType>
	ValueType* Map<KeyType, ValueType>::Wrapper::operator &()
	{
		if (value == NULL)
		{
			throw std::range_error("Key not found in map");
		}
		else
		{
			return value;
		}
	}

	//assignment operator.  This is used when a wrapper is the l-value in an assignment 
	//and the r-value is of type ValueType
	template <typename KeyType, typename ValueType>
	const ValueType& Map<KeyType, ValueType>::Wrapper::operator =(const ValueType& rValue)
	{
		if (value == NULL)
		{
			value = map.set(key, rValue);
		}
		else
		{
			*value = rValue;
		}
		return rValue;
	}

	/*==========================================================================
	* Iterator methods
	*/
	template <typename KeyType, typename ValueType>
	Map<KeyType, ValueType>::Iterator::Iterator(Map& map) : map(map)
	{

	}

	template <typename KeyType, typename ValueType>
	void Map<KeyType, ValueType>::Iterator::operator++()
	{
		if (index == map.size() - 1)
		{
			index == 0;
		}
		else
		{
			index++;
		}
	}

	template <typename KeyType, typename ValueType>
	typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::Iterator::operator++(int junk)
	{
		Iterator pastIterator = *this;
		if (index == map.size() - 1)
		{
			index = 0;
		}
		else
		{
			index++;
		}
		return pastIterator;
	}

	template <typename KeyType, typename ValueType>
	void Map<KeyType, ValueType>::Iterator::operator--()
	{
		if (index == 0)
		{
			index = map.size() - 1;
		}
		else
		{
			index--;
		}
	}

	template <typename KeyType, typename ValueType>
	typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::Iterator::operator--(int junk)
	{
		Iterator pastIterator = *this;
		if (index == 0)
		{
			index = map.size() - 1;
		}
		else
		{
			index--;
		}
		return pastIterator;
	}

	template <typename KeyType, typename ValueType>
	ValueType& Map<KeyType, ValueType>::Iterator::operator*()
	{
		return map.values[index];
	}
}	
