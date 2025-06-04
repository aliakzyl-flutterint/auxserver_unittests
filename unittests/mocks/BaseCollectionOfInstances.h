
#include <list>
#include <algorithm>

// Curiously recurring template pattern
template <class T>
class BaseCollectionOfInstances
{
	static std::list<T*> instances;
public:
	BaseCollectionOfInstances() {
		instances.push_front(static_cast<T*>(this));
	}
	virtual ~BaseCollectionOfInstances() {
		auto it = std::find(instances.begin(), instances.end(), static_cast<T*>(this));
		instances.erase(it);
	}
	
	static T* getLastCreatedObject() {
		return ((instances.size()) ? (*instances.begin()) : (nullptr));
	}
	
	static const std::list<T*>& getAllCreatedObjects() {
		return instances;
	}
};

template <class T>
std::list<T*> BaseCollectionOfInstances<T>::instances;
