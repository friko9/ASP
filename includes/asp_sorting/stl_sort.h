#ifndef STL_SORT_H
#define STL_SORT_H

template<typename T>
void stl_sort(std::vector<T>& v)
{
    std::sort(v.begin(), v.end());
}

template<typename T>
void stl_stable_sort(std::vector<T>& v)
{
    std::stable_sort(v.begin(), v.end());
}

template<typename T>
void stl_sort_indexing(std::vector<T>& v)
{
    if(v.size() <= 1) return;
    std::vector<T*> vp(v.size());
    std::vector<T> vres(v.size());
    T* x = v.data();
    for(auto it=vp.begin(),ite=vp.end();it!=ite;++it)
	*it = x++;
    std::sort(vp.begin(),vp.end(),[](T* p1,T* p2){ return *p1<*p2;});
    auto itv=vres.begin();
    for(auto it = vp.begin(); it != vp.end(); ++it,++itv)
	*itv = **it;
    v = std::move(vres);
}

template<typename T>
void stl_qsort_1(std::vector<T>& v)
{
    std::qsort(v.data(), v.size(), sizeof(T), [](const void* a,const void* b)
	       {
		   if(*(T*)a<*(T*)b) return -1;
		   if(*(T*)b<*(T*)a) return 1;
		   return 0;
	       });
}

template<typename T>
void stl_qsort_2(std::vector<T>& v)
{
    std::qsort(v.data(), v.size(), sizeof(T), [](const void* a,const void* b)
	       {
		   bool b_gt_a = *(T*)a < *(T*)b;
		   bool a_gt_b = *(T*)b < *(T*)a;
		   return a_gt_b - b_gt_a;
	       });
}

#endif /*STL_SORT_H*/
