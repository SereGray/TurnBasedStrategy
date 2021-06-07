#include"utility.h"

// TODO: add throw (not found exception!)
template<typename T>
inline T GetObjFromVectorUt(unsigned by_id, std::vector<T>& list_obj)
{
	auto it = std::find_if(list_obj.begin(), list_obj.end(), [by_id](T& obj_from_vector) {if (obj_from_vector.GetMyId() == by_id)return true; return false; });
	return *it;
}