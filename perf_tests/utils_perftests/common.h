#ifndef COMMON_H
#define COMMON_H

template<typename T_Subject,typename T_DataGenerator>
class PerformanceTester
{
    class setup_stage {
    protected: PerformanceTester& setup_data;
    protected: setup_stage(PerformanceTester& arg):setup_data(arg){}
    };
    struct setup_stage1 : private setup_stage    {
	using setup_stage(PerformanceTester&);
	setup_stage2 set_subjects(std::map<std::string,T_Subject>& arg);
	setup_stage2 set_subjects(std::map<std::string,T_Subject>&& arg);
    };
    struct setup_stage2 : private setup_stage    {
	using setup_stage(PerformanceTester&);
	setup_stage3 set_data_generators(std::map<std::string,T_DataGenerator>& arg);
	setup_stage3 set_data_generators(std::map<std::string,T_DataGenerator>&& arg);
    };
    struct setup_stage3 : private setup_stage    {
	using setup_stage(PerformanceTester&);
	setup_stage4 set_dataset_sizes(std::vector<size_t>& arg);
	setup_stage4 set_dataset_sizes(std::vector<size_t>&& arg);
    };
    struct setup_stage4 : private setup_stage    {
	using setup_stage(PerformanceTester&);
	operational_interface set_repetitions(size_t arg);
    };
    struct operational_interface : private setup_stage    {
	using setup_stage(PerformanceTester&);
	void run();
    };
public:
    setup_stage1 setup(){ return setup_stage1(*this); }
private:
    using timer_t = double;
    using timer_map_t = std::map<size_t,timer_t>;
    using elem_t = T_DataGenerator::result_type;
    std::map<std::string,timer_map_t > test_timers;
    std::map<std::string,T_Subject> subjects;
    std::map<std::string,T_DataGenerator> data_generators;
    std::map<size_t> dataset_sizes;
    size_t test_repetitions;
private:
    PerformanceTester() = default;
    void* operator new(size_t) = default;
    void* operator new(size_t,void*) = default;
private:
    template< typename T2>
    std::string get_name(std::pair<std::string,T2> arg){ return arg.first; }
    T_DataGenerator& get_generator(std::pair<std::string,T_DataGenerator>& arg){ return arg.second; }
    T_Subject& get_subject(std::pair<std::string,T_Subject>& arg){ return arg.second; }
    timer_map_t& get_timers(std::pair<std::string,timer_map_t>& arg){ return arg.second; }
};

template<typename T_S,typename T_DG>
inline
void
PerformanceTester<T_S,T_DG>::operational_interface::run()
{
    for( size_t i = 0; i < repetitions; ++i )
	for( auto generator : data_generators)
	    for( auto data_size : dataset_sizes )
	    {
		std::vector<elem_t> prepared_data(data_size);
		std::generate(vec.begin(), vec.end(), get_generator(generator));
		for( auto subject : subjects)
		{
		    std::vector<elem_t> data {prepared_data};
		    auto t1 = chrono::high_resolution_clock::now();
		    get_subject(subject)(data);
		    auto t2 = chrono::high_resolution_clock::now();
		    chrono::duration<timer_t,std::micro> d = t2-t1;

		    std::string test_name = get_name(subject)+"_"+get_name(generator);
		    test_timers[test_name][data_size] += d.count();
		}
	    }
    for( auto& test_timers : test_timers )
	for( auto& timer : test_timers )
	    timer /= (timer_t)repetitions;
}

// template<typename T,typename G,typename M>
// void test(M& map,G distr,unsigned int repetitions)
// {
//     while( repetitions-- != 0 )
	
// 	for (int i=0; i<sizes.size() ; ++i)
// 	{
// 	    std::vector<T> vec(sizes[i]);
// 	    std::generate(vec.begin(), vec.end(),distr.second);
// 	    cerr<<sizes[i]<<endl;
// 	    for( auto f : map)
// 	    {
// 		cerr<<f.first<<endl;
// 		std::vector<T> v {vec};
// 		auto t1 = chrono::high_resolution_clock::now();
// 		f.second(v);
// 		auto t2 = chrono::high_resolution_clock::now();
// //		cout<<v.front()<<' '<<v.back()<<',';
// 		chrono::duration<double,std::micro> d = t2-t1;
// 		t_map[f.first+"_"+distr.first][i] += d.count();
// 		if(is_unsorted(v)) cerr<<f.first<<"~bad\n";
// 	    }
// //	    cout<<endl;
// 	}
// }

template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage2
PerformanceTester<T_S,T_DG>::setup_stage1::set_subjects(std::map<std::string,T_Subject>& arg)
{
    setup_data.subjects = arg;
    return setup_stage2( setup_data );
}
template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage2
PerformanceTester<T_S,T_DG>::setup_stage1::set_subjects(std::map<std::string,T_Subject>&& arg)
{
    setup_data.subjects = arg;
    return setup_stage2( setup_data );
}
template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage3
PerformanceTester<T_S,T_DG>::setup_stage2::set_data_generators(std::map<std::string,T_DataDistribution>& arg)
{
    setup_data.data_distributions = arg;
    return setup_stage3( setup_data );
}
template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage3
PerformanceTester<T_S,T_DG>::setup_stage2::set_data_generators(std::map<std::string,T_DataDistribution>&& arg)
{
    setup_data.data_distributions = arg;
    return setup_stage3( setup_data );
}
template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage4
PerformanceTester<T_S,T_DG>::setup_stage3::set_data_distributions(std::vector<size_t>& arg)
{
    setup_data.dataset_sizes = arg;
    return setup_stage4( setup_data );
}
template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage4
PerformanceTester<T_S,T_DG>::setup_stage3::set_data_distributions(std::vector<size_t>&& arg)
{
    setup_data.dataset_sizes = arg;
    return setup_stage4( setup_data );
}
template<typename T_S,typename T_DG>
inline
PerformanceTester<T_S,T_DG>::setup_stage4
PerformanceTester<T_S,T_DG>::setup_stage4::set_repetitions(size_t arg)
{
    setup_data.test_repetitions = arg;
    return operational_interface( setup_data );
}
#endif COMMON_H
