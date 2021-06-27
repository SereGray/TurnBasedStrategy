#ifndef UTILITY
#define UTILITY
#include<vector>
#include<string>

class VectorUtException {
	std::string error_;
public:
	VectorUtException(std::string error): error_(error) {};
	const char* what() const noexcept { return error_.c_str(); }
};

template<typename T>
T* GetObjFromVectorUt(unsigned by_id, std::vector<T>& list_obj)
{
	auto it = std::find_if(list_obj.begin(), list_obj.end(), [by_id](T& obj_from_vector) {if (obj_from_vector.GetMyId() == by_id)return true; return false; });
	if (it == list_obj.end()) throw VectorUtException("not find");
	return &(*it);
}

#endif // UTILITY
